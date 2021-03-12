#include "LendListDaoImpl.h"

LendListDaoImpl::LendListDaoImpl()
:m_nIDMaker(0)
{
    m_pMySQLConn = SQLConnection::Instance()->GetConnection();
}

int LendListDaoImpl::AddLendData(TableLendList &lendList) throw (SQLException)
{
    string strSQL;

    try
    {
        int nSerNum = m_nIDMaker.GenerateID();
        
        strSQL = "INSERT INTO tbl_lendlist VALUES (";
        strSQL += to_string(nSerNum) + ",";
        strSQL += to_string(lendList.GetUserID()) + ",";
        strSQL += to_string(lendList.GetBookID()) + ",";
        strSQL += "'" + lendList.GetLendDate() + "',";
        strSQL += "'" + lendList.GetBackDate() + "',";
        strSQL += to_string(lendList.GetLendState()) + ")";

        //cout << "LendListDaoImpl::AddLendData>>"  << strSQL <<endl;
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

int LendListDaoImpl::DeleteLendByUserIDAndBookID(const string &strUserID, const string &strBookID) throw (SQLException)
{
    try
    {
        vector<FieldCond> vecfieldCond;
        FieldCond fieldCond;
        fieldCond.fieldName = "user_id";
        fieldCond.fieldValue = strUserID;
        vecfieldCond.push_back(fieldCond);

        fieldCond.fieldName = "book_id";
        fieldCond.fieldValue = strBookID;
        vecfieldCond.push_back(fieldCond);

        if (OK != DeleteLendDataByField(vecfieldCond))
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

int LendListDaoImpl::DeleteLendDataByField(const vector<FieldCond> &vecfieldCond) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "delete from tbl_lendlist where ";
        for (size_t i = 0; i < vecfieldCond.size(); i++)
        {
            if(vecfieldCond[i].fieldName == "lend_back" 
            || vecfieldCond[i].fieldName == "back_back")
            {
                strSQL += vecfieldCond[i].fieldName + " = '" + vecfieldCond[i].fieldValue + "' and ";
            }
            else
            {
                strSQL += vecfieldCond[i].fieldName + " = " + vecfieldCond[i].fieldValue + " and ";
            }
        }

        strSQL = strSQL.substr(0, strSQL.length() - 4);

        SQLConnection::Instance()->ExecuteSQL(strSQL);
    }
    catch(const SQLException& e)
    {
        std::cout << e.what() << endl;
        return FAIL;
    }

    return OK;
}

int LendListDaoImpl::DeleteAllLendData() throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "delete from tbl_lendlist";

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

int LendListDaoImpl::UpdateBackDateByUserIDAndBookID(const string &strUserID, const string &strBookID, const string &backDate) throw (SQLException)
{
    try
    {
        vector<FieldCond> setFieldCond;
        FieldCond fieldCond;
        fieldCond.fieldName = "back_date";
        fieldCond.fieldValue = backDate;
        setFieldCond.push_back(fieldCond);

        vector<FieldCond> vecFieldCond;
        fieldCond.fieldName = "user_id";
        fieldCond.fieldValue = strUserID;
        vecFieldCond.push_back(fieldCond);

        fieldCond.fieldName = "book_id";
        fieldCond.fieldValue = strBookID;
        vecFieldCond.push_back(fieldCond);
        if (OK != UpdateLendDataByField(setFieldCond, vecFieldCond))
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

int LendListDaoImpl::UpdateLendDataByField(const vector<FieldCond> &setFieldCond, const vector<FieldCond> &vecFieldCond) throw (SQLException)
{
    string strSQL;

    try
    {
        strSQL = "update tbl_lendlist set ";

        for (size_t i = 0; i < setFieldCond.size(); i++)
        {
            if(setFieldCond[i].fieldName == "lend_back" 
            || setFieldCond[i].fieldName == "back_back")
            {
                strSQL += setFieldCond[i].fieldName + " = '" + setFieldCond[i].fieldValue + "',";
            }
            else
            {
                strSQL += setFieldCond[i].fieldName + " = " + setFieldCond[i].fieldValue + ",";
            }  
        }

        strSQL = strSQL.substr(0, strSQL.length() - 1);

        strSQL += " where ";
        for (size_t i = 0; i < vecFieldCond.size(); i++)
        {
            if(vecFieldCond[i].fieldName == "lend_back" 
            || vecFieldCond[i].fieldName == "back_back")
            {
                strSQL += vecFieldCond[i].fieldName + " = '" + vecFieldCond[i].fieldValue + "' and ";
            }
            else
            {
                strSQL += vecFieldCond[i].fieldName + " = " + vecFieldCond[i].fieldValue + " and ";
            }  
        }
        
        strSQL = strSQL.substr(0, strSQL.length() - 4);

        cout << "strSQL:" << strSQL << endl;
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

int LendListDaoImpl::QueryLendDataByUserIDAndBookID(const string &strUserID, const string &strBookID, TableLendList &lendList) throw (SQLException)
{
    try
    {
        vector<FieldCond> vecfieldCond;
        FieldCond fieldCond;
        fieldCond.fieldName = "user_id";
        fieldCond.fieldValue = strUserID;
        vecfieldCond.push_back(fieldCond);

        fieldCond.fieldName = "book_id";
        fieldCond.fieldValue = strBookID;
        vecfieldCond.push_back(fieldCond);

        list<vector<string> > listLendList;

        if (OK != QueryLendDataByField(vecfieldCond, listLendList))
        {
            return FAIL;
        }

        list<vector<string> >::iterator iter = listLendList.begin();
        lendList.SetSerNum(atoi((*iter)[0].c_str()));
        lendList.SetUserID(atoi((*iter)[1].c_str()));
        lendList.SetBookID(atoi((*iter)[2].c_str()));
        lendList.SetLendDate((*iter)[3].c_str());
        lendList.SetBackDate((*iter)[4].c_str());
        lendList.SetLendState(atoi((*iter)[5].c_str()));
    }
    catch(const SQLException& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }

    return OK;
    
}

int LendListDaoImpl::QueryLendDataByField(const vector<FieldCond> &vecfieldCond, list<vector<string> > &listBookInfo) throw (SQLException)
{
    string strSQL;
    MYSQL_RES* result;
    MYSQL_FIELD* field = NULL;
    MYSQL_ROW row;

    try
    {
        strSQL = "select * from tbl_lendlist where ";
        for (size_t i = 0; i < vecfieldCond.size(); i++)
        {
            if(vecfieldCond[i].fieldName == "lend_back" 
            || vecfieldCond[i].fieldName == "back_back")
            {
                strSQL += vecfieldCond[i].fieldName + " = '" + vecfieldCond[i].fieldValue + "'";
            }
            else
            {
                strSQL += vecfieldCond[i].fieldName + " = " + vecfieldCond[i].fieldValue + "";
            }
        }
        
        bool flag = SQLConnection::Instance()->ExecuteSQL(strSQL);
        if (flag)
        {
            result = mysql_store_result(m_pMySQLConn);
            if (result == NULL)
            {
                cout << "LendListDaoImpl::QueryLendDataByField>>Get Result Fail!" << endl;
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


