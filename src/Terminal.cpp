/*****************************************************************************
 *
 *  John Schwartzman, Forte Systems, Inc.
 *
 *  FILENAME:
 *      Terminal.cpp
 *
 *  DESCRIPTION:
 *      Some terminal color escape codes and operations.
 *
 *  COMPILER:
 *      g++ 9.1.1
 *
 *  AUTHOR:
 *      08/03/2019    John Schwartzman
 *
 *****************************************************************************/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "StrStrmBuf.h"
#include "Terminal.h"

void Terminal::waitForUserInput()
{
    struct termios  oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    cout << RED << "\n\n\nHit any key to continue..." << RESET;
    getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    clearScreen();
}

void Terminal::displayCount(const long nCount)
{
    cout << GREEN  << "===== Number of records found: " 
         << YELLOW << utility::commaSeparate(nCount)
         << GREEN  << " =====\n"
         << RESET;
}

void Terminal::displayStatement(const string& s)
{
    cout << GREEN  << "===== " 
         << VIOLET << "Executing: " 
         << YELLOW << s 
         << GREEN  << " =====\n"
         << RESET;
}
void Terminal::displayLabel(const string& sLabel, const string& sContent)
{
    cout << GREEN    << "\n===== " 
         << VIOLET   << sLabel << ": ";

    if (!sContent.empty())
    {
        cout << BLUE<< sContent;
    }

    cout << GREEN  << " =====\n"
         << RESET;
}

