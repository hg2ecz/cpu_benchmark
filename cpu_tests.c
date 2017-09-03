#include <complex.h>
#include "cpu_tests.h"

int cycle_speed(int num, void *restrict outvoid, const void *restrict avoid, const void *restrict bvoid) {
    for (int i=0; i<num; i++) asm ("nop");
    return 0;
}

#define insert_compute_block(FUNCNAME, VARTYPE, INNERITER) \
  int FUNCNAME ## _speed(int type, void *restrict outvoid, const void *restrict avoid, const void *restrict bvoid) { \
    const VARTYPE *a = (const VARTYPE *)avoid; \
    const VARTYPE *b = (const VARTYPE *)bvoid; \
    VARTYPE *out = (VARTYPE *)outvoid; \
    VARTYPE outreg = 0; \
    for (int i=0; i<CYCLE/BLOCKSIZE; i++) { \
	for (int idx=0; idx<BLOCKSIZE; ) { \
	    for (int j=0; j<INNERITER; j++) { \
		outreg+=a[idx]*b[idx]; \
		idx++; \
	    } \
	} \
    } \
    out[0]=outreg; \
    return sizeof(VARTYPE);\
}

// make complex arithmetic without complex.h
#define insert_compute_complexblock(FUNCNAME, VARTYPE, INNERITER) \
  int FUNCNAME ## _speed(int type, void *restrict outvoid, const void *restrict avoid, const void *restrict bvoid) { \
    const VARTYPE *a = (const VARTYPE *)avoid; \
    const VARTYPE *b = (const VARTYPE *)bvoid; \
    VARTYPE *out = (VARTYPE *)outvoid; \
    VARTYPE outreg[2] = {0, 0}; \
    for (int i=0; i<CYCLE/BLOCKSIZE; i++) { \
	for (int idx=0; idx<2*BLOCKSIZE; ) { \
	    for (int j=0; j<INNERITER; j++) { \
		outreg[0]+=a[idx]*b[idx] - a[idx+1]*b[idx+1]; \
		outreg[1]+=a[idx]*b[idx+1] + a[idx+1]*b[idx]; \
		idx+=2; \
	    } \
	} \
    } \
    out[0]=outreg[0]; \
    out[1]=outreg[1]; \
    return sizeof(VARTYPE);\
}

insert_compute_block(char, char, ITERNUM)
insert_compute_block(short, short, ITERNUM)
insert_compute_block(int, int, ITERNUM)
insert_compute_block(longlong, long long, ITERNUM)
#if defined(__x86_64__)
insert_compute_block(int128, __int128, ITERNUM)
#endif
#if defined(__arm__) || defined(__aarch64__)
insert_compute_block(half, _Float16, ITERNUM)
#endif
insert_compute_block(float, float, ITERNUM)
insert_compute_block(double, double, ITERNUM)
insert_compute_block(longdouble, long double, ITERNUM)
#if defined(__x86_64__)
# include <quadmath.h>
insert_compute_block(float128, __float128, ITERNUM)
#endif

// complex
#if defined(__arm__) || defined(__aarch64__)
insert_compute_block(complexhalf, complex _Float16, ITERNUM/2)
insert_compute_complexblock(half2cmplx, _Float16, ITERNUM/2) // from std half
#endif

insert_compute_block(complexfloat, complex float, ITERNUM/2)
insert_compute_complexblock(float2cmplx, float, ITERNUM/2) // from std float

insert_compute_block(complexdouble, complex double, ITERNUM/2)
insert_compute_complexblock(double2cmplx, double, ITERNUM/2) // from std double
#if defined(__x86_64__)
# include <quadmath.h>
insert_compute_block(complex128, __complex128, ITERNUM/2)
insert_compute_complexblock(float128_2cmplx, __float128, ITERNUM/2) // from std __float128
#endif

#define memread8();\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;\
    res+=in[idx]; idx+=16;

int memread_speed(int type, void *restrict outvoid, const void *restrict avoid, const void *restrict bvoid) {
    const int *in = (const int *)avoid;
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

int memwrite_speed(int type, void *restrict outvoid, const void *restrict avoid, const void *restrict bvoid) {
    const int *in = (const int *)avoid;
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

int memmove_speed(int type, void *restrict outvoid, const void *restrict avoid, const void *restrict bvoid) {
    const int *in = (const int *)avoid;
    int *out = (int *)outvoid;
    if ( (1<<type) > CYCLE) return -1;
    const int mask = ( (1<<type)/sizeof(int) )-1;
    for (int idx=0, i=0; i<CYCLE>>6; i++) {
	memmove8(); memmove8(); memmove8(); memmove8(); // 32
	memmove8(); memmove8(); memmove8(); memmove8(); // 64
	idx &= mask;
    }
    return 0;
}
