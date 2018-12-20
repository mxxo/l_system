#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <unordered_map>
#include <numeric>
#include <functional>

#include <iostream>

namespace l_system {

  class LSymbolType {

    char representation_;

  public:

    LSymbolType() {}
    LSymbolType(char representation) : representation_(representation) {}

    [[nodiscard]] auto representation() const noexcept -> char {

      return representation_;
    }

    bool operator==(const LSymbolType &other) const {

      return representation_ == other.representation();
    }
  };

  static LSymbolType NullLSymbol;

  template <typename RepresentationHash = std::hash<char>>
  struct LSymbolTypeHash {

    size_t operator()(const LSymbolType& k) const {

      return RepresentationHash()(k.representation());
    }
  };

  class LSymbol {

    LSymbolType* type_;

  public:
    LSymbol(LSymbolType* type) : type_(type) {}

    LSymbol() : type_(&NullLSymbol) {}

    [[nodiscard]] auto type() const noexcept -> LSymbolType* {

      return type_;
    }
  };

  typedef std::basic_string<LSymbol> LString;

  [[nodiscard]] auto represent(const LString& lstring) noexcept -> std::basic_string<char> {

    std::basic_string<char> representation;

    for(LSymbol symbol : lstring) {

      representation.push_back(symbol.type()->representation());
    }

    return representation;
  }

  class LRule {

    LString result_;

  public:

    LRule(LString result) : result_(result) {}

    [[nodiscard]] auto operator()([[maybe_unused]] LString before, [[maybe_unused]] LString after) const noexcept -> LString {

      return result_;
    }
  };

  class LSystem {

    LString axiom_;
    std::unordered_map<LSymbolType, LRule, LSymbolTypeHash<>> rules;

  public:

    void addRule(LSymbolType* type, LRule rule) noexcept {

      rules.emplace(*type, rule);
    }

    void setAxiom(const LString& axiom) noexcept {

      axiom_ = axiom;
    }

    [[nodiscard]] auto axiom() const noexcept -> LString {

      return axiom_;
    }

    [[nodiscard]] auto generate(int generations) const noexcept -> LString {

      auto current = axiom_;

      for(int i = 0; i < generations; i++) {

        std::vector<LString> result;
        result.reserve(current.size());

        for(auto symbol = current.begin(); symbol != current.end(); symbol++) {

          bool symbolIsTerminal = rules.count(*symbol->type()) == 0;

          LString symbolReplacement;

          if(symbolIsTerminal) {

            symbolReplacement.push_back(*symbol);
          }
          else {

            LString before = (symbol == current.begin()) ? LString() : LString(current.begin(), symbol - 1);
            LString after = (symbol == current.end() - 1) ? LString() : LString(symbol + 1, current.end() - 1);
            symbolReplacement = rules.at(*symbol->type())(before, after);
          }

          result.emplace_back(symbolReplacement);
        }

        current = std::accumulate(result.begin(), result.end(), LString());
      }

      return current;
    }
  };
}

#endif
