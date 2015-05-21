This is a project connected with yandex-school programming studies (2nd task, 4th problem):

Roles of programmers:

Sasha: Classes inheritance structure (Object: Hunter, Prey, Obstacle), classes interfaces design (Singleton, Ocean interfaces), implementation of multiple dispatch and all code in object.h/object.cpp.
Maxim: Implementation of Ocean singleton factory, main modeling loop (all implementation code in ocean.hpp and main.cpp).
See commit log for more details.

Design patterns and idioms used:

- Singleton pattern.
- Factory pattern.
- «Mirror pattern» (see comments in a source code).
- Multiple dispatch (visitor pattern).
- RTTI idiom (was later replaced by virtual function PrintSelf?).

Build:

- cmake
- make

Documentation:

run doxygen or use pre-generated documentation in html/index.html
