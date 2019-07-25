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
 *      07/23/2019    John Schwartzman
 *
 *****************************************************************************/

#ifndef _TERMINAL_H	//********************************************************
#define _TERMINAL_H //********************************************************

#include <iostream>		// for std::cout

using namespace std;

class Terminal
{
public:
	static constexpr char* RED    = (char*)"\033[1;91;40m"; //    red on black
	static constexpr char* GREEN  = (char*)"\033[1;92;40m"; //  green on black
	static constexpr char* BLUE   = (char*)"\033[1;94;40m"; //   blue on black
	static constexpr char* CYAN   = (char*)"\033[1;96;40m"; //   cyan on black
	static constexpr char* WHITE  = (char*)"\033[1;97;40m"; //  white on black
	static constexpr char* VIOLET = (char*)"\033[1;95;40m"; // violet on black
	static constexpr char* BLACK  = (char*)"\033[1;90;40m"; //  black on black
	static constexpr char* YELLOW = (char*)"\033[1;93;40m"; // yellow on black
	static constexpr char* RESET  = (char*)"\033[0m";		//     normal text

	static void displayCount(const long nCount);
	static inline void clearScreen() { cout << "\033[2J\033[1;1H"; }
	static inline void resetAndClearScreen() { system("clear"); }
	static inline void waitForUserInput()
	{
		cout << RED << "\n\n\nPress ENTER to continue..." << RESET;
		getc(stdin);
		clearScreen();
	}
	static inline void writeYellow(const string& sContent)
	{
		cout << YELLOW << sContent << RESET;
	}
	static inline void displayStatement(const string& s)
	{
		cout << GREEN   << "===== " 
			 << VIOLET  << "Executing: " 
			 << YELLOW  << s 
			 << GREEN << " =====\n"
			 << RESET;
	}
	static inline void displayLabel(const string& sLabel, 
									const string& sContent = "")
	{
		cout << GREEN    << "\n===== " 
			 << VIOLET   << sLabel << ": " << BLUE
			 << sContent << GREEN  << " =====\n"
			 << RESET;
	}
	static inline void displayCaption(const string& sCaption)
	{
		cout << CYAN << sCaption << RESET;
	}
	static inline void displayNewLines(const int nCount = 1)
	{
		cout << string(nCount, '\n');
	}
	static inline void reset()
	{
		cout << RESET;
	}
};

#endif	//****************************** _TERMINAL_H ************************