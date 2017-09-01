#include "cpu_tests.h"

int cycle_speed(int type, void *outvoid, const void *invoid) {
    for (int i=0; i<CYCLE; i++) asm ("nop");
    return 0;
}

int char_speed(int type, void *outvoid, const void *invoid) {
    const char *in = (const char *)invoid;
    char *out = (char *)outvoid;
    for (int i=0; i<CYCLE; i++) {
	int idx = i&(BLOCKSIZE-1);
	out[idx]+=in[idx]*in[idx];
    }
    return 0;
}

int short_speed(int type, void *outvoid, const void *invoid) {
    const short *in = (const short *)invoid;
    short *out = (short *)outvoid;
    for (int i=0; i<CYCLE; i++) {
	int idx = i&(BLOCKSIZE-1);
	out[idx]+=in[idx]*in[idx];
    }
    return 0;
}

int int_speed(int type, void *outvoid, const void *invoid) {
    const int *in = (const int *)invoid;
    int *out = (int *)outvoid;
    for (int i=0; i<CYCLE; i++) {
	int idx = i&(BLOCKSIZE-1);
	out[idx]+=in[idx]*in[idx];
    }
    return 0;
}

int longlong_speed(int type, void *outvoid, const void *invoid) {
    const long long *in = (const long long *)invoid;
    long long *out = (long long *)outvoid;
    for (int i=0; i<CYCLE; i++) {
	int idx = i&(BLOCKSIZE-1);
	out[idx]+=in[idx]*in[idx];
    }
    return 0;
}

#if defined(__ARM__) || defined(__AARCH64__)
int half_speed(int type, void *outvoid, const void *invoid) {
    const _fp16 *in = (const _fp16 *)invoid;
    _fp16 *out = (_fp16 *)outvoid;
    for (int i=0; i<CYCLE; i++) {
	int idx = i&(BLOCKSIZE-1);
	out[idx]+=in[idx]*in[idx];
    }
    return 0;
}
#endif

int float_speed(int type, void *outvoid, const void *invoid) {
    const float *in = (const float *)invoid;
    float *out = (float *)outvoid;
    for (int i=0; i<CYCLE; i++) {
	int idx = i&(BLOCKSIZE-1);
	out[idx]+=in[idx]*in[idx];
    }
    return 0;
}

int double_speed(int type, void *outvoid, const void *invoid) {
    const double *in = (const double *)invoid;
    double *out = (double *)outvoid;
    for (int i=0; i<CYCLE; i++) {
	int idx = i&(BLOCKSIZE-1);
	out[idx]+=in[idx]*in[idx];
    }
    return 0;
}

int longdouble_speed(int type, void *outvoid, const void *invoid) {
    const long double *in = (const long double *)invoid;
    long double *out = (long double *)outvoid;
    for (int i=0; i<CYCLE; i++) {
	int idx = i&(BLOCKSIZE-1);
	out[idx]+=in[idx]*in[idx];
    }
    return 0;
}

int mem_speed(int type, void *outvoid, const void *invoid) {
    const int *in = (const int *)invoid;
    int *out = (int *)outvoid;
    int mask = ( (1<<type)/sizeof(int) )-1;
    for (int i=0; i<CYCLE; i++) {
	int idx = (i<<4)&mask;
	out[idx]=in[idx];
    }
    return 0;
}
