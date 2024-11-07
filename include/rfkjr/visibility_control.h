#ifndef RFKJR__VISIBILITY_CONTROL_H_
#define RFKJR__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define RFKJR_EXPORT __attribute__ ((dllexport))
    #define RFKJR_IMPORT __attribute__ ((dllimport))
  #else
    #define RFKJR_EXPORT __declspec(dllexport)
    #define RFKJR_IMPORT __declspec(dllimport)
  #endif
  #ifdef RFKJR_BUILDING_LIBRARY
    #define RFKJR_PUBLIC RFKJR_EXPORT
  #else
    #define RFKJR_PUBLIC RFKJR_IMPORT
  #endif
  #define RFKJR_PUBLIC_TYPE RFKJR_PUBLIC
  #define RFKJR_LOCAL
#else
  #define RFKJR_EXPORT __attribute__ ((visibility("default")))
  #define RFKJR_IMPORT
  #if __GNUC__ >= 4
    #define RFKJR_PUBLIC __attribute__ ((visibility("default")))
    #define RFKJR_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define RFKJR_PUBLIC
    #define RFKJR_LOCAL
  #endif
  #define RFKJR_PUBLIC_TYPE
#endif
#endif  // RFKJR__VISIBILITY_CONTROL_H_
// Generated 07-Nov-2024 10:33:33
// Copyright 2019-2020 The MathWorks, Inc.
