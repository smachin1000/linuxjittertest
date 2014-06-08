CC = gcc
CXXFLAGS += -Wall
TARGET = jittertest_basic jittertest_sched_fifo jittertest_mmap

.PHONY:	clean all test
all: jittertest_basic jittertest_sched_fifo jittertest_mmap

jittertest_basic:	jittertest_basic.o
jittertest_sched_fifo:	jittertest_sched_fifo.o
jittertest_mmap:	jittertest_mmap.o

clean:
	rm -f $(TARGET)
	rm -f $(objects)
	rm -f *.o
