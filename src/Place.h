/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Place.h
 *
 *  DESCRIPTION:
 *      A database access object class (interface).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/08/2019    John Schwartzman
 *
 *****************************************************************************/
#ifndef PLACE_  //************************************************************
#define PLACE_  //************************************************************

#include "StrStrmBuf.h"
#include <cppconn/resultset.h>

class Place
{
private:
    static long       _snRecCount;
    const std::string _sField1;
    const std::string _sField2;
    const std::string _sField3;
    const long        _nField4;

public:
    Place(std::string name, 
            std::string capital, 
            std::string headOfState,
            long        population) : _sField1(name),
                                      _sField2(capital),
                                      _sField3(headOfState),
                                      _nField4(population)    {}
    ~Place() {}
    static void clearCount()    { _snRecCount = 0; }
    static long getCount()      { return _snRecCount; }
    void display();
    const std::string& getField1()  { return _sField1; }
    const std::string& getField2()  { return _sField2; }
    const std::string& getField3()  { return _sField3; }
    long getField4()                { return _nField4; }
    const std::string  getField4String()     
        { return utility::commaSeparate(_nField4); }
    static long display(sql::ResultSet* pRS, bool bDisplayCount = false);
};

#endif //*************************** PLACE_H ********************************
