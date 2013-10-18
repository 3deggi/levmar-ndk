ANDROID_NDK_BIN:=C:/android-ndk-r9/toolchains/arm-linux-androideabi-4.6/prebuilt/windows/bin

# Compilation Tools

CC := $(ANDROID_NDK_BIN)/arm-linux-androideabi-gcc

#CPP := $(ANDROID_NDK_BIN)/arm-linux-androideabi-g++

AR := $(ANDROID_NDK_BIN)/arm-linux-androideabi-ar

# Compiler flags

# Specify all the flags below which you want to use for your compilation, For this simple example, we only need to specify the include directory path

CFLAGS          := -I.

# Rule for making C++ object file

.cpp.o:

$(CPP) $(CFLAGS) -c  $<

# Rule for making C object file

.c.o:

$(CC) $(CFLAGS) -c  $<

STATIC_LIB_SRC = lm.c \
Axb.c \
misc.c \
lmlec.c \
lmbc.c \
lmblec.c \
lmbleic.c

STATIC_LIB_OBJ = lm.o \
Axb.o \
misc.o \
lmlec.o \
lmbc.o \
lmblec.o \
lmbleic.o

OUT = liblevmar.a

$(OUT): $(STATIC_LIB_OBJ)

$(AR) -crs $(OUT) $(STATIC_LIB_OBJ)