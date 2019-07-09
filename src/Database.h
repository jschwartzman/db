/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Database.h
 *
 *  DESCRIPTION:
 *      This encapsulates the MySQL Connector/C++ (interface).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/08/2019    John Schwartzman
 *
 *****************************************************************************/
#ifndef DATABASE_H_ //********************************************************
#define DATABASE_H_ //********************************************************

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

class Database
{
private:
    std::string         _sUser;
    std::string         _sPassword;
    std::string         _sAddress;
    std::string         _sSchema;
    std::string         _sContinent;
    std::string         _sSelectStmt;
    sql::Driver*        _pDriver;
    sql::Connection*    _pConnection;
    sql::Statement*     _pStatement;
    sql::ResultSet*     _pResultSet;

public:
    Database(std::string sUser,
             std::string sPassword,
             std::string sAddress = "tcp://127.0.0.1:3306",
             std::string sSchema = "world",
             std::string sContinent = "North America") : _sUser(sUser),
                                                         _sPassword(sPassword),
                                                         _sAddress(sAddress),
                                                         _sSchema(sSchema),
                                                         _sContinent(sContinent)
    {
        _pDriver = get_driver_instance();
        _pConnection = _pDriver->connect(_sAddress, _sUser, _sPassword);
        _pConnection->setSchema(_sSchema);
        _pStatement = _pConnection->createStatement();
    }
    ~Database()
    {
        delete _pResultSet;
        delete _pStatement;
        delete _pConnection;
    }
    void setContinent(std::string sContinent)
    {
        _sContinent = sContinent;
        _sSelectStmt = "SELECT country.name, city.name,"
                       " country.HeadOfState, country.Population"
                       " FROM country, city"
                       " WHERE country.Continent = '" +
                       _sContinent +
                       "' AND country.capital = city.id"
					   " AND country.population > 10000000"
                       " ORDER BY country.name";
    }
    sql::ResultSet*  getResultSet()  { return _pResultSet;  }
    sql::Connection* getConnection() { return _pConnection; }
    sql::Statement*  getStatement()  { return _pStatement;  }
    const std::string getContinent() { return _sContinent;  }
    std::string getSelectStatement() { return _sSelectStmt; }
    void setSelectStatement(std::string sSelectStmt)
    {
        _sSelectStmt = sSelectStmt;
    }
    sql::ResultSet* executeQuery()
    {
        return _pResultSet = _pStatement->executeQuery(_sSelectStmt);
    }
    sql::ResultSet* executeQuery(const std::string sStatement, 
								 bool bDisplay = false)
    {
        return _pResultSet = _pStatement->executeQuery(sStatement);
    }
    long queryHasRecords(const std::string sQuery, 
                         bool bDisplay = false);
    long executeAndDisplay(std::string sContinent = "North America", 
                           bool bDisplay = false);
    long executePlaceQuery(std::string sPlaceQuery,
                           std::string sPlaceLabel = "", 
                           bool bDisplay = false);
    void execute(const std::string sStatement, bool bDisplay = false);
    long executeCountQuery(const std::string sQuery, 
                           bool bDisplay = false);
};

#endif //*************************** DATABASE_H *****************************