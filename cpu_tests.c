#include <complex.h>
#include "cpu_tests.h"

int cycle_speed(int type, void *outvoid, const void *invoid) {
    for (int i=0; i<CYCLE; i++) asm ("nop");
    return 0;
}

#define MAKE_FN_NAME(x) int x ## _speed (int type, void *outvoid, const void *invoid)
#define FUNCTION_NAME(fnnamedef) MAKE_FN_NAME(fnnamedef)

#define insert_compute_block(FUNCNAME, VARTYPE) \
FUNCTION_NAME(FUNCNAME) { \
    const VARTYPE *in = (const VARTYPE *)invoid; \
    VARTYPE *out = (VARTYPE *)outvoid; \
    for (int i=0; i<CYCLE/BLOCKSIZE; i++) {\
	for (int idx=0; idx<BLOCKSIZE; ) {\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
					     \
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	    out[idx]+=in[idx]*in[idx]; idx++;\
	}\
    } \
    return sizeof(VARTYPE);\
}

insert_compute_block(char, char)
insert_compute_block(short, short)
insert_compute_block(int, int)
insert_compute_block(longlong, long long)
#if defined(__x86_64__)
insert_compute_block(int128, __int128)
#endif
#if defined(__arm__) || defined(__aarch64__)
insert_compute_block(half, __fp16)
insert_compute_block(complexhalf, _Complex _Float16)
#endif
insert_compute_block(float, float)
insert_compute_block(double, double)
insert_compute_block(longdouble, long double)
#if defined(__x86_64__)
# include <quadmath.h>
insert_compute_block(float128, __float128)
insert_compute_block(complex128, __complex128)
#endif

insert_compute_block(complexfloat, complex float)
insert_compute_block(complexdouble, complex double)



#define memread8();\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;

int memread_speed(int type, void *outvoid, const void *invoid) {
    const int *in = (const int *)invoid;
    int *out = (int *)outvoid;
    int res=out[0];
    const int mask = ( (1<<type)/sizeof(int) )-1;
    for (int idx=0, i=0; i<CYCLE>>6; i++) {
	memread8(); memread8(); memread8(); memread8(); // 32
	memread8(); memread8(); memread8(); memread8(); // 64
	idx &= mask;
    }
    return res;
}

#define memwrite8();\
    out[idx]=ct++; idx+=16;\
    out[idx]=ct++; idx+=16;\
    out[idx]=ct++; idx+=16;\
    out[idx]=ct++; idx+=16;\
    out[idx]=ct++; idx+=16;\
    out[idx]=ct++; idx+=16;\
    out[idx]=ct++; idx+=16;\
    out[idx]=ct++; idx+=16;

int memwrite_speed(int type, void *outvoid, const void *invoid) {
    const int *in = (const int *)invoid;
    int *out = (int *)outvoid;
    int ct=in[0];
    const int mask = ( (1<<type)/sizeof(int) )-1;
    for (int idx=0, i=0; i<CYCLE>>6; i++) {
	memwrite8(); memwrite8(); memwrite8(); memwrite8(); // 32
	memwrite8(); memwrite8(); memwrite8(); memwrite8(); // 64
	idx &= mask;
    }
    return 0;
}

#define memmove8();\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;\
    out[idx]=in[idx]; idx+=16;

int memmove_speed(int type, void *outvoid, const void *invoid) {
    const int *in = (const int *)invoid;
    int *out = (int *)outvoid;
    const int mask = ( (1<<type)/sizeof(int) )-1;
    for (int idx=0, i=0; i<CYCLE>>6; i++) {
	memmove8(); memmove8(); memmove8(); memmove8(); // 32
	memmove8(); memmove8(); memmove8(); memmove8(); // 64
	idx &= mask;
    }
    return 0;
}
