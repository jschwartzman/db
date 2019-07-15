/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Language.h
 *
 *  DESCRIPTION:
 *      A ResultSet access object class (interface).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/14/2019    John Schwartzman
 *
 *****************************************************************************/
#ifndef LANGUAGE_H  //********************************************************
#define LANGUAGE_H  //********************************************************

typedef sql::ResultSet* pRS;    // just the type definition is sufficient here

class Language
{
private:
    static long         _snRecCount;
    const std::string   _sField1;
    const long double   _nField2;

public:
    Language(std::string country,           // constructor
             long double percent) : _sField1(country),
                                    _nField2(percent)    {}
    ~Language() {}                         // destructor
    static void clearCount()    { _snRecCount = 0; }
    static long getCount()      { return _snRecCount; }
    void display();
    static long display(sql::ResultSet* pRS, bool bDisplayCount = false);
};

#endif //************************* LANGUAGE_H *******************************
