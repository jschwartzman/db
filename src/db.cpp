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
 *      07/25/2019    John Schwartzman
 *
 *****************************************************************************/
#include <stdlib.h>             // defines EXIT_SUCCESS and EXIT_FAILURE
#include "Database.h"           // encapsulates the Database Connection
#include "Place.h"              // utility for displaying ResultSets
#include "Language.h"           // utility for displaying ResultSets
#include "Terminal.h"           // screen writing utility
#include "StrStrmBuf.h"         // for text manipulation

int main(int argc, char *argv[])
{
  Terminal::resetAndClearScreen();
  try
  {
    // When pDB goes out of scope, the Database object pointed to
    // by pDB will be automatically deleted.
    unique_ptr <Database> pDB(new Database("worlduser", "worlduser123"));

    Terminal::displayLabel("A Gentle Introduction to SQL");
    Terminal::displayCaption("\n\nWelcome to this brief SQL tutorial.\n"
                             "You will encounter a variety of annotated "
                             "SQL queries and statements here, using the world "
                             "database.\nThe world database is just a "
                             "default parameter used by the program. You can "
                             "substitute\nany database and any "
                             "commands and queries that you like. You can "
                             "even create and use your own database.\nYou "
                             "can alter the program's flow of control based on "
                             "the results of a SQL query.\n\n"
                             "During this tutorial, you will be able to view "
                             "previous screens by using the mouse to scroll "
                             "your console up."
                             "\nPlease set your console to use a black background "
                             "and hit the F11 key to make it full screen.\n\n"
                             "Relax, sit back and enjoy.");
    Terminal::waitForUserInput();

    //******************************* Screen 1 ******************************
    Terminal::displayCaption("You're viewing four COLUMNs of an "
                             "INNER JOIN of the country TABLE and the "
                             "city TABLE.\nNote the various conditions "
                             "in the WHERE clause. You're asking to see "
                             "four specific\nCOLUMNs from two separate TABLEs "
                             "combining those ROWs in both TABLEs where "
                             "every part\nof the WHILE clause is satisfied."
                             "\n\n"
                             "The country TABLE doesn't have a COLUMN where "
                             "the capital city is saved by name. Instead,\n"
                             "country's capital COLUMN holds the ID "
                             "number of its capital city. You need to join\n"
                             "the country TABLE and the city TABLE together "
                             "in order to read a country's capital city name.\n"
                             "The ID COLUMN is the PRIMARY KEY of the city TABLE.\n\n\n");

    string sSelectStmt = "SELECT country.name, city.name, "
                         "country.HeadOfState, country.Population\n"
                         "FROM country INNER JOIN city\n"
                         "WHERE country.Continent = 'North America' "
                         "AND country.capital = city.ID AND "
                         "country.Population >= 1000000"
                         "\nORDER BY country.name";

    sql::ResultSet* pRS = pDB->executeQuery(sSelectStmt);
    Terminal::displayLabel("Continent", "North America");
    Place::display(pRS);
    pDB->deleteResultSet();
    Terminal::displayCaption("\n\nNOTE: You can change the SQL query "
                             "shown above so that it reads\n\"SELECT ... "
                             "FROM country, city WHERE ...\" "
                             "and it means exactly the same thing.\n\n"
                             "Why did you get so few matches?\nYou're only "
                             "looking for countries with populations "
                             "greater than 1 million.");
    Terminal::waitForUserInput();

    //******************************* Screen 2 ******************************
    Terminal::displayCaption("You're now asking the database if the "
                             "country TABLE\nhas any ROWs where the "
                             "HeadOfState COLUMN contains "
                             "George W. Bush.\n\nNote the use of the "
                             "wildcard character '%'. It will match any "
                             "number of characters.\nThe wildcard "
                             "character '_' will match any one "
                             "character.\nEmploy 'LIKE' instead of "
                             "'=' when using wildcards.\n\n\n");

    string sTestHeadOfState = "SELECT COUNT(HeadOfState) FROM country\nWHERE "
                              "HeadOfState LIKE 'George%Bush'";
    long nCount = pDB->executeCountQuery(sTestHeadOfState);
    if (nCount) // condition branch based on result of last COUNT query
    {
      utility::StrStrmBuf ssb("\n\n\nAccording to the database, "
                              "George Bush is the Head Of State of ");
      ssb << nCount << " countries.\nThis database is way out of date, "
                       "but we'll stay firmly in the past.\nExecute the following "
                       "UPDATE statement.\n\n\n";
      Terminal::displayCaption(ssb);
      // execute an UPDATE statement
      string sStmt = "UPDATE country "
                     "SET HeadOfState = 'Barack Obama'\n"
                     "WHERE HeadOfState LIKE 'George%Bush'";
      pDB->execute(sStmt);
    }
    else
    {
      Terminal::displayCaption("\n\n\nNo records found. "
                               "Barack Obama must be president of "
                               "the US.\n"
                               "Let's change that and restore the "
                               "original content of the database.\nYou'll "
                               "use an UPDATE statement to restore "
                               "the database's previous HeadOfState.\n\n");
      // execute an UPDATE statement
      string sStmt = "UPDATE country "
                     "SET HeadOfState = 'George W. Bush'\n"
                     "WHERE HeadOfState = 'Barack Obama'";
      pDB->execute(sStmt);
    }
    Terminal::waitForUserInput();

    //******************************* Screen 3 ******************************
    Terminal::displayCaption("You're executing the same SQL query as last time\n"
                             "but, notice how the database has changed.\n\n"
                             "You're using the Place ResultSet display class "
                             "to display these and other, similar query results."
                             "\n\n\n");
    // reexecute the SELECT statement we used earlier
    pRS = pDB->executeQuery(sSelectStmt);
    Terminal::displayLabel("Continent", "North America");
    Place::display(pRS);
    pDB->deleteResultSet();
    Terminal::waitForUserInput();

    //******************************* Screen 4 ******************************
    Terminal::displayCaption("Here are a couple more count queries.\n"
                             "Count queries return a ResultSet "
                             "containing a single element.\n"
                             "That element contains a long integer "
                             "representing the number\nof rows retrieved.\n\n\n");
    // execute a SELECT COUNT statement
    string sCountQuery = "SELECT COUNT(HeadOfState) FROM country";
    pDB->executeCountQuery(sCountQuery);

    Terminal::displayNewLines(3);
    // execute a SELECT COUNT statement
    sCountQuery = "SELECT COUNT(DISTINCT HeadOfState) FROM country";
    pDB->executeCountQuery(sCountQuery);

    Terminal::displayCaption("\n\nNote that the number of DISTINCT (unique) "
                             "heads of state is less\nthan the total number "
                             "of heads of state.\nThat is because some "
                             "heads of state are leaders of more \n"
                             "than one country. DISTINCT removes "
                             "duplicates.\n\n");

    Terminal::waitForUserInput();

    //******************************* Screen 5 ******************************
    Terminal::displayCaption("We can add items to and remove items from the "
                             "database.\nExecute an INSERT statment with multiple "
                             "rows.\nYou can also achieve the same results " 
                             "using two separate INSERT statements.\n\n"
                             "The city TABLE has an ID COLUMN, but we don't "
                             "mention it in the the INSERT statement.\nThat's "
                             "because the ID COLUMN is a PRIMARY KEY. It is\n"
                             "an auto incrementing value chosen by the RDBMS.\n\n");

    // execute an INSERT statement with multiple rows
    string sStmt = "INSERT INTO city (name, countrycode, district, population) "
                   "VALUES\n"
                   "('Columbia',      'USA', 'Maryland', 100000),\n"
                   "('Ellicott City', 'USA', 'Maryland',  85000)";

    pDB->execute(sStmt);

    Terminal::displayCaption("\n\nNow execute a SELECT statement to see what \n"
                             "ROWs you've inserted into the city TABLE.\n\n");

    // execute a SELECT statement to see what you've inserted
    sStmt = "SELECT name, district, countrycode, population FROM city\n"
            "WHERE district = 'Maryland'";
    pRS = pDB->executeQuery(sStmt);
    Terminal::displayLabel("USA", "Cities in Maryland");
    Place::display(pRS);
    pDB->deleteResultSet();
    Terminal::displayCaption("\n\nExecute a DELETE statement to remove\n"
                             "the rows you've just inserted into the city "
                             "TABLE.\nYou must be specific enough to avoid "
                             "deleting Columbia, North Caroline, if it\n"
                             "exists in the database. That's why we need "
                             "district = 'Maryland' in the WHERE clause.\n\n");

    // execute a DELETE statement to undo what you just inserted
    sStmt = "DELETE FROM city WHERE district = 'Maryland' AND\n"
            "(name = 'Columbia' OR name = 'Ellicott City')";
    pDB->execute(sStmt);

    // execute a SELECT statment to see what you've deleted
    Terminal::displayCaption("\n\nHere's another SELECT statement so "
                             "you can see what ROWs \nyou've deleted "
                             "from the city TABLE.\n\n");
    sStmt = "SELECT name, district, countrycode, population FROM city\n"
            "WHERE district = 'Maryland'";
    pRS = pDB->executeQuery(sStmt);
    Terminal::displayLabel("USA", "Cities in Maryland");
    Place::display(pRS);
    pDB->deleteResultSet();
    Terminal::displayCaption("\n\nYou've deleted the records you added and "
                             "the city TABLE is restored to its original "
                             "form.\n");
    Terminal::waitForUserInput();
    
    //******************************* Screen 6 ******************************
    Terminal::displayCaption("Here's another four column SELECT statement.\n"
                             "Note the various conditions in the WHERE clause " 
                             "and note the\nparentheses. The query behaves very "
                             "differently without parentheses!\n\n\n");

    sStmt       = "SELECT country.name, city.name, "
                  "country.HeadOfState, country.Population\n"
                  "FROM country, city\n"
                  "WHERE country.Continent = 'Europe' "
                  "AND country.capital = city.id "
                  "AND (country.name < 'D' OR country.name > 'T')"
                  "\nORDER BY country.name DESC";
    pRS = pDB->executeQuery(sStmt);
    Terminal::displayLabel("Continent", "Europe");
    Place::display(pRS);
    Terminal::waitForUserInput();

    //******************************* Screen 7 ******************************
    Terminal::displayCaption("Let's use the countrylanguage TABLE to find out "
                             "the percentage of English speakers by country."
                             "\nThis SQL query produces a name and a long "
                             "double. The Language ResultSet display class\n"
                             "is used to display these query results.\n\n\n");

    sStmt =  "SELECT name, percentage FROM country, countrylanguage WHERE\n"
             "country.code=countrylanguage.countrycode "
             "AND language='English' AND percentage >= 1.0\n"
             "ORDER BY percentage DESC";

    pRS = pDB->executeQuery(sStmt);
    Terminal::displayLabel("Percentage of English Speakers by Country");
    Language::display(pRS);
    Terminal::displayCaption("\n\nYou now know quite a bit about SQL. "
                            "Alter some of the SQL\n"
                            "statements you've used in this tutorial.\n"
                            "Play around and have fun!\n\n\n");
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