/*****************************************************************************
 *
 *	NOTICE:
 *      Copyright 2011, Forte Systems, Inc.
 *
 *  FILENAME:
 *      StrStrmBuf.h
 *
 *  DESCRIPTION:
 *      A java-like string builder utility class (interface).
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      10/28/2011    John Schwartzman
*		07/23/2019	  John Schwartzman
 *****************************************************************************/
#ifndef STRSTRMBUF_H_	//****************************************************
#define STRSTRMBUF_H_	//****************************************************

#include <sstream>

namespace utility	{

const long TEN			= 10;
const long SIXTY		= 60;
const long HOUR			= SIXTY * SIXTY;
const long HUNDRED		= 100;
const long THOUSAND 	= 1000;
const long MILLION  	= THOUSAND * THOUSAND;
const long BILLION 		= THOUSAND * MILLION;
const long TRILLION 	= THOUSAND * BILLION;
const long QUADRILLION	= THOUSAND * TRILLION;
const long QUINTILLION  = THOUSAND * QUADRILLION;

/*****************************************************************************
 *
 *  class StrStrmBuf : public std::stringstream
 *
 *  	operator const char*() allows this class to be passed
 *  	to std::cout and std::cerr
 *
 *****************************************************************************/

#define SSB_OPEN_MODE std::ios_base::out|std::ios_base::in|std::ios_base::ate

class StrStrmBuf : public std::stringstream
{
public:
	inline explicit StrStrmBuf() : std::stringstream(SSB_OPEN_MODE)	{}
	inline explicit StrStrmBuf(const std::string& str) :
		std::stringstream(str, SSB_OPEN_MODE)					{}
	inline explicit StrStrmBuf(const char* pStr) :
		std::stringstream(pStr, SSB_OPEN_MODE)					{}
	template <typename T>
	StrStrmBuf(const std::string& str, T const param) :
		std::stringstream(str, SSB_OPEN_MODE)  { *this << param; }
	StrStrmBuf(StrStrmBuf& rhs) 		       { str(rhs.str()); }
	inline StrStrmBuf& putch(char ch, size_t nCount = 1);
	inline StrStrmBuf& putstr(const std::string& str);

	inline StrStrmBuf& width(int nCol)
		{ std::ios_base::width(nCol); return *this; }
	StrStrmBuf& clear()							{ str(""); return *this;  }
	inline size_t length() const				{ return str().length();  }
	inline bool empty() const
		{ return str().length() == 0; }
	inline StrStrmBuf& operator=(const std::string& s)
		{ str(s); return *this; }
	inline StrStrmBuf& operator=(const char* s)	{ str(s); return *this;	  }
	inline StrStrmBuf& operator=(StrStrmBuf& rhs);
	inline operator const char*()		{ return this->str().c_str();	  	 }
	inline operator char*()				{ return (char*)this->str().c_str(); }
	inline operator const std::string()	{ return this->str();		  	     }

	StrStrmBuf& ltrim();
	StrStrmBuf& rtrim();
	StrStrmBuf& trim();

	StrStrmBuf& lpad(const std::string& s,   size_t nSize, char ch = ' ');
	StrStrmBuf& rpad(const std::string& s,   size_t nSize, char ch = ' ');
	StrStrmBuf& center(const std::string& s, size_t nSize, char ch = ' ');
};

/*****************************************************************************
 *
 * Non-Member Convenience Functions:
 *
 *****************************************************************************/
/*****************************************************************************
 *
 * Overload of StrStrmBuf operator << (std::ostream& out, StrStrmBuf& rhs)
 *
 *****************************************************************************/
inline __attribute__ ((unused))
std::ostream& operator<<(std::ostream& out, StrStrmBuf& rhs)
	{ out.write(rhs.str().c_str(), rhs.length()); return out; }

inline __attribute__ ((unused))
const char* boolString(bool b)			{ return (b ? "true" : "false"); }

__attribute__ ((unused)) std::string toHHMMSS(long nTimeDiff);
__attribute__ ((unused)) std::string commaSeparate(long n);

template <typename T> inline  __attribute__ ((unused)) static const char*
singularPlural(T intType, const char* pSingular, const char* pPlural)
					{ return (intType == 1 ? pSingular : pPlural); }

std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);

__attribute__ ((unused))
static const char* SH_DATETIME_FMT 		= "%m/%d/%Y %X";
__attribute__ ((unused))
static const char* LONG_DATE_FMT 		= "%A, %B %d, %Y";
__attribute__ ((unused))
static const char* LONG_DATETIME_FMT	= "%A, %B %d, %Y %X";
__attribute__ ((unused))
static const char* MED_DATETIME_FMT		= "%c";

__attribute__ ((unused))
std::string formatDateTime(time_t* t = NULL,
                           const char* fmt = SH_DATETIME_FMT);

// **************************************************************************
}	// end namespace utility
#endif //***************************  STRSTRMBUF_H_ *************************
