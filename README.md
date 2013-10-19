levmar-ndk
==========

Levenberg-Marquardt library in NDK for Android Application

These files are the source code of the driver for using LevMar library in NDK. 
Levenberg-Marquardt source code is from http://users.ics.forth.gr/~lourakis/levmar/
LevMar library can be used in two modes: with and without LAPACK. 
This folder also contains LAPACK, BLAS and F2C library for android from https://github.com/simonlynen/android_libs

The driver inside the JNI folder jni_part.cpp contains one block of codes from lmdemo.c inside the LevMar library. 
The android interface calls one function in the jni_part.cpp and output the result via LOG (info) in eclipse.

Read the installation manual here:

https://sites.google.com/site/sandymartedi/levmar-ndk

=================

sandclow@gmail.com


