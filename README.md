# SGML-validator

A SGML tag validator we had to do in CS class (Polytech, 3rd year).

*Nota bene*: no validation is done on tags outside the root tag ; no validation is done on tag attributes.

## Requirements

* CMake >= 3.8
* gcc >= 7

## How to use it

The main executable (named `TP`) is taking 0 or 1 argument, if none are given, it uses a default file: `tests/first.txt`, otherwise it tries to valide a file whose filename was given as argument.

## Building

```bash
$ cmake -H. -Bbuild
$ cmake --build build --config Debug
```