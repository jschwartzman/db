/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Database.h
 *
 *  DESCRIPTION:
 *      This class encapsulates the MySQL Connector/C++ (interface).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/23/2019    John Schwartzman
 *
 *****************************************************************************/
#ifndef DATABASE_H_ //********************************************************
#define DATABASE_H_ //********************************************************

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>  // handles sql::SQLException; used by clients

class Database
{
private:
    sql::Driver*     _pDriver;
    sql::Connection* _pConnection;
    sql::Statement*  _pStatement;
    sql::ResultSet*  _pRS;

public:
    Database(std::string sUser,      // constructor
             std::string sPassword,
             std::string sAddress = "tcp://127.0.0.1:3306", //localhost
             std::string sSchema = "world") : _pRS(nullptr)
    {
        _pDriver = get_driver_instance();
        _pConnection = _pDriver->connect(sAddress, sUser, sPassword);
        _pConnection->setSchema(sSchema);
        _pStatement = _pConnection->createStatement();
    }
    ~Database()                     // destructor
    {
        if (_pRS != nullptr) delete _pRS;
        delete _pStatement;
        delete _pConnection;
    }
    sql::ResultSet* executeQuery(const std::string sStatement,
                                 bool bDisplay = true);
    long queryHasRecords(const std::string sQuery,   bool bDisplay = true);
    bool execute(const std::string sStatement,       bool bDisplay = true);
    long executeCountQuery(const std::string sQuery, bool bDisplay = true);
    void deleteResultSet();  // not necessary - may reduce memory usage 
 };

#endif //*************************** DATABASE_H *****************************