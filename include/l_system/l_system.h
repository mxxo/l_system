#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <unordered_map>
#include <algorithm>

namespace l_system {

  class LSymbolType {

    char representation_;

    LSymbolType(char representation) : representation_(representation) {}

    [[nodiscard]] auto representation() const noexcept -> char {

      return representation_;
    }
  };

  class LSymbol {

    LSymbolType* type_;

    LSymbol(LSymbolType* type) : type_(type) {}

    [[nodiscard]] auto type() const noexcept -> LSymbolType* {

      return type_;
    }
  };

  typedef std::basic_string<LSymbol> LString;

  class LRule {

    LString result_;

    LRule(LString result) : result_(result) {}

    [[nodiscard]] auto operator()(LString before, LString after) const noexcept -> LString {

      return result_;
    }
  };

  class LSystem {

    LString axiom_;
    std::unordered_map<LSymbolType, LRule> rules;

    void addRule(LSymbolType* type, LRule rule) noexcept {

      rules.emplace(&type, rule);
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

        std::vector<LString> result();
        result.reserve(current.size());

        for(auto symbol = current.begin(); symbol != current.end(); symbol++) {

          bool symbolIsTerminal = rules.count(*symbol) == 0;

          LString symbolReplacement;

          if(symbolIsTerminal) {

            symbolReplacement.push_back(*symbol);
          }
          else {

            symbolReplacement = rules.at(symbol->type())(LString(current.begin(), symbol - 1), LString(symbol + 1, current.end() - 1));
          }

          result.emplace_back(symbolReplacement);
        }

        current = std::accumulate(result.begin(), result.end());
      }

      return current;
    }
  };

  [[nodiscard]] auto represent(const LString& lstring) noexcept -> std::basic_string<char> {

    std::basic_string<char> representation;

    for(LSymbol symbol : lstring) {

      representation.push_back(symbol.type()->representation());
    }

    return representation;
  }
}

#endif
