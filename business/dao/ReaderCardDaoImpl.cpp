#include "ReaderCardDaoImpl.h"

ReaderCardDaoImpl::ReaderCardDaoImpl()
{
    m_pMySQLConn = SQLConnection::Instance()->GetConnection();
}

int ReaderCardDaoImpl::AddReaderCard(TableReaderCard &readerCard) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "INSERT INTO tbl_readercard VALUES (";
        strSQL += to_string(readerCard.GetReaderID()) + ",";
        strSQL += "'" + readerCard.GetUserName() + "',";
        strSQL += "'" + readerCard.GetPasswd() + "')";

        //cout << "UserInfoDaoImpl::AddUser>>"  << strSQL <<endl;
        if (!SQLConnection::Instance()->ExecuteSQL(strSQL))
        {
            return FAIL;
        }
    }
    catch(const SQLException& e)
    {
        std::cout << e.what() << endl;
        return FAIL;
    }

    return OK;
}

int ReaderCardDaoImpl::DeleteReaderCardByReaderID(const string &strReaderID) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "delete from tbl_readercard where reader_id";
        strSQL += " = " + strReaderID;

        SQLConnection::Instance()->ExecuteSQL(strSQL);
    }
    catch(const SQLException& e)
    {
        std::cout << e.what() << endl;
        return FAIL;
    }

    return OK;
}

int ReaderCardDaoImpl::DeleteAllReaderCard() throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "delete from tbl_readercard";

        if (!SQLConnection::Instance()->ExecuteSQL(strSQL))
        {
            return FAIL;
        }
    }
    catch(const SQLException& e)
    {
        std::cout << e.what() << endl;
        return FAIL;
    }

    return OK;
}

int ReaderCardDaoImpl::UpdateReaderCard(const FieldCond &setFieldCond, const FieldCond &fieldCond) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "update tbl_readercard set ";
        strSQL += setFieldCond.fieldName + " = '" + setFieldCond.fieldValue + "'";
        strSQL += " where ";
        if (fieldCond.fieldName == "reader_id")
        {
            strSQL += fieldCond.fieldName + " = " + fieldCond.fieldValue;
        }
        else
        {
            strSQL += fieldCond.fieldName + " = '" + fieldCond.fieldValue + "'";
        }
        
        
        if (!SQLConnection::Instance()->ExecuteSQL(strSQL))
        {
            return FAIL;
        }
    }
    catch(const SQLException& e)
    {
        std::cout << e.what() << endl;
        return FAIL;
    }

    return OK;
}

int ReaderCardDaoImpl::QueryReaderCardByUserName(const string &strUserName, TableReaderCard &readerCard) throw (SQLException)
{
    try
    {
        FieldCond fieldCond;
        fieldCond.fieldName = "username";
        fieldCond.fieldValue = strUserName;
        list<vector<string> > listBookInfo;
        if (OK != QueryReaderCardByField(fieldCond, listBookInfo))
        {
            return FAIL;
        }

        if (!listBookInfo.empty())
        {
            readerCard.SetReaderID(atoi((*listBookInfo.begin())[1].c_str()));
            readerCard.SetUserName((*listBookInfo.begin())[1]);
            readerCard.SetPasswd((*listBookInfo.begin())[2]);
        }
        else
        {
            return FAIL;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }

    return OK;
    
}

int ReaderCardDaoImpl::QueryReaderCardByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException)
{
    string strSQL;
    MYSQL_RES* result;
    MYSQL_FIELD* field = NULL;
    MYSQL_ROW row;

    try
    {
        strSQL = "select * from tbl_readercard where ";
        if (fieldCond.fieldName == "reader_id")
        {
            strSQL += fieldCond.fieldName + " = " + fieldCond.fieldValue;
        }
        else
        {        
            strSQL += fieldCond.fieldName + " = '" + fieldCond.fieldValue + "'";
        }
        

        bool flag = SQLConnection::Instance()->ExecuteSQL(strSQL);
        if (flag)
        {
            result = mysql_store_result(m_pMySQLConn);
            if (result == NULL)
            {
                cout << "ReaderCardDaoImpl::QueryReaderCardByField>>Get Result Fail!" << endl;
            }

            for(int i=0; i<mysql_num_fields(result); i++)
            {         
                field = mysql_fetch_field_direct(result,i);
                //cout << field->name << "\t\t";
            }
            //cout << endl;          
                   
            row = mysql_fetch_row(result);  

            while (row != NULL)
            {
                vector<string> setRecord;
                for(int i=0; i<mysql_num_fields(result); i++)
                {              
                    setRecord.push_back(row[i]);
                    //cout << row[i] << "\t\t";                                         
                }              
                //cout << endl;

                listBookInfo.push_back(setRecord);
                row = mysql_fetch_row(result);
            }          
        }
        
    }
    catch(const SQLException& e)
    {
        std::cout << e.what() << endl;
        return FAIL;
    }

    return OK;
}


