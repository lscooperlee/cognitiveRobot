CROSS=

CC=$(CROSS)gcc
CPP=$(CROSS)g++
LD=$(CROSS)ld
AS=$(CROSS)as
OBJCOPY=$(CROSS)objcopy

EXEC=robot

INSTALLDIR=/tmp/robot

ifeq ($(strip $(CROSS)),)
LIBDIR=/usr
else
LIBDIR=../libs
endif

LDFLAGS = 

CFLAGS = -O2 -Wall -I. -DDEBUG -g -I$(LIBDIR)/include/ -I./include -I../install/include/


COPY        := cp
MKDIR       := mkdir -p
MV          := mv
RM          := rm -f
DIRNAME     := dirname


OBJDIR=/tmp/.obj

PATHDIR=$(shell find -type d) 
#PATHDIR=.
SRCS= $(foreach dir,$(PATHDIR),$(wildcard $(dir)/*.cpp)) 
PATHOBJS=$(subst ./,,$(SRCS:.cpp=.o))
OBJS=$(patsubst %,$(OBJDIR)/%,$(PATHOBJS))

$(EXEC):$(OBJS)
	$(CPP) $(STATIC) $(OBJS) -o $@ $(LDFLAGS) 

$(OBJS):$(OBJDIR)/%.o:%.cpp
	@echo COMPILING $(notdir $@)
	@$(MKDIR) `$(DIRNAME) $@`
	$(CPP) $(CFLAGS) -c -o $@ $<

install:
	@echo "installing"
	@$(MKDIR) $(INSTALLDIR)
	@$(COPY) -av $(EXEC) $(INSTALLDIR)

clean:
	rm -rf $(EXEC) $(OBJDIR)
