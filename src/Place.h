/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Place.h
 *
 *  DESCRIPTION:
 *      A ResultSet access object class (interface).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/21/2019    John Schwartzman
 *
 *****************************************************************************/
#ifndef PLACE_  //************************************************************
#define PLACE_  //************************************************************

typedef sql::ResultSet* pRS;    // just the type definition is sufficient here

class Place
{
private:
    const std::string _sField1;
    const std::string _sField2;
    const std::string _sField3;
    const long        _nField4;

public:
    Place(std::string name,             // constructor
          std::string capital, 
          std::string headOfState,
          long        population) : _sField1(name),
                                    _sField2(capital),
                                    _sField3(headOfState),
                                    _nField4(population)    {}
    ~Place() {}                         // destructor
    void display();
    static long display(sql::ResultSet* pRS, bool bDisplayCount = true);
};

#endif //*************************** PLACE_H ********************************
