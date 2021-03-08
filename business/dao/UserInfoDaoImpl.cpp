#include "UserInfoDaoImpl.h"

UserInfoDaoImpl::UserInfoDaoImpl()
{
    m_pMySQLConn = SQLConnection::Instance()->GetConnection();
}

int UserInfoDaoImpl::AddUser(TblUserInfo &userInfo) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "INSERT INTO tbl_userinfo VALUES (";
        strSQL += to_string(userInfo.GetUserID()) + ",";
        strSQL += to_string(userInfo.GetReaderID()) + ",";
        strSQL += "'" + userInfo.GetPhone() + "',";
        strSQL += "'" + userInfo.GetUserName() + "',";
        strSQL += "'" + userInfo.GetSex() + "',";
        strSQL += "'" + userInfo.GetBirth() + "',";
        strSQL += "'" + userInfo.GetAddress() + "',";
        strSQL += to_string(userInfo.GetUserType()) + ")";

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

int UserInfoDaoImpl::DeleteUserByUserID(const string &fieldName, const string &fieldValue) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "delete from tbl_userinfo where ";
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

int UserInfoDaoImpl::DeleteAllUser() throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "delete from tbl_userinfo";

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

int UserInfoDaoImpl::UpdateUserInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "update tbl_userinfo set ";

        for (size_t i = 0; i < setFieldCond.size(); i++)
        {

            strSQL += setFieldCond[i].fieldName + " = '" + setFieldCond[i].fieldValue + "',";   
        }

        if (strSQL[strSQL.length() - 1] == ',')
        {
            strSQL = strSQL.substr(0, strSQL.length() - 1);
        }

        strSQL += " where " + fieldCond.fieldName + " = " + fieldCond.fieldValue;
        

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

int UserInfoDaoImpl::QueryUserByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException)
{
    string strSQL;
    MYSQL_RES* result;
    MYSQL_FIELD* field = NULL;
    MYSQL_ROW row;

    try
    {
        strSQL = "select * from tbl_userinfo where ";
        strSQL += fieldCond.fieldName + " = '" + fieldCond.fieldValue + "'";

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