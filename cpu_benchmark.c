#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include "cpu_tests.h"

static double *testa, *testb;
void print_time(int type, const char *name, int (*test)(int type, void *, const void *)) {
    struct timespec gstart, gend;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    test(type, testa, testb);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);

    double eltime = 1000.*1000.*1000.*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec);
    if (!type) printf("%17s: %7.5f ns/instruction\n", name, eltime/CYCLE);
    else printf("%17s(%d): %7.5f ns/instruction\n", name, type, eltime/CYCLE);
}

int main() {
    testa = malloc(1<<26);
    testb = malloc(1<<26);
    printf("\nCYCLE: %.3f million\n", CYCLE/1000./1000.);
    print_time(0, "cycle speed", cycle_speed);
    puts("");
    print_time(0, "char speed", char_speed);
    print_time(0, "short speed", short_speed);
    print_time(0, "int speed", int_speed);
    print_time(0, "long long speed", longlong_speed);
    puts("");
#if defined(__ARM__) || defined(__AARCH64__)
    print_time(0, "half speed", half_speed);
#endif
    print_time(0, "float speed", float_speed);
    print_time(0, "double speed", double_speed);
    print_time(0, "long double speed", longdouble_speed);
    puts("");
    print_time(10, "mem speed", mem_speed);
    print_time(12, "mem speed", mem_speed);
    print_time(14, "mem speed", mem_speed);
    print_time(16, "mem speed", mem_speed);
    print_time(18, "mem speed", mem_speed);
    print_time(20, "mem speed", mem_speed);
    print_time(22, "mem speed", mem_speed);
    print_time(24, "mem speed", mem_speed);
    print_time(26, "mem speed", mem_speed);

    free(testb);
    free(testa);
    return 0;
}
