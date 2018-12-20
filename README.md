# l_system
A fast, flexible, general, work in progress lindenmayer-like system evaluation library in C++.
## Fast
The runtime complexity of any given l system is completely dependent on the axiom and rules of that system.
That being said, this library aims to generate as fast as possible.
The analysis is non-recursive, there is no dynamic dispatch, and move semantics are used to hasten data flow.
Many more speed improvements are still to be had.
## General
This library separates the model of an l system from its representation.
An l system can be created with representation by any data type, including user defined types.
There are minimal requirements for enabling a user defined type to work with the library.
## Flexible
The symbol types, symbols, rules, and axiom for an l system can all be modified and re-evaluated during runtime.
## A work in progress
This library is heavily work in progress. Things may change in breaking ways.
The goal is a bi-directional model which supports stochastic, parametric, and context sensitive grammar for rules.
Currently, the model is bi-directional, but lacks the other capabilities, which are being actively implemented.
