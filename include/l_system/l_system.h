#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <unordered_map>
#include <numeric>
#include <functional>

#include <iostream>

namespace l_system {

  template <typename T>
  class LSymbolType {

    T representation_;

    public:

    LSymbolType() {}
    LSymbolType(T representation) : representation_(representation) {}

    auto representation() const noexcept -> T {

      return representation_;
    }

    bool operator==(const LSymbolType &other) const {

      return representation_ == other.representation();
    }
  };

  template <typename T>
  LSymbolType<T>* NullLSymbol() {

    static LSymbolType<T>* res = new LSymbolType<T>();

    return res;
  }

  template <typename T, typename H = std::hash<T>>
  struct LSymbolTypeHash {

    size_t operator()(const LSymbolType<T>& k) const {

      return H()(k.representation());
    }
  };

  template <typename T>
  class LSymbol {

    LSymbolType<T>* type_;

  public:
    LSymbol(LSymbolType<T>* type) : type_(type) {}

    LSymbol() : type_(NullLSymbol<T>()) {}

     auto type() const noexcept -> LSymbolType<T>* {

      return type_;
    }
  };

  template <typename T>
  using LString = std::basic_string<LSymbol<T>>;

  template <typename T>
   auto represent(const LString<T>& lstring) noexcept -> std::basic_string<T> {

    std::basic_string<T> representation;

    for(LSymbol<T> symbol : lstring) {

      representation.push_back(symbol.type()->representation());
    }

    return representation;
  }

  template <typename T>
  class LRule {

    LString<T> result_;

  public:

    LRule(LString<T> result) : result_(result) {}

    LRule(std::initializer_list<LSymbol<T>> result) : result_(result) {}

     auto operator()([[maybe_unused]] LString<T> before, [[maybe_unused]] LString<T> after) const noexcept -> LString<T> {

      return result_;
    }
  };

  template <typename T>
  class LSystem {

    LString<T> axiom_;
    std::unordered_map<LSymbolType<T>, LRule<T>, LSymbolTypeHash<T>> rules;

  public:

    LSystem(LString<T> axiom) : axiom_(axiom) {}
    LSystem(std::initializer_list<LSymbol<T>> axiom) : axiom_(axiom) {}

    void addRule(LSymbolType<T>* type, LRule<T> rule) noexcept {

      rules.emplace(*type, rule);
    }

    void setAxiom(const LString<T>& axiom) noexcept {

      axiom_ = axiom;
    }

     auto axiom() const noexcept -> LString<T> {

      return axiom_;
    }

     auto generate(int generations) const noexcept -> LString<T> {

      auto current = axiom_;

      for(int i = 0; i < generations; i++) {

        std::vector<LString<T>> result;
        result.reserve(current.size());

        for(auto symbol = current.begin(); symbol != current.end(); symbol++) {

          bool symbolIsTerminal = rules.count(*symbol->type()) == 0;

          LString<T> symbolReplacement;

          if(symbolIsTerminal) {

            symbolReplacement.push_back(*symbol);
          }
          else {

            auto before = (symbol == current.begin()) ? LString<T>() : LString<T>(current.begin(), symbol - 1);
            auto after = (symbol == current.end() - 1) ? LString<T>() : LString<T>(symbol + 1, current.end() - 1);
            symbolReplacement = rules.at(*symbol->type())(before, after);
          }

          result.emplace_back(symbolReplacement);
        }

        current = std::accumulate(result.begin(), result.end(), LString<T>());
      }

      return current;
    }
  };
}

#endif
