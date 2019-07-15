/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Language.cpp
 *
 *  DESCRIPTION:
 *      A ResultSet access object class (implementation).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/14/2019    John Schwartzman
 *
 *****************************************************************************/

#include <cppconn/resultset.h>
#include "StrStrmBuf.h"
#include "Terminal.h"
#include "Language.h"

using namespace std;
using namespace utility;

long Language::_snRecCount = 0;    // static counter

void Language::display()
{
    ++_snRecCount;
    StrStrmBuf ssb;
    ssb.rpad(_sField1, 30);
    long double ld = _nField2;
    string s = to_string(ld);
    if (ld == 100.0)
    {
        s = s.substr(0, 5);
    }
    else if (ld < 10.0)
    {
        s = s.substr(0, 3);
    }
    else
    {
        s = s.substr(0, 4);
    }
    ssb.lpad(s, 6);
    ssb << endl;
    Terminal::writeYellow(ssb);
}

long Language::display(sql::ResultSet *pRS, bool bDisplay)
{
    Language::clearCount();
    Language* pLanguage;
    while (pRS->next())
    {
        pLanguage = new Language(pRS->getString(1),
                                 pRS->getDouble(2));
        pLanguage->display();                           
    }

    if (bDisplay)
    {
        Terminal::displayCount(_snRecCount);
    }
    return Language::getCount();
}