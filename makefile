SHELL = /bin/bash

HOMEDIR=/home/zhangfengli/vscode-projects/BookManagerSystem

ALLLIBS: UTILS MODEL DAO BOOKMGRSERVICE USERMGRSERVICE COMPONENT TESTCLIENT TEST ECHO

UTILS:
	@cp -rf $(HOMEDIR)/utils/*.h $(HOMEDIR)/include/utils
	${MAKE} -C $(HOMEDIR)/utils
	@cp $(HOMEDIR)/utils/libbookutils.so $(HOMEDIR)/lib

MODEL:
	@cp -rf $(HOMEDIR)/business/model/*.h $(HOMEDIR)/include/model
	${MAKE} -C $(HOMEDIR)/business/model
	@cp $(HOMEDIR)/business/model/libbookmodel.so $(HOMEDIR)/lib

DAO: UTILS
	@cp -rf $(HOMEDIR)/business/dao/*.h $(HOMEDIR)/include/dao
	${MAKE} -C $(HOMEDIR)/business/dao
	@cp $(HOMEDIR)/business/dao/libbookmgrdao.so $(HOMEDIR)/lib

BOOKMGRSERVICE: UTILS MODEL DAO
	@cp -rf $(HOMEDIR)/business/bookmgrservice/*.h $(HOMEDIR)/include/bookmgrservice
	${MAKE} -C $(HOMEDIR)/business/bookmgrservice
	@cp $(HOMEDIR)/business/bookmgrservice/libbookmgrservice.so $(HOMEDIR)/lib

USERMGRSERVICE: UTILS MODEL DAO
	@cp -rf $(HOMEDIR)/business/usermgrservice/*.h $(HOMEDIR)/include/usermgrservice
	${MAKE} -C $(HOMEDIR)/business/usermgrservice
	@cp $(HOMEDIR)/business/usermgrservice/libusermgrservice.so $(HOMEDIR)/lib

COMPONENT:
	@cp -rf $(HOMEDIR)/component/*.h $(HOMEDIR)/include/component
	${MAKE} -C $(HOMEDIR)/component
	@cp $(HOMEDIR)/component/libcomponent.so $(HOMEDIR)/lib

TESTCLIENT: COMPONENT
	${MAKE} -C $(HOMEDIR)/test/client

TEST: BOOKMGRSERVICE UTILS MODEL DAO
	${MAKE} -C $(HOMEDIR)/test/bookmanagertest
	${MAKE} -C $(HOMEDIR)/test/usermanagertest

ECHO:
	echo $(DynamicLib)

.PHONY : clean
clean: 
	@${MAKE} clean -C $(HOMEDIR)/utils
	@${MAKE} clean -C $(HOMEDIR)/business/model
	@${MAKE} clean -C $(HOMEDIR)/business/dao
	@${MAKE} clean -C $(HOMEDIR)/business/bookmgrservice
	@${MAKE} clean -C $(HOMEDIR)/business/usermgrservice
	@${MAKE} clean -C $(HOMEDIR)/test/bookmanagertest
	@${MAKE} clean -C $(HOMEDIR)/test/usermanagertest
	@${MAKE} clean -C $(HOMEDIR)/test/client
	@${MAKE} clean -C $(HOMEDIR)/component
	@rm -rf $(HOMEDIR)/lib/*.so
	@rm -rf $(HOMEDIR)/build-BookManagerClient-Desktop_Qt_5_12_10_GCC_64bit-Debug
