#include "BookInfoDaoImpl.h"

BookInfoDaoImpl::BookInfoDaoImpl()
{
    m_pMySQLConn = SQLConnection::Instance()->GetConnection();
}

int BookInfoDaoImpl::AddBook(TblBookInfo &bookInfo) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "INSERT INTO tbl_bookinfo VALUES (";
        strSQL += to_string(bookInfo.GetBookID()) + ",";
        strSQL += to_string(bookInfo.GetClassID()) + ",";
        strSQL += "'" + bookInfo.GetName() + "',";
        strSQL += "'" + bookInfo.GetAuther() + "',";
        strSQL += "'" + bookInfo.GetPublish() + "',";
        strSQL += "'" + bookInfo.GetISBN() + "',";
        strSQL += "'" + bookInfo.GetIntroduction() + "',";
        strSQL += "'" + bookInfo.GetLanguage() + "',";
        strSQL += to_string(bookInfo.GetPrice()) + ",";
        strSQL += "'" + bookInfo.GetPubDate() + "',";
        strSQL += to_string(bookInfo.GetNumber()) + ")";

        cout << "BookInfoDaoImpl::AddBook>>"  << strSQL <<endl;
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

int BookInfoDaoImpl::DeleteBook(const string &fieldName, const string &fieldValue) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "delete from tbl_bookinfo where ";
        strSQL += fieldName + " = '" + fieldValue + "'";

        SQLConnection::Instance()->ExecuteSQL(strSQL);
    }
    catch(const SQLException& e)
    {
        std::cout << e.what() << endl;
        return FAIL;
    }

    return OK;
}

int BookInfoDaoImpl::UpdateBook(const string &fieldName, const string &fieldValue, TblBookInfo &bookInfo) throw (SQLException)
{
    
}

int BookInfoDaoImpl::QueryBook(const string &fieldName, const string &fieldValue, list<vector<string> > &listBookInfo) throw (SQLException)
{
    string strSQL;
    MYSQL_RES* result;
    MYSQL_FIELD* field = NULL;
    MYSQL_ROW row;

    TblBookInfo bookInfo;

    try
    {
        strSQL = "select * from tbl_bookinfo where ";
        strSQL += fieldName + " = '" + fieldValue + "'";

        bool flag = SQLConnection::Instance()->ExecuteSQL(strSQL);
        if (flag)
        {
            result = mysql_store_result(m_pMySQLConn);
            if (result == NULL)
            {
                cout << "BookInfoDaoImpl::QueryBook>>Get Result Fail!" << endl;
            }

            for(int i=0; i<mysql_num_fields(result); i++)
            {         
                field = mysql_fetch_field_direct(result,i);
                cout << field->name << "\t\t";
            }
            cout << endl;          
                   
            row = mysql_fetch_row(result);  

            while (row != NULL)
            {
                vector<string> setRecord;
                for(int i=0; i<mysql_num_fields(result); i++)
                {              
                    setRecord.push_back(row[i]);
                    cout << row[i] << "\t\t";                                         
                }              
                cout << endl;

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

