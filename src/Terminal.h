/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Terminal.h
 *
 *  DESCRIPTION:
 *      Some terminal color escape codes and operations.
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      07/08/2019    John Schwartzman
 *
 *****************************************************************************/

#ifndef _TERMINAL_H	//********************************************************
#define _TERMINAL_H //********************************************************

#include <streambuf>
#include "StrStrmBuf.h"

using namespace std;
using namespace utility;

class Terminal
{
public:
	static constexpr char* RED     = (char*)"\033[1;31;40m"; //    red on black
	static constexpr char* GREEN   = (char*)"\033[1;32;40m"; //  green on black
	static constexpr char* BLUE    = (char*)"\033[1;34;40m"; //   blue on black
	static constexpr char* CYAN    = (char*)"\033[1;36;40m"; //   cyan on black
	static constexpr char* WHITE   = (char*)"\033[0;37;40m"; //  white on black
	static constexpr char* VIOLET  = (char*)"\033[1;35;40m"; // violet on black
	static constexpr char* BLACK   = (char*)"\033[0;30;40m"; //  black on black
	static constexpr char* YELLOW  = (char*)"\033[1;33;40m"; // yellow on black
	static constexpr char* RESET   = (char*)"\033[0m";		 // normal text

	static void clearScreen() { cout << "\033c"; }
	static void waitForUserInput()
	{
		std::cout << RED << "\n\n\nPress ENTER to continue..." << RESET;
		getc(stdin);
		clearScreen();
	}
	static void writeYellow(string s)
	{
		StrStrmBuf ssb(YELLOW);
		ssb << s << RESET;
		cout << ssb;
	}
	static void writeYellow(StrStrmBuf s)
	{
		StrStrmBuf ssb(YELLOW);
		ssb << s << RESET;
		cout << ssb;
	}
	static void displayCount(const long nCount)
	{
		cout << "===== Number of records found: " 
				<< YELLOW
				<< commaSeparate(nCount)
				<< RESET
				<< " =====\n";
	}
	static void displayStatement(const std::string s)
	{
		cout << "===== " 
				<< VIOLET << "Executing: " 
				<< YELLOW 
				<< s << RESET << " =====\n";
	}
	static void displayLabel(const string sLabel, const string sContent)
	{
		cout << "\n===== " << sLabel << ": "
				<< sContent   << " =====\n";
	}
	static void displayCaption(const string sCaption)
	{
		cout << sCaption;
	}
	static void displayNewLines(const int nCount = 1)
	{
		cout << string(nCount, '\n');
	}
};

#endif	//****************************** _TERMINAL_H ************************