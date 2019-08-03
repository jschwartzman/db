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
 *      08/02/2019    John Schwartzman
 *
 *****************************************************************************/
#ifndef LANGUAGE_H  //********************************************************
#define LANGUAGE_H  //********************************************************

typedef sql::ResultSet* pRS;    // just the type definition is sufficient here

class Language
{
private:
    const std::string   _sField1;
    const long double   _nField2;

public:
    Language(std::string country,           // constructor
             long double percent) : _sField1(country),
                                    _nField2(percent)    {}
    ~Language() {}                         // destructor
    void display();
    static long display(sql::ResultSet* pRS, bool bDisplayCount = true);
};

#endif //************************* LANGUAGE_H *******************************
