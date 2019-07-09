/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Place.cpp
 *
 *  DESCRIPTION:
 *      A database access object class (implementation).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/07/2019    John Schwartzman
 *
 *****************************************************************************/

#include <iostream>
#include "Terminal.h"
#include "Place.h"

using namespace std;
using namespace utility;

long Place::_snRecCount = 0;    // static counter

void Place::display()
{
    ++_snRecCount;
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
    Place::clearCount();
    Place* pPlace;
    while (pRS->next())
    {
        ++_snRecCount;
        pPlace = new Place(pRS->getString(1),
                           pRS->getString(2),
                           pRS->getString(3),
                           pRS->getUInt64(4));
        StrStrmBuf ssb;
        ssb.rpad(pPlace->getField1(), 40);
        ssb.rpad(pPlace->getField2(), 34);
        ssb.rpad(pPlace->getField3(), 34);
        ssb.lpad(pPlace->getField4String(), 14);
        ssb << endl;
        Terminal::writeYellow(ssb);
    }

    if (bDisplay)
    {
        Terminal::displayCount(_snRecCount);
    }
    return Place::getCount();
}