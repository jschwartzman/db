/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      db.cpp
 *
 *  DESCRIPTION:
 *      A SQL Tutorial program to exercise the Database class.
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/15/2019    John Schwartzman
 *
 *****************************************************************************/
#include <stdlib.h>             // defines EXIT_SUCCESS and EXIT_FAILURE
#include <cppconn/exception.h>  // handles sql::SQLException
#include "Database.h"           // encapsulates the Database Connection
#include "Place.h"              // utility for displaying ResultSets
#include "Language.h"           // utility for displaying ResultSets
#include "Terminal.h"           // screen writing utility
#include "StrStrmBuf.h"         // for text manipulation

using namespace std;
using namespace sql;
using namespace utility;        // for StrStrmBuf

int main(int argc, char *argv[])
{
  Terminal::resetAndClearScreen();
  try
  {
    // When pDB goes out of scope, the Database object pointed to
    // by pDB will be automatically deleted.
    unique_ptr <Database> pDB(new Database("worlduser", "worlduser123"));

    Terminal::displayLabel("A Gentle Introduction to SQL");
    Terminal::displayCaption("\n\nWelcome to a brief SQL tutorial.\n"
                             "Here you'll encounter a variety of annotated "
                             "SQL queries and statements using the world "
                             "database.\nIn one case you'll "
                             "alter the program's flow of control based on "
                             "the results of a query.\n\n"
                             "During this tutorial, you will be able to view "
                             "previous screens by using the mouse to scroll "
                             "your terminal up."
                             "\n\nRelax, sit back and enjoy.");
    Terminal::waitForUserInput();

    //******************************* Screen 1 ******************************
    Terminal::displayCaption("You're viewing four COLUMNs of an "
                             "INNER JOIN of the country TABLE and the "
                             "city TABLE.\nNote the various conditions "
                             "in the WHERE clause. You're asking to see "
                             "four specific\nCOLUMNs from two separate TABLEs "
                             "combining those ROWs in both tables where "
                             "every part\nof the WHILE clause is satisfied. "
                             "Note that the city TABLE has an id COLUMN.\n"
                             "The country TABLE doesn't have a COLUMN where "
                             "the capital city is saved by name. Instead,\n"
                             "the country.capital COLUMN holds the id "
                             "number of its capital city. We need to join\n"
                             "the country TABLE and the city TABLE together "
                             "in order to read a country's capital city.\n\n\n");

    string sSelectStmt = "SELECT country.name, city.name, "
                         "country.HeadOfState, country.Population\n"
                         "FROM country INNER JOIN city\n"
                         "WHERE country.Continent = 'North America' "
                         "AND country.capital = city.id AND "
                         "country.Population >= 1000000"
                         "\nORDER BY country.name";

    Terminal::displayStatement(sSelectStmt);
    Terminal::displayLabel("Continent", "North America");
    ResultSet* pRS = pDB->executeQuery(sSelectStmt);
    Place::display(pRS, true);
    pDB->deleteResultSet();
    Terminal::displayCaption("\n\nNOTE: You can change the statement shown "
                             "above so that it reads\n\"SELECT ... "
                             "FROM country, city WHERE ... \" "
                             "and it means the same thing.\n"
                             "Why did you get so few matches? You're only "
                             "looking for countries with populations\n"
                             "greater than 1 million.");
    Terminal::waitForUserInput();

    //******************************* Screen 2 ******************************
    Terminal::displayCaption("You're now asking the database if the "
                             "country TABLE\nhas any ROWs where the "
                             "HeadOfState COLUMN contains "
                             "George W. Bush.\nNote the use of the "
                             "wildcard character '%'. It will match any "
                             "number of characters.\nThe wildcard "
                             "character '_' will match any one "
                             "character.\nWe employ 'LIKE' instead of "
                             "'=' when using wildcards.\n\n\n");

    string sTestHeadOfState = "SELECT COUNT(HeadOfState) FROM country\nWHERE "
                              "HeadOfState LIKE 'George%Bush'";
    long nCount = pDB->executeCountQuery(sTestHeadOfState, true);
    if (nCount) // condition branch based on result of last COUNT query
    {
      StrStrmBuf ssb("\n\n\nAccording to the database, George is the "
                     "Head Of State of ");
      ssb << nCount << " countries.\nThis database is way out of date.\n"
                       "Forgive us for writing this next UPDATE statement!";
      Terminal::displayCaption(ssb);
      Terminal::displayNewLines(3);
      // execute an UPDATE statement
      string sStmt = "UPDATE country "
                     "SET HeadOfState = 'Donald Trump'\n"
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
                     "SET HeadOfState = 'George W. Bush'\n"
                     "WHERE HeadOfState = 'Donald Trump'";
      pDB->execute(sStmt, true);
    }
    Terminal::waitForUserInput();

    //******************************* Screen 3 ******************************
    Terminal::displayCaption("Now see who's president of the US.\nYou're "
                             "executing the same SQL query as last time\n\n");
    Terminal::displayStatement(sSelectStmt);
    // reexecute the SELECT statement we used earlier
    pRS = pDB->executeQuery(sSelectStmt);
    Terminal::displayLabel("Continent", "North America");
    Place::display(pRS, true);
    pDB->deleteResultSet();
    Terminal::waitForUserInput();

    //******************************* Screen 4 ******************************
    Terminal::displayCaption("Here are a couple more count queries.\n"
                             "Count queries return a ResultSet "
                             "containing a single element.\n"
                             "That element contains a long integer.\n\n\n");
    // execute a SELECT COUNT statement
    string sCountQuery = "SELECT COUNT(HeadOfState) FROM country";
    pDB->executeCountQuery(sCountQuery, true);

    Terminal::displayNewLines(3);
    // execute a SELECT COUNT statement
    sCountQuery = "SELECT COUNT(DISTINCT HeadOfState) FROM country";
    pDB->executeCountQuery(sCountQuery, true);

    Terminal::displayCaption("\n\nNote that the number of DISTINCT (unique) "
                             "heads of state is less\nthan the total number "
                             "of heads of state.\nThat is because some "
                             "heads of state are leaders of more \n"
                             "than one country. DISTINCT removes "
                             "duplicates.\n\n");

    Terminal::waitForUserInput();

    //******************************* Screen 5 ******************************
    Terminal::displayCaption("Execute an INSERT statment with multiple "
                             "rows.\nYou can achieve the same results " 
                             "using two separate INSERT statements\n\n");

    // execute an INSERT statement with multiple rows
    string sStmt = "INSERT INTO city (name, countrycode, district, population) "
                   "VALUES\n"
                   "('Columbia',      'USA', 'Maryland', 100000),\n"
                   "('Ellicott City', 'USA', 'Maryland',  85000)";

    pDB->execute(sStmt, true);

    Terminal::displayCaption("\n\nNow execute a SELECT statement to see what \n"
                             "ROWs you've inserted into the city TABLE.\n\n");

    // execute a SELECT statement to see what you've inserted
    sStmt = "SELECT name, district, countrycode, population FROM city\n"
            "WHERE district = 'Maryland'";
    Terminal::displayStatement(sStmt);
    Terminal::displayLabel("USA", "Cities in Maryland");
    pRS = pDB->executeQuery(sStmt);
    Place::display(pRS, true);
    pDB->deleteResultSet();
    Terminal::displayCaption("\n\nExecute a DELETE statement to remove\n"
                             "the rows you've just inserted into the city "
                             "TABLE.\n\n");

    // execute a DELETE statement to undo what you just inserted
    sStmt = "DELETE FROM city WHERE district = 'Maryland' AND\n"
            "(name = 'Columbia' OR name = 'Ellicott City')";
    pDB->execute(sStmt, true);

    // execute a SELECT statment to see what you've deleted
    Terminal::displayCaption("\n\nHere's another SELECT statement so "
                             "you can see what ROWs \nyou've deleted "
                             "from the city TABLE.\n\n");
    sStmt = "SELECT name, district, countrycode, population FROM city\n"
            "WHERE district = 'Maryland'";
    Terminal::displayStatement(sStmt);
    Terminal::displayLabel("USA", "Cities in Maryland");
    pRS = pDB->executeQuery(sStmt);
    Place::display(pRS, true);
    pDB->deleteResultSet();
    Terminal::waitForUserInput();
    
    //******************************* Screen 6 ******************************
    Terminal::displayCaption("Here's another four column SELECT statement.\n"
                             "Note the various conditions in the WHERE clause " 
                             "and note the\nparentheses. The query behaves very "
                             "differently without the parentheses!\n\n\n");

    sStmt       = "SELECT country.name, city.name, "
                  "country.HeadOfState, country.Population\n"
                  "FROM country, city\n"
                  "WHERE country.Continent = 'Europe' "
                  "AND country.capital = city.id "
                  "AND (country.name < 'D' OR country.name > 'T')"
                  "\nORDER BY country.name DESC";
    Terminal::displayStatement(sStmt);
    Terminal::displayLabel("Continent", "Europe");
    pRS = pDB->executeQuery(sStmt);
    Place::display(pRS, true);
    Terminal::waitForUserInput();

    //******************************* Screen 7 ******************************
    Terminal::displayCaption("Let use the countrylanguage TABLE to find out "
                             "the percentage of English speakers by country."
                             "\nThis SQL query produces a name and a long "
                             "double. The ResultSet display class,\n"
                             "Language is used to display this query.\n\n\n");

    sStmt =  "SELECT name, percentage FROM country, countrylanguage WHERE\n"
             "country.code=countrylanguage.countrycode "
             "AND language='English' AND percentage >= 1.0\n"
             "ORDER BY percentage DESC";

    Terminal::displayStatement(sStmt);
    Terminal::displayLabel("Percentage of English Speakers by Country");
    pRS = pDB->executeQuery(sStmt);
    Language::display(pRS, true);
    Terminal::displayCaption("\n\nYou now know quite a bit about SQL "
                            "statements. Alter some of the SQL\n"
                            "statements you've used in this tutorial.\n"
                            "Play around and have fun!\n\n\n");
  }
  catch(const SQLException &e)
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