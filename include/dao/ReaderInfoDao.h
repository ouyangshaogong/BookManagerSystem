#ifndef __READER_INFO_DAO__
#define __READER_INFO_DAO__

class ReaderInfoDao
{

public:
    virtual int Add(TblBookInfo &bookInfo) throw (SQLException) = 0;
    virtual int DeleteBookByField(const string &fieldName, const string &fieldValue) throw (SQLException) = 0;
    virtual int DeleteBookAllBook() throw (SQLException) = 0;
    virtual int UpdateBookInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond) throw (SQLException) = 0;
    virtual int QueryBookByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException) = 0;
};

#endif