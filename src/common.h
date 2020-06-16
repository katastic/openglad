// KATKO - October 5th, 2018
#ifndef HEADER_COMMON
#define HEADER_COMMON
// KAT (maybe the same as CX_SCREEN. Separate till we find out.)
const int SCREEN_W = 400;
const int SCREEN_H = 300;

#define KAT_2X
// see sai2x.cpp:~800

#ifdef KAT_2X
const int WINDOWS_W = (SCREEN_W*2);
const int WINDOWS_H = (SCREEN_H*2);
#else
const int WINDOWS_W = SCREEN_W;
const int WINDOWS_H = SCREEN_H;
#endif
#endif