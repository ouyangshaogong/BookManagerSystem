#ifndef __LEND_LIST_DAO__
#define __LEND_LIST_DAO__

#include "TableLendList.h"
#include "SQLException.h"


class LendListDao
{

public:
    virtual int AddLendData(TableLendList &bookInfo) throw (SQLException) = 0;
    virtual int DeleteLendDataByField(const FieldCond &fieldCond) throw (SQLException) = 0;
    virtual int DeleteAllLendData() throw (SQLException) = 0;
    virtual int UpdateLendDataByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond) throw (SQLException) = 0;
    virtual int QueryLendDataByField(const vector<FieldCond> &vecfieldCond, list<vector<string> > &listBookInfo) throw (SQLException) = 0;
    virtual int QueryLendDataByUserIDAndBookID(const int nUserID, const int nBookID, TableLendList &lendList) throw (SQLException) = 0;
};

#endif