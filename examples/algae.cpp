#include <iostream>
#include <cassert>
#include <stdlib.h>

#include "l_system/l_system.h"

using namespace l_system;

int main(int argc, char const *argv[]) {

  assert(argc >= 2 && "Usage: algae generation");
  int generation = static_cast<int>(strtol(argv[1], nullptr, 0));

  LSymbolType A('A'); //define symbol types
  LSymbolType B('B');

  LSymbol A_(&A); //define symbols needed for axiom and rules
  LSymbol B_(&B);

  LRule A_AB({A_, B_}); //define rules
  LRule B_A({A_});

  LSystem algae({LSymbol(&A)}); //define the system using an axiom

  algae.setAxiom({LSymbol(&A)}); //the axiom can also be modified

  algae.addRule(&A, A_AB); //add the rules to the axiom
  algae.addRule(&B, B_A);

  std::cout << "Algae generation " << generation << ": " << represent(algae.generate(generation)) << '\n';

  return 0;
}
