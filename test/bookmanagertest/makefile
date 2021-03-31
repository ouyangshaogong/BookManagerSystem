SHELL = /bin/bash
 
AllDirs := $(shell ls -R | grep '^\./.*:$$' | awk '{gsub(":","");print}') .
Sources := $(foreach n,$(AllDirs) , $(wildcard $(n)/*.cpp))
Objs := $(patsubst %.cpp,%.o, $(Sources))
Deps := $(patsubst %.cpp,%.d, $(Sources))


HOMEDIR=/mnt/hgfs/BOOKDEVELOPMENT/BookManagerSystem
INCDIR=$(HOMEDIR)/include

Bin := bookmanagertest

AllLibs : $(Bin)
CC = g++
CXXFLAGS = -g -O2 -fPIC -Wall
CPPFLAGS = $(foreach n,$(AllDirs) , -I$(n)) -I$(INCDIR)/common -I$(INCDIR)/bookmgrservice -I$(INCDIR)/dao -I$(INCDIR)/model -I$(INCDIR)/utils
LDFLAGS = -lstdc++ -lmysqlclient -lbookutils -lbookmodel -lbookmgrdao -lbookmgrservice

$(Bin) : $(Objs)
	g++ $(Objs) -o $@ $(LDFLAGS) 

%.d : %.cpp
	$(CC) -MT"$(<:.cpp=.o) $@" -MM $(CXXFLAGS) $(CPPFLAGS) $< > $@

.PHONY : clean
clean: 
	@rm -f $(Objs) $(Deps) $(Bin)
	@rm -rf core.*
