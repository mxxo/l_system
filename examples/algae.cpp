#include <iostream>
#include <cassert>
#include <stdlib.h>

#include "l_system/l_system.h"

int main(int argc, char const *argv[]) {

  using namespace l_system;

  assert(argc >= 2 && "Usage: algae generation");

  int generation = static_cast<int>(strtol(argv[1], nullptr, 0));

  LSymbolType A('A');
  LSymbolType B('B');

  LRule A_AB({LSymbol(&A), LSymbol(&B)});
  LRule B_A({LSymbol(&A)});

  LSystem algae;

  algae.setAxiom({LSymbol(&A)});

  algae.addRule(&A, A_AB);
  algae.addRule(&B, B_A);

  std::cout << "Algae generation " << generation << ": " << represent(algae.generate(generation)) << '\n';

  return 0;
}
