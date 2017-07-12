#define BLOCKSIZE (1<<12)
#define CYCLE (1<<30)
#define ITERNUM 8

int cycle_speed(int type, void *out, const void *in);

int char_speed(int type, void *out, const void *in);
int short_speed(int type, void *out, const void *in);
int int_speed(int type, void *out, const void *in);
int longlong_speed(int type, void *out, const void *in);
int int128_speed(int type, void *out, const void *in); // x86_64

int half_speed(int type, void *out, const void *in);   // arm || aarch64
int float_speed(int type, void *out, const void *in);
int double_speed(int type, void *out, const void *in);
int longdouble_speed(int type, void *out, const void *in);
int float128_speed(int type, void *out, const void *in); // x86_64

int complexhalf_speed(int type, void *out, const void *in);
int complexfloat_speed(int type, void *out, const void *in);
int complexdouble_speed(int type, void *out, const void *in);
int complex128_speed(int type, void *out, const void *in);

int memread_speed(int type, void *out, const void *in);
int memwrite_speed(int type, void *out, const void *in);
int memmove_speed(int type, void *out, const void *in);
