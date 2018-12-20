#include <iostream>

#include "l_system/l_system.h"

int main(int argc, [[maybe_unused]] char const *argv[]) {

  using namespace l_system;

  LSymbolType A('A');
  LSymbolType B('B');

  LRule A_AB({LSymbol(&A), LSymbol(&B)});
  LRule B_A({LSymbol(&A)});

  LSystem algae;

  algae.setAxiom({LSymbol(&A)});

  algae.addRule(&A, A_AB);
  algae.addRule(&B, B_A);

  for(int i = 0; i < 10; ++i) {

    std::cout << "Algae generation " << i << ": " << represent(algae.generate(i)) << '\n';
  }

  return 0;
}
