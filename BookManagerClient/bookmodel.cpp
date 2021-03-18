#include "bookmodel.h"

void BookModel::SetBookID(int nBookID)
{
    this->m_nBookId = nBookID;
}

int BookModel::GetBookID()
{
    return m_nBookId;
}

void BookModel::SetClassID(int nClassID)
{
    this->m_nClassID = nClassID;
}

int BookModel::GetClassID()
{
    return m_nClassID;
}

void BookModel::SetIntroduction(string strIntroduction)
{
    this->m_strIntroduction = strIntroduction;
}

string BookModel::GetIntroduction()
{
    return m_strIntroduction;
}

void BookModel::SetName(string strName)
{
    this->m_strName = strName;
}

string BookModel::GetName()
{
    return m_strName;
}

void BookModel::SetAuthor(string strAuthor)
{
    this->m_strAuthor = strAuthor;
}

string BookModel::GetAuthor()
{
    return m_strAuthor;
}

void BookModel::SetPublish(string strPublish)
{
    this->m_strPublish = strPublish;
}

string BookModel::GetPublish()
{
    return m_strPublish;
}

void BookModel::SetISBN(string strISBN)
{
    this->m_strISBN = strISBN;
}

string BookModel::GetISBN()
{
    return m_strISBN;
}

void BookModel::SetLanguage(string strLanguage)
{
    this->m_strLanguage = strLanguage;
}

string BookModel::GetLanguage()
{
    return m_strLanguage;
}

void BookModel::SetPrice(int nPrice)
{
    this->m_nPrice = nPrice;
}

int BookModel::GetPrice()
{
    return m_nPrice;
}

void BookModel::SetPubDate(string strPubDate)
{
    this->m_strPubDate = strPubDate;
}

string BookModel::GetPubDate()
{
    return m_strPubDate;
}

void BookModel::SetNumber(int nNumber)
{
    this->m_nNumber = nNumber;
}

int BookModel::GetNumber()
{
    return m_nNumber;
}
