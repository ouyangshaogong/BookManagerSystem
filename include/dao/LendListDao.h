#ifndef __LEND_LIST_DAO__
#define __LEND_LIST_DAO__

#include "TableLendList.h"
#include "SQLException.h"


class LendListDao
{

public:
    virtual int AddLendData(TableLendList &bookInfo) throw (SQLException) = 0;
    virtual int DeleteLendDataByField(const vector<FieldCond> &vecfieldCond) throw (SQLException) = 0;
    virtual int DeleteAllLendData() throw (SQLException) = 0;
    virtual int UpdateLendDataByField(const vector<FieldCond> &setFieldCond, const vector<FieldCond> &vecFieldCond) throw (SQLException) = 0;
    virtual int QueryLendDataByField(const vector<FieldCond> &vecfieldCond, list<vector<string> > &listBookInfo) throw (SQLException) = 0;
    virtual int QueryLendDataByUserIDAndBookID(const string &strUserID, const string &strBookID, TableLendList &lendList) throw (SQLException) = 0;
    virtual int DeleteLendByUserIDAndBookID(const string &strUserID, const string &strBookID) throw (SQLException) = 0;
    virtual int UpdateBackDateByUserIDAndBookID(const string &strUserID, const string &strBookID, const string &backDate) throw (SQLException) = 0;
};

#endif