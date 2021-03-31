SHELL = /bin/bash

HOMEDIR=/mnt/hgfs/BOOKDEVELOPMENT/BookManagerSystem

ALLLIBS: SUTILS MSGPROTO TASKMGR MSGCOMCLIENT MSGCOMSERVER MODEL DAO BOOKMGRSERVICE USERMGRSERVICE MVCFRAME TESTCLIENT TEST ECHO

SUTILS:
	@cp -rf $(HOMEDIR)/utils/*.h $(HOMEDIR)/include/utils
	${MAKE} -C $(HOMEDIR)/utils
	@cp $(HOMEDIR)/utils/libbookutils.so $(HOMEDIR)/lib

MSGPROTO:
	@cp -rf $(HOMEDIR)/component/msgproto/*.h $(HOMEDIR)/include/component/msgproto
	${MAKE} -C $(HOMEDIR)/component/msgproto
	@cp $(HOMEDIR)/component/msgproto/libmsgproto.so $(HOMEDIR)/lib

TASKMGR:
	@cp -rf $(HOMEDIR)/component/taskmgr/*.h $(HOMEDIR)/include/component/taskmgr
	${MAKE} -C $(HOMEDIR)/component/taskmgr
	@cp $(HOMEDIR)/component/taskmgr/libtaskmgr.so $(HOMEDIR)/lib

MSGCOMCLIENT:MSGPROTO TASKMGR
	@cp -rf $(HOMEDIR)/component/msgcomclient/*.h $(HOMEDIR)/include/component/msgcomclient
	${MAKE} -C $(HOMEDIR)/component/msgcomclient
#	@cp $(HOMEDIR)/component/msgcomclient/libmsgcomclient.so $(HOMEDIR)/lib

MSGCOMSERVER:MSGPROTO
	${MAKE} -C $(HOMEDIR)/component/msgcomserver


MODEL:
	@cp -rf $(HOMEDIR)/business/model/*.h $(HOMEDIR)/include/model
	${MAKE} -C $(HOMEDIR)/business/model
	@cp $(HOMEDIR)/business/model/libbookmodel.so $(HOMEDIR)/lib

DAO: SUTILS
	@cp -rf $(HOMEDIR)/business/dao/*.h $(HOMEDIR)/include/dao
	${MAKE} -C $(HOMEDIR)/business/dao
	@cp $(HOMEDIR)/business/dao/libbookmgrdao.so $(HOMEDIR)/lib

BOOKMGRSERVICE: SUTILS MODEL DAO
	@cp -rf $(HOMEDIR)/business/bookmgrservice/*.h $(HOMEDIR)/include/bookmgrservice
	${MAKE} -C $(HOMEDIR)/business/bookmgrservice
	@cp $(HOMEDIR)/business/bookmgrservice/libbookmgrservice.so $(HOMEDIR)/lib

USERMGRSERVICE: SUTILS MODEL DAO
	@cp -rf $(HOMEDIR)/business/usermgrservice/*.h $(HOMEDIR)/include/usermgrservice
	${MAKE} -C $(HOMEDIR)/business/usermgrservice
	@cp $(HOMEDIR)/business/usermgrservice/libusermgrservice.so $(HOMEDIR)/lib

MVCFRAME:
	@cp -rf $(HOMEDIR)/component/mvcframe/*.h $(HOMEDIR)/include/component/mvcframe
	${MAKE} -C $(HOMEDIR)/component/mvcframe
	@cp $(HOMEDIR)/component/mvcframe/libmvcframe.so $(HOMEDIR)/lib

TESTCLIENT: MVCFRAME
	${MAKE} -C $(HOMEDIR)/test/client

TEST: BOOKMGRSERVICE SUTILS MODEL DAO
	${MAKE} -C $(HOMEDIR)/test/bookmanagertest
	${MAKE} -C $(HOMEDIR)/test/usermanagertest

ECHO:
	@echo "compile success"

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
	@${MAKE} clean -C $(HOMEDIR)/component/msgproto
	@${MAKE} clean -C $(HOMEDIR)/component/taskmgr
	@${MAKE} clean -C $(HOMEDIR)/component/msgcomclient
	@${MAKE} clean -C $(HOMEDIR)/component/msgcomserver
	@${MAKE} clean -C $(HOMEDIR)/component/mvcframe
	@rm -rf $(HOMEDIR)/lib/*.so
	@rm -rf $(HOMEDIR)/build-BookManagerClient-Desktop_Qt_5_12_10_GCC_64bit-Debug
