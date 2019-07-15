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
 *      07/12/2019    John Schwartzman
 *
 *****************************************************************************/
#ifndef DATABASE_H_ //********************************************************
#define DATABASE_H_ //********************************************************

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class Database
{
private:
    std::string      _sUser;         // user name
    std::string      _sPassword;     // user password
    std::string      _sAddress;      // user ip address - default localhost
    std::string      _sSchema;       // database - default world
    sql::Driver*     _pDriver;
    sql::Connection* _pConnection;
    sql::Statement*  _pStatement;
    sql::ResultSet*  _pRS;

public:
    Database(std::string sUser,      // constructor
             std::string sPassword,
             std::string sAddress = "tcp://127.0.0.1:3306", //localhost
             std::string sSchema = "world") : _sUser(sUser),
                                              _sPassword(sPassword),
                                              _sAddress(sAddress),
                                              _sSchema(sSchema),
                                              _pRS(nullptr)
    {
        _pDriver = get_driver_instance();
        _pConnection = _pDriver->connect(_sAddress, _sUser, _sPassword);
        _pConnection->setSchema(_sSchema);
        _pStatement = _pConnection->createStatement();
    }
    ~Database()                     // destructor
    {
        if (_pRS != nullptr) delete _pRS;
        delete _pStatement;
        delete _pConnection;
    }
    sql::ResultSet* executeQuery(const std::string sSQLStatement);
    long queryHasRecords(const std::string sQuery, bool bDisplay = false);
    bool execute(const std::string sStatement, bool bDisplay = false);
    long executeCountQuery(const std::string sQuery, bool bDisplay = false);
    void deleteResultSet();  // not necessary - may reduce memory usage 
 };

#endif //*************************** DATABASE_H *****************************