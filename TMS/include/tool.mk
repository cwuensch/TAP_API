#
# Default toolchain
#
ARCH ?= mipsel-linux-uclibc


CROSS_COMPILE ?= $(ARCH)-

AS      = $(CROSS_COMPILE)as
LD      = $(CROSS_COMPILE)ld
CC      = $(CROSS_COMPILE)gcc -mips32 -D_TMS_
CXX     = $(CROSS_COMPILE)c++ -mips32 -D_TMS_
AR      = $(CROSS_COMPILE)ar
NM      = $(CROSS_COMPILE)nm
STRIP   = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB  = $(CROSS_COMPILE)ranlib
MKDIR   = mkdir -p
PWD     = pwd
MV      = mv

CPP     = $(CC) -E
CP      = cp -f
RM      = rm -f
SORT    = sort
SED     = sed
TOUCH   = touch
AWK     = awk
JB      = JailBreak.exe
RMDIR   = rmdir

# Option for quiet builds
ifeq ($(VERBOSE),n)
Q_ := @
else
Q_ :=
endif
