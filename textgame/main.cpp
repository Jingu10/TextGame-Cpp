// main.cpp
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include <cstdlib>
#include <ctime>
#include "GameManager.h"

#pragma execution_character_set("utf-8")

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    GameManager game;
    game.Run();

    return 0;
}