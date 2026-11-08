#ifndef CLEAR_TERMINAL_CPP
#define CLEAR_TERMINAL_CPP

#include <iostream>
using namespace std;

void ClearTerminal() {
    std::cout << "\033[2J\033[H" << std::flush;
    std::cout << "\033[3J\033[2J\033[H" << std::flush;
}

#endif