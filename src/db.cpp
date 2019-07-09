/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      db.cpp
 *
 *  DESCRIPTION:
 *      A program to exercise database access.
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/08/2019    John Schwartzman
 *
 *****************************************************************************/
#include <stdlib.h>             // defines EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include "Database.h"
#include "Place.h"
#include "Terminal.h"

using namespace std;

int main(int argc, char *argv[])
{
  Terminal::clearScreen();
  try
  {
    // When pDB goes out of scope, the Database object pointed to
    // by pDB will be automatically deleted.
    // execute a SELECT statement
    unique_ptr <Database> pDB(new Database("worlduser", "worlduser123"));

    Terminal::displayCaption("You're now viewing four COLUMNs of an "
                             "INNER JOIN of the country TABLE and the "
                             "city TABLE.\nNote the various conditions "
                             "in the WHERE clause.\n\n");
        pDB->executeAndDisplay("North America", true);
    Terminal::waitForUserInput();

    // execute a SELECT statement
    Terminal::displayCaption("You're about to ask the database if the "
                             "country TABLE\nhas any ROWS where the "
                             "HeadOfState COLUMN contains "
                             "George W. Bush.\n\n");
    string sTestHeadOfState = "SELECT HeadOfState FROM country WHERE "
                              "HeadOfState LIKE 'George%Bush'";
    if (pDB->queryHasRecords(sTestHeadOfState, true))                              
    {
      Terminal::displayCaption("\n\n\nGeorge is the president. "
                               "This database is way out of date.\n"
                               "Forgive me for the UPDATE statement "
                               "I'm about to execute...\n\n");
      // execute an UPDATE statement
      string sStmt = "UPDATE country "
                     "SET HeadOfState = 'Donald Trump' "
                     "WHERE HeadOfState = 'George W. Bush'";
      pDB->execute(sStmt, true);
    }
    else
    {
      Terminal::displayCaption("\n\n\nNo records found. "
                               "The Donald must be president. "
                               "Let's change that!\nYou'll "
                               "use an UPDATE statement to restore "
                               "the database's previous HeadOfState.\n\n");
      // execute an UPDATE statement
      string sStmt = "UPDATE country "
                     "SET HeadOfState = 'George W. Bush' "
                     "WHERE HeadOfState = 'Donald Trump'";
      pDB->execute(sStmt, true);
    }
    Terminal::waitForUserInput();

    Terminal::displayCaption("Now see who's president of the US.\n\n");

    // execute a SELECT statement
    pDB->executeAndDisplay("North America", true);
    Terminal::waitForUserInput();

    Terminal::displayCaption("Here are a couple of count queries.\n"
                             "Count queries return a ResultSet "
                             "containing a single element.\n"
                             "That element contains a long integer.\n\n");
    // execute a SELECT COUNT statement
    string sCountQuery = "SELECT COUNT(HeadOfState) FROM country";
    pDB->executeCountQuery(sCountQuery, true);

    Terminal::displayNewLines(2);
    // execute a SELECT COUNT statement
    sCountQuery = "SELECT COUNT(DISTINCT HeadOfState) FROM country";
    pDB->executeCountQuery(sCountQuery, true);

    Terminal::displayCaption("\n\nNote that the number of DISTINCT (unique) "
                             "heads of state is less\nthan the total number "
                             "of heads of state.\nSome heads of state are "
                             "leaders of more than one country.\n\n");

    Terminal::waitForUserInput();

    Terminal::displayCaption("Execute an INSERT statment with multiple (2) "
                             "rows.\nYou can also do this with two "
                             "separate INSERT statements\n\n");
    // execute an INSERT statement with multiple rows
    string sStmt = "INSERT INTO city (name, countrycode, district, population) "
                   "VALUES "
                   "('Columbia', 'USA', 'Maryland', 100000), "
                   "('Ellicott City', 'USA', 'Maryland', 85000)";

    pDB->execute(sStmt, true);

    Terminal::displayCaption("\n\n\nExecute a SELECT statement to see what "
                             "ROWs you've inserted into the city TABLE.\n\n");
    // execute a SELECT statement to see what you've inserted
    sStmt = "SELECT name, district, countrycode, population FROM city "
            "WHERE district = 'Maryland'";
    pDB->executePlaceQuery(sStmt, "Maryland Cities", true);
    Terminal::displayNewLines();

    Terminal::displayCaption("\nNow execute a DELETE statement to remove "
                             "the rows you just inserted into the city."
                             "TABLE\n\n");
    // execute a DELETE statement to undo what you just inserted
    sStmt = "DELETE FROM city WHERE "
            "name = 'Columbia' OR name = 'Ellicott City'";
    pDB->execute(sStmt, true);
    Terminal::displayNewLines();

    // execute a SELECT statment to see what you've deleted
    Terminal::displayCaption("\nHere's another SELECT statement so "
                             "you can see what ROWs you've deleted "
                             "from the city TABLE.\n\n");
    sStmt = "SELECT name, district, countrycode, population FROM city "
            "WHERE district = 'Maryland'";
    pDB->executePlaceQuery(sStmt, "Maryland Cities", true);
    Terminal::waitForUserInput();
    
    //***********************************************************************
    // This following code shows how to execute the equivalent of
    // pDB->executeAndDisplay() with all of the gory details shown.
    //***********************************************************************
    Terminal::displayCaption("Here's another four column SELECT statement."
                             "\nHere you use all of the separate components "
                             "of the Database class to display your results."
                             "\n\n");
    Place* pPlace;
    string sContinent  = "Europe"; 
    string sSelectStmt = "SELECT country.name, city.name,"
                         " country.HeadOfState, country.Population"
                         " FROM country, city"
                         " WHERE country.Continent = '" + sContinent +
                         "' AND country.capital = city.id "
                         " AND country.population > 10000000"
                         " ORDER BY country.name";
    pDB->setSelectStatement(sSelectStmt);
    Terminal::displayStatement(sSelectStmt);
    Terminal::displayLabel("Continent", sContinent);
    sql::ResultSet* pRS = pDB->executeQuery();
    Place::clearCount();
    
    while (pRS->next())
    {
      pPlace= new Place(pRS->getString(1),
                        pRS->getString(2),
                        pRS->getString(3),
                        pRS->getUInt64(4));
      pPlace->display();
    }
    Terminal::displayCount(Place::getCount());
    //***********************************************************************

  Terminal::displayNewLines();
  }
  catch(const sql::SQLException &e)
  {
    cerr << "SQL EXCEPTION:\n";
    cerr << "code:  " << e.getErrorCode() << endl;
    cerr << "state: " << e.getSQLState() << endl;
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }
  catch (const std::exception &e)
  {
    cerr << "EXCEPTION:\n";
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}