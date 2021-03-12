#ifndef __TABLE_BOOK_INFO__
#define __TABLE_BOOK_INFO__

#include "common.h"

class TblBookInfo 
{

public:
    TblBookInfo();
    
    void SetBookID(int nBookID);
    int GetBookID();

    void SetClassID(int nClassID);
    int GetClassID();

    void SetName(string strName);
    string GetName();

    void SetAuther(string strAuther);
    string GetAuther();

    void SetPublish(string strPublish);
    string GetPublish();

    void SetISBN(string strIDBN);
    string GetISBN();

    void SetIntroduction(string strIntroduction);
    string GetIntroduction();

    void SetLanguage(string strLanguage);
    string GetLanguage();

    void SetPrice(int nPrice);
    int GetPrice();

    void SetPubDate(string strPubDate);
    string GetPubDate();

    void SetNumber(int nNumber);
    int GetNumber();


private:
    int m_nBookId;
    int m_nClassID;
    string m_strName;
    string m_strAuther;
    string m_strPublish;
    string m_strISBN;
    string m_strIntroduction;
    string m_strLanguage;
    int m_nPrice;
    string m_strPubDate;
    int m_nNumber;

};

#endif