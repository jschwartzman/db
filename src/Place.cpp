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
 *      07/21/2019    John Schwartzman
 *
 *****************************************************************************/

#include <cppconn/resultset.h>
#include "StrStrmBuf.h"
#include "Terminal.h"
#include "Place.h"

void Place::display()
{
    utility::StrStrmBuf ssb;
    ssb.rpad(_sField1, 40);
    ssb.rpad(_sField2, 34);
    ssb.rpad(_sField3, 34);
    ssb.lpad(utility::commaSeparate(_nField4), 14);
    ssb << endl;
    Terminal::writeYellow(ssb);
}

long Place::display(sql::ResultSet *pRS, bool bDisplay)
{
    long nCount = 0;
    while (pRS->next())
    {
        Place* pPlace = new Place(pRS->getString(1),
                                  pRS->getString(2),
                                  pRS->getString(3),
                                  pRS->getUInt64(4));
        pPlace->display();
        delete pPlace;
        ++nCount;                          
    }

    if (bDisplay)
    {
        Terminal::displayCount(nCount);
    }
    return nCount;
}
