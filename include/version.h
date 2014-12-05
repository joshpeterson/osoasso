#ifndef __VERSION_H
#define __VERSION_H

#define VERSION "23"

#if defined(__EMSCRIPTEN__)
    #define TARGET "JavaScript"
#else
    #define TARGET "PNaCL"
#endif

#endif // __VERSION_H
