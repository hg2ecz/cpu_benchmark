#define BLOCKSIZE (1<<12)
#define CYCLE (1<<26)

int cycle_speed(int num, void *restrict out, const void *restrict a, const void *restrict b);

int char_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int short_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int int_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int longlong_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int int128_speed(int type, void *restrict out, const void *restrict a, const void *restrict b); // x86_64

int half_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);   // arm || aarch64
int float_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int double_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int longdouble_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int float128_speed(int type, void *restrict out, const void *restrict a, const void *restrict b); // x86_64

// from complex.h  variable
int complexhalf_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int complexfloat_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int complexdouble_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int complex128_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);

// from std variable
int half2cmplx_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int float2cmplx_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int double2cmplx_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int float128_2cmplx_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);


int memread_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int memwrite_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
int memmove_speed(int type, void *restrict out, const void *restrict a, const void *restrict b);
