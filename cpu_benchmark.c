#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include "cpu_tests.h"

static double *out, *testa, *testb;
static int varlength;

double measure(int type, int num, int (*test)(int type, void *restrict out, const void *restrict a, const void *restrict b)) {
    struct timespec gstart, gend;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<num; i++) varlength = test(type, out, testa, testb);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    return 1000.*1000.*1000.*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec);
}

void print_time_arithmetic(const char *name, int (*test)(int type, void *restrict out, const void *restrict a, const void *restrict b)) {
    double eltime = measure(BLOCKSIZE, CYCLE/BLOCKSIZE, test);
    printf("%15s (%2d byte) speed: %7.4f ns/instruction\n", name, varlength, eltime/CYCLE);
}

void print_time_mem(unsigned int log2size) {
    double eltime_read = measure(log2size, 1, memread_speed);
    double eltime_write = measure(log2size, 1, memwrite_speed);
    double eltime_move = measure(log2size, 1, memmove_speed);
    printf("memtest(%d --> %5d kB) --> read: %7.4f ns/instr, write: %7.4f ns/instr, move: %7.4f ns/instr\n",
	log2size, (1<<log2size)/1024, eltime_read/CYCLE, eltime_write/CYCLE, eltime_move/CYCLE);
}

int main() {
    out = malloc(1<<26);
    testa = malloc(1<<26);
    testb = malloc(1<<26);


    printf("\n  (CYCLE: %.3f million)\n", CYCLE/1000./1000.);
    measure(CYCLE, 1, cycle_speed);
    measure(CYCLE, 1, cycle_speed);
    print_time_arithmetic("cycle", cycle_speed);

    puts("");
    print_time_arithmetic("char", char_speed);
    print_time_arithmetic("short", short_speed);
    print_time_arithmetic("int", int_speed);
    print_time_arithmetic("long long", longlong_speed);
#if defined(__x86_64__)
    print_time_arithmetic("int128", int128_speed);
#endif

    puts("");
#if defined(__arm__) || defined(__aarch64__)
    print_time_arithmetic("half", half_speed);
#endif
    print_time_arithmetic("float", float_speed);
    print_time_arithmetic("double", double_speed);
    print_time_arithmetic("long double", longdouble_speed);
#if defined(__x86_64__)
    print_time_arithmetic("float128", float128_speed);
#endif

    puts("");
#if defined(__arm__) || defined(__aarch64__)
# if __GNUC__ >= 7
    print_time_arithmetic("complexhalf", complexhalf_speed);
# endif
    print_time_arithmetic("half2cmplx", half2cmplx_speed);
#endif
    print_time_arithmetic("complex float", complexfloat_speed);
    print_time_arithmetic("float2cmplx", float2cmplx_speed);
    print_time_arithmetic("complex double", complexdouble_speed);
    print_time_arithmetic("double2cmplx", double2cmplx_speed);
#if defined(__x86_64__)
    print_time_arithmetic("complex128", complex128_speed);
    print_time_arithmetic("float128_2cmplx", float128_2cmplx_speed);
#endif


    puts("");
    print_time_mem(10);
    print_time_mem(12);
    print_time_mem(14);
    print_time_mem(15);
    print_time_mem(16);
    print_time_mem(17);
    print_time_mem(18);
    print_time_mem(19);
    print_time_mem(20);
    print_time_mem(22);
    print_time_mem(24);
    print_time_mem(26);

    free(testb);
    free(testa);
    free(out);
    return 0;
}
