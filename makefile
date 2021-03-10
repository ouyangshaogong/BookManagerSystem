SHELL = /bin/bash

HOMEDIR=/home/zhangfengli/vscode-projects/BookManagerSystem

ALLLIBS: UTILS MODEL DAO BOOKMGRSERVICE USERMGRSERVICE TEST ECHO

UTILS:
	@cp -rf $(HOMEDIR)/utils/*.h $(HOMEDIR)/include/utils
	make -C $(HOMEDIR)/utils
	@cp $(HOMEDIR)/utils/libbookutils.so $(HOMEDIR)/lib

MODEL:
	@cp -rf $(HOMEDIR)/business/model/*.h $(HOMEDIR)/include/model
	make -C $(HOMEDIR)/business/model
	@cp $(HOMEDIR)/business/model/libbookmodel.so $(HOMEDIR)/lib

DAO: UTILS
	@cp -rf $(HOMEDIR)/business/dao/*.h $(HOMEDIR)/include/dao
	make -C $(HOMEDIR)/business/dao
	@cp $(HOMEDIR)/business/dao/libbookmgrdao.so $(HOMEDIR)/lib

BOOKMGRSERVICE: UTILS MODEL DAO
	@cp -rf $(HOMEDIR)/business/bookmgrservice/*.h $(HOMEDIR)/include/bookmgrservice
	make -C $(HOMEDIR)/business/bookmgrservice
	@cp $(HOMEDIR)/business/bookmgrservice/libbookmgrservice.so $(HOMEDIR)/lib

USERMGRSERVICE: UTILS MODEL DAO
	@cp -rf $(HOMEDIR)/business/usermgrservice/*.h $(HOMEDIR)/include/usermgrservice
	make -C $(HOMEDIR)/business/usermgrservice
	@cp $(HOMEDIR)/business/usermgrservice/libusermgrservice.so $(HOMEDIR)/lib

TEST: BOOKMGRSERVICE UTILS MODEL DAO
	make -C $(HOMEDIR)/test/bookmanagertest
	make -C $(HOMEDIR)/test/usermanagertest

ECHO:
	echo $(DynamicLib)

.PHONY : clean
clean: 
	@make clean -C $(HOMEDIR)/utils
	@make clean -C $(HOMEDIR)/business/model
	@make clean -C $(HOMEDIR)/business/dao
	@make clean -C $(HOMEDIR)/business/bookmgrservice
	@make clean -C $(HOMEDIR)/business/usermgrservice
	@make clean -C $(HOMEDIR)/test/bookmanagertest
	@make clean -C $(HOMEDIR)/test/usermanagertest
	@rm -rf $(HOMEDIR)/lib/*.so
