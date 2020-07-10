#ifndef UTILITY_H
#define UTILITY_H

#include <bits/stdc++.h>
using namespace std;

class Utility{
public:
    static string ls_headers;
    static string ls_seperators;

    static void memcpy(void *dest, const void *src, size_t n);
	static void memset(void *s, int ch, size_t n);
	static int memcmp(const void *buf1, const void *buf2, unsigned int count);
    static void stamp_to_standard(time_t nSrc, char *sDestTime);
	static int min(int a, int b);
	static time_t time(time_t* t);
	static string mode_to_str(unsigned int mode);
//    static const unsigned int get_mask();
};

#endif
