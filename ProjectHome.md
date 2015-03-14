This is a project connected with [yandex-school](http://shad.yandex.ru/) programming studies (2nd task, 4th problem):


Roles of programmers:

  * **Sasha:** Classes inheritance structure (Object: Hunter, Prey, Obstacle), classes interfaces design (Singleton, Ocean interfaces), implementation of multiple dispatch and all code in object.h/object.cpp.
  * **Maxim:** Implementation of Ocean singleton factory, main modeling loop (all implementation code in ocean.hpp and main.cpp).

See [commit log](http://code.google.com/p/oceanmodeling/source/list) for more details.

Design patterns and idioms used:
  1. Singleton pattern.
  1. Factory pattern.
  1. «Mirror pattern» (see comments in a source code).
  1. Multiple dispatch (visitor pattern).
  1. RTTI idiom (was later replaced by virtual function PrintSelf).

Build:
  * cmake
  * make

Documentation:
  * run doxygen or use pre-generated documentation in html/index.html