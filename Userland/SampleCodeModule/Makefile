include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)

SOURCES_LIBS=$(wildcard libs/*.c)

SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

SOURCES_APPS=$(wildcard apps/*.c)

all: $(MODULE)


$(MODULE): $(SOURCES) $(SOURCES_LIBS) $(OBJECTS_ASM) $(APPS_OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld _loader.c $(SOURCES) $(SOURCES_LIBS) $(SOURCES_APPS) $(OBJECTS_ASM) -o ../$(MODULE)


%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf asm/*.o

.PHONY: all clean print
