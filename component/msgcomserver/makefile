SHELL = /bin/bash
 
AllDirs := $(shell ls -R | grep '^\./.*:$$' | awk '{gsub(":","");print}') .
Sources := $(foreach n,$(AllDirs) , $(wildcard $(n)/*.cpp))
Objs := $(patsubst %.cpp,%.o, $(Sources))
Deps := $(patsubst %.cpp,%.d, $(Sources))

HOMEDIR=/mnt/hgfs/BOOKDEVELOPMENT/BookManagerSystem
INCDIR=$(HOMEDIR)/include

Bin := msgcomserver

AllLibs : $(Bin)
CC = g++
CXXFLAGS = -g -O -fPIC -Wall
CPPFLAGS = $(foreach n,$(AllDirs), -I$(n)) -I$(INCDIR)/common -I$(INCDIR)/component/msgproto -I$(INCDIR)/component/taskmgr 
LDFLAGS = -lstdc++ -lACE -ljsoncpp -lmsgproto -ltaskmgr

$(Bin) : $(Objs)
	g++ -shared -o $@ $^ $(LDFLAGS) 

%.d : %.cpp
	$(CC) -MT"$(<:.cpp=.o) $@" -MM $(CXXFLAGS) $(CPPFLAGS) $< > $@

.PHONY : clean
clean: 
	rm -f $(Objs) $(Deps) $(Bin)
