/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Place.cpp
 *
 *  DESCRIPTION:
 *      A ResultSet access object class (implementation).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/19/2019    John Schwartzman
 *
 *****************************************************************************/

#include <cppconn/resultset.h>
#include "StrStrmBuf.h"
#include "Terminal.h"
#include "Place.h"

using namespace std;
using namespace utility;

long Place::_snRecCount = 0;    // static counter

void Place::display()
{
    StrStrmBuf ssb;
    ssb.rpad(_sField1, 40);
    ssb.rpad(_sField2, 34);
    ssb.rpad(_sField3, 34);
    ssb.lpad(commaSeparate(_nField4), 14);
    ssb << endl;
    Terminal::writeYellow(ssb);
}

long Place::display(sql::ResultSet *pRS, bool bDisplay)
{
    _snRecCount = 0;
    Place* pPlace;
    while (pRS->next())
    {
        pPlace = new Place(pRS->getString(1),
                           pRS->getString(2),
                           pRS->getString(3),
                           pRS->getUInt64(4));
        pPlace->display();
        ++_snRecCount;                          
    }

    if (bDisplay)
    {
        Terminal::displayCount(_snRecCount);
    }
    return Place::getCount();
}
