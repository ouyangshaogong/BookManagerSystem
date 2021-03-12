#ifndef __LEND_LIST_DAT_IMPL__
#define __LEND_LIST_DAT_IMPL__

#include "LendListDao.h"
#include "TableLendList.h"
#include "SQLConnection.h"
#include "common.h"
#include "IDMaker.h"

#define LENDBOOK 0
#define BACKBOOK 1

class LendListDaoImpl: public LendListDao
{

public:
    LendListDaoImpl();
    ~LendListDaoImpl(){};
    
    virtual int AddLendData(TableLendList &bookInfo) throw (SQLException);
    virtual int DeleteLendDataByField(const vector<FieldCond> &vecfieldCond) throw (SQLException);
    virtual int DeleteAllLendData() throw (SQLException);
    virtual int UpdateLendDataByField(const vector<FieldCond> &setFieldCond, const vector<FieldCond> &vecFieldCond) throw (SQLException);
    virtual int QueryLendDataByField(const vector<FieldCond> &vecfieldCond, list<vector<string> > &listBookInfo) throw (SQLException);
    virtual int QueryLendDataByUserIDAndBookID(const string &strUserID, const string &strBookID, TableLendList &lendList) throw (SQLException);
    virtual int DeleteLendByUserIDAndBookID(const string &strUserID, const string &strBookID) throw (SQLException);
    virtual int UpdateBackDateByUserIDAndBookID(const string &strUserID, const string &strBookID, const string &backDate) throw (SQLException);
private:
    MYSQL *m_pMySQLConn;
    IDMaker m_nIDMaker;
};

#endif //__LEND_LIST_DAT_IMPL__