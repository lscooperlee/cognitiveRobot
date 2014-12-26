CROSS=

CC=$(CROSS)gcc
CPP=$(CROSS)g++
LD=$(CROSS)ld
AS=$(CROSS)as
AR=$(CROSS)ar
OBJCOPY=$(CROSS)objcopy


INSTALLDIR=.
EXEC=$(INSTALLDIR)/robot
LIB=$(INSTALLDIR)/librobot.a

ifeq ($(strip $(CROSS)),)
LIBDIR=/usr
else
LIBDIR=../libs
endif

LDFLAGS = 

CFLAGS = -std=c++11 -O2 -Wall -I. -DDEBUG -g -I$(LIBDIR)/include/ -I./include -I./src -I./src/robot


COPY        := cp
MKDIR       := mkdir -p
MV          := mv
RM          := rm -f
DIRNAME     := dirname


OBJDIR=/tmp/.obj

PATHDIR=src . src/robot
#PATHDIR=$(shell find -type d) 
SRCS= $(foreach dir,$(PATHDIR),$(wildcard $(dir)/*.cpp)) 
PATHOBJS=$(subst ./,,$(SRCS:.cpp=.o))
OBJS=$(patsubst %,$(OBJDIR)/%,$(PATHOBJS))
DEPS=$(OBJS:%.o=%.d)

all:$(EXEC) $(LIB) TEST

$(EXEC):$(OBJS)
	@$(CPP) $(STATIC) $(OBJS) -o $@ $(LDFLAGS) 

$(LIB):$(OBJS)
	@$(AR) rcs $@ $?

$(OBJDIR)/%.o:%.cpp 
	@echo COMPILING $(notdir $@)
	@$(MKDIR) `$(DIRNAME) $@`
#	$(CPP) $(CFLAGS) $< -MM -MT $@ -MF $@.d
	@$(CPP) $(CFLAGS) -c -o $@ $<

TEST:
	@make -C test

$(DEPS):$(OBJDIR)/%.d:%.cpp
	@$(MKDIR) `$(DIRNAME) $@`
	@$(CPP) $(CFLAGS) $< -MM -MT $(patsubst %.d,%.o,$@) -MF $@



install:
	@echo "installing"
	@$(MKDIR) $(INSTALLDIR)
	@$(COPY) -av $(EXEC) $(INSTALLDIR)

clean:
	@echo "cleaning"
	@make -C test clean
	@rm -rf $(EXEC) $(LIB) $(OBJS) $(DEPS) $(OBJDIR)


-include $(DEPS)
