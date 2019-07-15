/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Database.cpp
 *
 *  DESCRIPTION:
 *      This encapsulates the MySQL Connector/C++ (implementation).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/12/2019    John Schwartzman
 *
 *****************************************************************************/
#include "Terminal.h"
#include "Database.h"

using namespace std;

bool Database::execute(const string sStatement, bool bDisplay)
{
    if (bDisplay)
    {
        Terminal::displayStatement(sStatement);
    }
    return _pStatement->execute(sStatement);
}

sql::ResultSet* Database::executeQuery(const std::string sSQLStatement)
{
        if (_pRS != nullptr)
        {
            delete _pRS;
            _pRS = nullptr;
        }
        _pRS = _pStatement->executeQuery(sSQLStatement);
        return _pRS;
}

long Database::queryHasRecords(const string sQuery, bool bDisplay)
{
    if (bDisplay)
    {
        Terminal::displayStatement(sQuery);
    }

    sql::ResultSet* pRS = _pStatement->executeQuery(sQuery);
    long nCount = 0;

    while (pRS->next())
    {
        ++nCount;
    }

    if (bDisplay)
    {
        Terminal::displayCount(nCount);
    }

    delete pRS;
    return nCount;
}

long Database::executeCountQuery(const string sQuery, bool bDisplay)
{
    if (bDisplay)
    {
        Terminal::displayStatement(sQuery);
    }

    sql::ResultSet* pRS = _pStatement->executeQuery(sQuery);
    pRS->next();                        // move into the ResultSet
    long nCount = pRS->getUInt64(1);    // and get its first and only record 
    
    if (bDisplay)
    {
        Terminal::displayCount(nCount);
    }

    delete pRS;
    return nCount;
}

void Database::deleteResultSet()  // not necessary - may reduce memory usage
{ 
    if (_pRS != nullptr) 
    {
        delete _pRS;
        _pRS = nullptr;
    }
}

//***************************************************************************
