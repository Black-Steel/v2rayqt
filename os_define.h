#ifndef OS_DEFINE_H
#define OS_DEFINE_H

//msvc
//https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=vs-2019

//gcc
//gcc -dM -E - < /dev/null

//g++
//g++ -dM -E -x c++ - < /dev/null
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
    //windows
    #define OS_WINDOWS 1
#elif defined(__CYGWIN__)
    #define OS_CYGWIN 1
#elif defined(__ANDROID__) || defined(ANDROID)
    //android
    #define OS_ANDROID 1
#elif defined(__APPLE__)
    //apple
    #define OS_APPLE 1
#elif defined(__linux__) || defined(__linux)
    //linux
    #define OS_LINUX 1
#else
    //unknow
    #define OS_UNKNOW 1
#endif

#endif // OS_DEFINE_H
