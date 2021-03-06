SHELL = /bin/bash
 
AllDirs := $(shell ls -R | grep '^\./.*:$$' | awk '{gsub(":","");print}') .
Sources := $(foreach n,$(AllDirs) , $(wildcard $(n)/*.cpp))
Objs := $(patsubst %.cpp,%.o, $(Sources))
Deps := $(patsubst %.cpp,%.d, $(Sources))


HOMEDIR=/home/zhangfengli/vscode-projects/BookManagerSystem
INCDIR=$(HOMEDIR)/include

DynamicLib := libbookdao.so

AllLibs : $(DynamicLib)

CC = g++
CXXFLAGS = -g -O2 -fPIC -Wall
CPPFLAGS = $(foreach n,$(AllDirs) , -I$(n)) -I$(INCDIR)/common -I$(INCDIR)/model -I$(INCDIR)/utils
LDFLAGS = -lstdc++ -lbookmodel -lmysqlclient -lbookutils

$(DynamicLib) : $(Objs)
	g++ -shared -g -o $@ $^ $(LDFLAGS) 

%.d : %.cpp
	$(CC) -MT"$(<:.cpp=.o) $@" -MM $(CXXFLAGS) $(CPPFLAGS) $< > $@

.PHONY : clean
clean: 
	rm -f $(Objs) $(Deps) $(DynamicLib)
