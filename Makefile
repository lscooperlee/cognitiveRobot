CROSS=

CC=$(CROSS)gcc
CPP=$(CROSS)g++
LD=$(CROSS)ld
AS=$(CROSS)as
OBJCOPY=$(CROSS)objcopy

EXEC=/tmp/robot

INSTALLDIR=/tmp/robot

ifeq ($(strip $(CROSS)),)
LIBDIR=/usr
else
LIBDIR=../libs
endif

LDFLAGS = 

CFLAGS = -O2 -Wall -I. -DDEBUG -g -I$(LIBDIR)/include/ -I./include -I./src 


COPY        := cp
MKDIR       := mkdir -p
MV          := mv
RM          := rm -f
DIRNAME     := dirname


OBJDIR=/tmp/.obj

PATHDIR=$(shell find -type d) 
SRCS= $(foreach dir,$(PATHDIR),$(wildcard $(dir)/*.cpp)) 
PATHOBJS=$(subst ./,,$(SRCS:.cpp=.o))
OBJS=$(patsubst %,$(OBJDIR)/%,$(PATHOBJS))
DEPS=$(OBJS:%.o=%.d)

all:$(EXEC) 

$(EXEC):$(OBJS)
	$(CPP) $(STATIC) $(OBJS) -o $@ $(LDFLAGS) 

$(OBJDIR)/%.o:%.cpp 
	@echo COMPILING $(notdir $@)
	@$(MKDIR) `$(DIRNAME) $@`
#	$(CPP) $(CFLAGS) $< -MM -MT $@ -MF $@.d
	$(CPP) $(CFLAGS) -c -o $@ $<


$(DEPS):$(OBJDIR)/%.d:%.cpp
	@$(MKDIR) `$(DIRNAME) $@`
	$(CPP) $(CFLAGS) $< -MM -MT $(patsubst %.d,%.o,$@) -MF $@


install:
	@echo "installing"
	@$(MKDIR) $(INSTALLDIR)
	@$(COPY) -av $(EXEC) $(INSTALLDIR)

clean:
	rm -rf $(EXEC) $(OBJDIR)


-include $(DEPS)
