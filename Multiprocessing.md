Python
* threading in python does not use multiple cores
  * It just appears to work like that it is actually concurrent not parallel
* For true multithreading we actually want to use multiprocessing
  * however this does not work on standard python because of the GIL (global interpreter lock)
  * the GIL prevents python from using multiple cores
  * choices from here are
    * find a way around the GIL
    * download a version of python that doesn't have the GIL some options mentioned were Jython and IronPython
* obviously need multiple cpus and/or cores
* three modes
  * multiprocessing
  * threading
  * asyncio
  * each one is good at certain things and we would need to research which to use
  * need a name = main guard to avoid infinite loops
C++
* Works on any C++ past 2017 version (for parallel but this is what we want concurrent isn't worth it)
* can use more threads than cores in C++
* Only beneficial for long processes (not a problem for us)
  * also takes a lot of memory
* the functions we right need to be independent of each other completely because predicting which will finish first is hard
  * they can't use the same variables or outside functions
