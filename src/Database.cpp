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
 *      07/07/2019    John Schwartzman
 *
 *****************************************************************************/
#include "Database.h"
#include "Place.h"
#include "Terminal.h"

using namespace std;
using namespace utility;

long Database::executeAndDisplay(string sContinent, bool bDisplay)
{
    setContinent(sContinent);

    if (bDisplay)
    {
        Terminal::displayStatement(getSelectStatement());
    }
    _pResultSet = executeQuery();
    Terminal::displayLabel("Continent", sContinent);
    return Place::display(_pResultSet, bDisplay);
}

long Database::executePlaceQuery(string sPlaceQuery, 
                                 string sPlaceLabel, 
                                 bool bDisplay)
{   
    if (bDisplay)
    {
        Terminal::displayStatement(sPlaceQuery);
    }
    setSelectStatement(sPlaceQuery);
    _pResultSet = executeQuery();
    if (!sPlaceLabel.empty())
    {
        Terminal::displayLabel("Place", sPlaceLabel);
    }
    return Place::display(_pResultSet, bDisplay);
}

void Database::execute(const string sStatement, bool bDisplay)
{
    if (bDisplay)
    {
        Terminal::displayStatement(sStatement);
    }
    _pStatement->execute(sStatement);
}

long Database::queryHasRecords(const string sQuery, bool bDisplay)
{
    if (bDisplay)
    {
        Terminal::displayStatement(sQuery);
    }

    long nCount(0);
    sql::ResultSet* pRS = _pStatement->executeQuery(sQuery);
    while (pRS->next())
    {
        nCount++;   // count the number of records returned
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

//***************************************************************************
