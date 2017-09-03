CC=gcc
CFLAGS =-Wall -Ofast
CFLAGS += -funroll-all-loops

PARAMS_CPU = -march=native -DITERNUM=16
ifeq ($(shell uname -m), armv6l)
    PARAMS_CPU = -march=native -mfp16-format=ieee
endif
ifeq ($(shell uname -m), armv7l)
    PARAMS_CPU = -mcpu=cortex-a5 -mfpu=neon-fp16 -mfp16-format=ieee -DITERNUM=4
endif
CFLAGS+= $(PARAMS_CPU)

LDFLAGS=-lm -s
OBJS=cpu_tests.o cpu_benchmark.o

TARGET=benchmark



all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
