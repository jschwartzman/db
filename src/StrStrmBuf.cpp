/*****************************************************************************
 *
 *	NOTICE:
 *      Copyright 2011, Forte Systems, Inc.
 *
 *  FILENAME:
 *      StrStrmBuf.cpp
 *
 *  DESCRIPTION:
 *      a java-like string builder utility class - implementation
 *
 *  COMPILER:
 *      g++ 9.1.1	now supports c++ 11
 *
 *  AUTHOR:
 *      10/28/2011    John Schwartzman
 *		06/29/2018	  John Schwartzman
 *		07/25/2019	  John Schwartzman
 *****************************************************************************/
#include <locale>			// for formatDateTime()
#include <cstring>			// for strlen() in formatDateTime()
#include "StrStrmBuf.h"

namespace utility	{

using std::string;
using std::ostream;

/*****************************************************************************
 *
 *  class StrStrmBuf : public std::stringstream
 *
 *  	a java-like string builder utility class
 *
 *  	operator const char*() allows this class to be passed
 *  	to std::cout and std::cerr
 *
 *****************************************************************************/
/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::operator=(StrStrmBuf& rhs)
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::operator=(StrStrmBuf& rhs)
{
	if (&rhs != this)
	{
		str(rhs.str());
	}
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::putch(char ch, size_t nCount);
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::putch(char ch, size_t nCount)
{
	for (size_t i = 0; i < nCount; i++)
	{
		put(ch);
	}
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::putstr(const string& str)
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::putstr(const string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		put(str[i]);
	}
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf pad functions
 *
 *****************************************************************************/
size_t utf8_strlen(const string& s)	// this function thanks to www.zedwood.com
{
    size_t c = 0, i = 0, ix = s.length(), q;
    for (q = 0; i < ix; i++, q++)
    {
        c = static_cast<unsigned char>(s[i]);
        if      (c >= 0 && c <= 127)   i += 0;	// single byte char
        else if ((c & 0xE0) == 0xC0)   i += 1;  // double byte char
        else if ((c & 0xF0) == 0xE0)   i += 2;  // triple byte char
        else if ((c & 0xF8) == 0xF0)   i += 3;  // quadruple byte char
        else return 0;  //invalid utf8
    }

    return q;
}

/*****************************************************************************/

StrStrmBuf& StrStrmBuf::lpad(const string& s, size_t nWidth, char ch)
{
	size_t nLen = utf8_strlen(s);
	if (nLen < nWidth)
	{
		putch(ch, nWidth - nLen);
		*this << s;
	}
	else
	{
		*this << s.substr(0, nWidth);
	}
	
	return *this;
}

StrStrmBuf& StrStrmBuf::rpad(const string& s, size_t nWidth, char ch)
{
	size_t nLen = utf8_strlen(s);
	if (nLen < nWidth)
	{
		*this << s;
		putch(ch, nWidth - nLen);
	}
	else
	{
		*this << s.substr(0, nWidth);
	}
	
	return *this;
}

StrStrmBuf& StrStrmBuf::center(const string& s, size_t nWidth, char ch)
{
	size_t nLen = utf8_strlen(s);
	size_t nRight = (nWidth - nLen) / 2;
	if (nLen < nWidth)
	{
		putch(ch, nWidth - nLen - nRight);
		*this << s;
		putch(ch, nRight);
	}
	else
	{
		*this << s.substr(0, nWidth);
	}
	
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::ltrim();
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::ltrim()
{
	str(utility::ltrim(str()));
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::rtrim();
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::rtrim()
{
	str(utility::rtrim(str()));
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::trim();
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::trim()
{
	str(utility::trim(str()));
	return *this;
}

/*****************************************************************************
 *
 * Non-Member Functions:
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * string toHHMMSS(long nTime)
 *
 * 		converts a long into hours, minutes and seconds (HH:MM:SS)
 *
 *****************************************************************************/
string toHHMMSS(long nTime)
{
	StrStrmBuf	ssb;
	long 		nTimeTmp = nTime / HOUR;	// get hours

	if (nTimeTmp < TEN) ssb.put('0');		// write hours
	ssb << nTimeTmp << ':';
	nTime %= HOUR;							// remove hours

	nTimeTmp = nTime / SIXTY;				// get minutes
	if (nTimeTmp < TEN) ssb.put('0');		//rpad write minutes
	ssb << nTimeTmp << ':';

	nTime %= SIXTY;							// get seconds
	if (nTime < TEN) ssb.put('0');			// write seconds
	ssb << nTime;
	return ssb.str();
}

/*****************************************************************************
 *
 * string commaSeparate(long n)
 *
 * 		comma separate a long into powers of 10^3
 *
 *****************************************************************************/
string commaSeparate(long n)
{
	bool		bFoundFactor(false);
	StrStrmBuf	ssb;
	long		nTmp;

	nTmp = n / QUINTILLION;							// get quintillions
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * QUINTILLION;					// remove quintillions
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// write quintillions
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// write quintillions
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}
	
	nTmp = n / QUADRILLION;							// get quadrillions
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * QUADRILLION;					// remove quadrillions
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// write quadrillions
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// write quadrillions
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}
	
	nTmp = n / TRILLION;							// get trillions
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * TRILLION;						// remove trillions
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// write trillions
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// write trillions
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}

	nTmp = n / BILLION;								// get billions
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * BILLION;						// remove billions
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// write billions
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// write billions
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}

	nTmp = n / MILLION;								// get millions
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * MILLION;						// remove millions
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// write millions
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// write millions
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}

	nTmp = n / THOUSAND;							// get thousands
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * THOUSAND;						// remove thousands
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// write thousands
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// write thousands
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}

	if (!bFoundFactor)
	{
		ssb << n;									// write units
	}
	else
	{
		if (n < HUNDRED) ssb.put('0');				// write units
		if (n < TEN)  ssb.put('0');
		ssb << n;
	}
	return ssb.str();
}

/*****************************************************************************
 *
 * String trim Functions:
 *
 *****************************************************************************/
string ltrim(const string& s)
{
	if (s.empty()) return std::string();

	size_t nBegin = s.find_first_not_of(" \t\n", 0);
	// if we don't find whitespace, return empty string
	if (nBegin == string::npos) return string();

	return s.substr(nBegin);
}

string rtrim(const string& s)
{
	if (s.empty()) return string();

	size_t nEnd = s.find_last_not_of(" \t\n");
	// if we don't find whitespace, return empty string
	if (nEnd == string::npos) return string();

	return s.substr(0, nEnd + 1);
}

string trim(const string& s)
{
	if (s.empty()) return string();

	size_t nBegin = s.find_first_not_of(" \t\n", 0);
	// if we don't find whitespace, return empty string
	if (nBegin == string::npos) return string();

	size_t nEnd = s.find_last_not_of(" \t\n");
	return s.substr(nBegin, nEnd - nBegin + 1);
}

/*****************************************************************************
 *
 *	std::string formatDateTime(time_t* t = NULL,
 *				   			   const char* fmt = utility::SHORT_DATETIME_FMT);
 *
 *****************************************************************************/
string formatDateTime(time_t* t, const char* fmt)
{
	using namespace std;
	tm*		tminfo;
	StrStrmBuf	ssb;
	time_t 		rawtm = time(t);
	tminfo = localtime(&rawtm);
	const time_put<char>& dtwriter = use_facet<time_put<char> >(ssb.getloc());
	if (dtwriter.put(ssb, ssb, ' ', tminfo, fmt, fmt + strlen(fmt)).failed())
	{
		return "";
	}
	return ssb.str();
}

// ***************************************************************************
}	// end namespace utility
// ***************************************************************************
