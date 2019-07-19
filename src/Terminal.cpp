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
 *      07/17/2019    John Schwartzman
 *
 *****************************************************************************/

#include "StrStrmBuf.h"
#include "Terminal.h"

void Terminal::displayCount(const long nCount)
{
    cout << Terminal::GREEN  << "===== Number of records found: " 
         << Terminal::YELLOW << utility::commaSeparate(nCount)
         << Terminal::GREEN  << " =====\n"
         << Terminal::RESET;
}
