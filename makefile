SHELL = /bin/bash

HOMEDIR=/home/zhangfengli/vscode-projects/BookManagerSystem

ALLLIBS: UTILS MODEL DAO BOOKMGRSERVICE TEST ECHO

COPYINCLUDE:
	cp -rf $(HOMEDIR)/business/bookmgrservice/*.h $(HOMEDIR)/include/bookmgrservice
	cp -rf $(HOMEDIR)/business/dao/*.h $(HOMEDIR)/include/dao
	cp -rf $(HOMEDIR)/business/model/*.h $(HOMEDIR)/include/model
	cp -rf $(HOMEDIR)/utils/*.h $(HOMEDIR)/include/utils

UTILS:
	make -C $(HOMEDIR)/utils
	@cp $(HOMEDIR)/utils/libbookutils.so $(HOMEDIR)/lib

MODEL:
	make -C $(HOMEDIR)/business/model
	@cp $(HOMEDIR)/business/model/libbookmodel.so $(HOMEDIR)/lib

DAO: UTILS
	make -C $(HOMEDIR)/business/dao
	@cp $(HOMEDIR)/business/dao/libbookdao.so $(HOMEDIR)/lib

BOOKMGRSERVICE: UTILS MODEL DAO
	make -C $(HOMEDIR)/business/bookmgrservice
	@cp $(HOMEDIR)/business/bookmgrservice/libbookmgrservice.so $(HOMEDIR)/lib

TEST: BOOKMGRSERVICE UTILS MODEL DAO
	make -C $(HOMEDIR)/test

ECHO:
	echo $(DynamicLib)

.PHONY : clean
clean: 
	@make clean -C $(HOMEDIR)/utils
	@make clean -C $(HOMEDIR)/business/model
	@make clean -C $(HOMEDIR)/business/dao
	@make clean -C $(HOMEDIR)/business/bookmgrservice
	@make clean -C $(HOMEDIR)/test
	@rm -rf $(HOMEDIR)/lib/*.so
