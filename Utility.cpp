#include "Utility.h"

string Utility::ls_headers = "Type\tAccessMode\tName\tSize\tLastModifyTime\n";
//string Utility::ls_headers = "Type\tAccessMode\tName\tOwner\tSize\tLastModifyTime\n";
string Utility::ls_seperators = string(70, '-') + string("\n");

void Utility::memcpy(void *dest, const void *src, size_t n) {
	::memcpy(dest, src, n);
}

void Utility::memset(void *s, int ch, size_t n) {
	::memset(s, ch, n);
}

int Utility::memcmp(const void *buf1, const void *buf2, unsigned int count) {
	return ::memcmp(buf1, buf2, count);
}

void Utility::stamp_to_standard(time_t nSrc, char *sDestTime){
    struct tm p;
    p = *localtime(&nSrc);
    strftime(sDestTime, 1000,"%Y-%m-%d %H:%M:%S", &p);
}

int Utility::min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

time_t Utility::time(time_t* t) {
	return ::time(t);
}

string Utility::mode_to_str(unsigned int mode){
    string mode_str("");
    char cur_mode;
    for(int len=0;len<9;++len){
        if(mode%2==1) cur_mode = len%3==0?'x':len%3==1?'w':'r';
        else cur_mode = '-';
        mode_str = string(1,cur_mode)+mode_str;
        mode /= 2;
    }
    return mode_str;
}

//const unsigned int Utility::get_mask() {
//    unsigned int ch = 0b110;
//    return (const unsigned int)(~(ch<<3));
//}
