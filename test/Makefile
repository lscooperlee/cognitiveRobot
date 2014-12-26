CROSS=

CC=$(CROSS)gcc
CPP=$(CROSS)g++
LD=$(CROSS)ld
AS=$(CROSS)as
OBJCOPY=$(CROSS)objcopy


INSTALLDIR=./

ifeq ($(strip $(CROSS)),)
LIBDIR=../
else
LIBDIR=../libs
endif

LDFLAGS = -L$(LIBDIR) -lrobot

CFLAGS = -std=c++11 -O2 -Wall -I. -DDEBUG -g -I$(LIBDIR)/include/ -I./include -I../src -I../src/robot


COPY        := cp
MKDIR       := mkdir -p
MV          := mv
RM          := rm -f
DIRNAME     := dirname


OBJDIR=/tmp/.obj

PATHDIR=.
SRCS= $(foreach dir,$(PATHDIR),$(wildcard $(dir)/*.cpp)) 
PATHOBJS=$(notdir $(SRCS:.cpp=.o))
OBJS=$(patsubst %,$(OBJDIR)/%,$(PATHOBJS))
DEPS=$(OBJS:%.o=%.d)
#EXEC=$(patsubst %,$(INSTALLDIR)/%, $(notdir $(OBJS:.o=)))
EXEC=$(OBJS:.o=)

all:$(EXEC) 
	@$(MV) $? $(INSTALLDIR)

$(EXEC):%:%.o
	@$(CPP) $(STATIC) $< -o $@ $(LDFLAGS) 

$(OBJDIR)/%.o:%.cpp 
	@echo COMPILING $(notdir $@)
	@$(MKDIR) `$(DIRNAME) $@`
	@$(CPP) $(CFLAGS) -c -o $@ $<


$(DEPS):$(OBJDIR)/%.d:%.cpp
	@$(MKDIR) `$(DIRNAME) $@`
	@$(CPP) $(CFLAGS) $< -MM -MT $(patsubst %.d,%.o,$@) -MF $@

install:
	@echo "installing"
	@$(MKDIR) $(INSTALLDIR)
	@$(COPY) -av $(EXEC) $(INSTALLDIR)

clean:
	@echo "cleaning"
	@rm -rf $(patsubst %,$(INSTALLDIR)/%,$(notdir $(EXEC))) $(EXEC) $(OBJS) $(DEPS)


-include $(DEPS)
