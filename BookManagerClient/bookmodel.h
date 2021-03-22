#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include "common.h"

#define BOOK_ATTR_NAME 0
#define BOOK_ATTR_CLASS 7
#define BOOK_ATTR_AUTHOR 1
#define BOOK_ATTR_PUBLISH 2
#define BOOK_ATTR_ISBN 3
#define BOOK_ATTR_INTRODUCT 9
#define BOOK_ATTR_LANGUAGE 4
#define BOOK_ATTR_PRICE 5
#define BOOK_ATTR_PUBDATE 6
#define BOOK_ATTR_NUMBER 8

class BookModel
{
public:
    BookModel(){};

    void SetBookID(int nBookID);
    int GetBookID();

    void SetClassID(int nClassID);
    int GetClassID();

    void SetName(string strName);
    string GetName();

    void SetAuthor(string strAuthor);
    string GetAuthor();

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

    bool operator < (const BookModel& bookData) const
    {
        return this->m_nBookId < bookData.m_nBookId;
    }

private:
    int m_nBookId;
    int m_nClassID;
    string m_strName;
    string m_strAuthor;
    string m_strPublish;
    string m_strISBN;
    string m_strIntroduction;
    string m_strLanguage;
    int m_nPrice;
    string m_strPubDate;
    int m_nNumber;
};

#endif // BOOKMODEL_H
