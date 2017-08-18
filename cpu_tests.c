#include "cpu_tests.h"

int cycle_speed(int type, void *outvoid, const void *invoid) {
    for (int i=0; i<CYCLE; i++) asm ("nop");
    return 0;
}

#define compute(); \
    for (int i=0; i<CYCLE/BLOCKSIZE; i++) {\
	for (int idx=0; idx<BLOCKSIZE; ) {\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
/*					     \
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
*/	}\
    }



int char_speed(int type, void *outvoid, const void *invoid) {
    const char *in = (const char *)invoid;
    char *out = (char *)outvoid;
    compute();
    return 0;
}

int short_speed(int type, void *outvoid, const void *invoid) {
    const short *in = (const short *)invoid;
    short *out = (short *)outvoid;
    compute();
    return 0;
}

int int_speed(int type, void *outvoid, const void *invoid) {
    const int *in = (const int *)invoid;
    int *out = (int *)outvoid;
    compute();
    return 0;
}

int longlong_speed(int type, void *outvoid, const void *invoid) {
    const long long *in = (const long long *)invoid;
    long long *out = (long long *)outvoid;
    compute();
    return 0;
}

#if defined(__x86_64__)
int int128_speed(int type, void *outvoid, const void *invoid) {
    const __int128 *in = (const __int128 *)invoid;
    __int128 *out = (__int128 *)outvoid;
    compute();
    return 0;
}
#endif

#if defined(__arm__) || defined(__aarch64__)
int half_speed(int type, void *outvoid, const void *invoid) {
    const __fp16 *in = (const __fp16 *)invoid;
    __fp16 *out = (__fp16 *)outvoid;
    compute();
    return 0;
}
#endif

int float_speed(int type, void *outvoid, const void *invoid) {
    const float *in = (const float *)invoid;
    float *out = (float *)outvoid;
    compute();
    return 0;
}

int double_speed(int type, void *outvoid, const void *invoid) {
    const double *in = (const double *)invoid;
    double *out = (double *)outvoid;
    compute();
    return 0;
}

int longdouble_speed(int type, void *outvoid, const void *invoid) {
    const long double *in = (const long double *)invoid;
    long double *out = (long double *)outvoid;
    compute();
    return 0;
}

#if defined(__x86_64__)
# include <quadmath.h>
int float128_speed(int type, void *outvoid, const void *invoid) {
    const __float128 *in = (const __float128 *)invoid;
    __float128 *out = (__float128 *)outvoid;
    compute();
    return 0;
}
#endif



#define move_and_inc4();\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;

int mem_speed(int type, void *outvoid, const void *invoid) {
    const int *in = (const int *)invoid;
    int *out = (int *)outvoid;
    int mask = ( (1<<type)/sizeof(int) )-1;
    for (int idx=0, i=0; i<CYCLE>>6; i++) {
	move_and_inc4(); move_and_inc4(); move_and_inc4(); move_and_inc4(); // 16
	move_and_inc4(); move_and_inc4(); move_and_inc4(); move_and_inc4(); // 32
	move_and_inc4(); move_and_inc4(); move_and_inc4(); move_and_inc4(); // 48
	move_and_inc4(); move_and_inc4(); move_and_inc4(); move_and_inc4(); // 64
	idx &= mask;
    }
    return 0;
}
