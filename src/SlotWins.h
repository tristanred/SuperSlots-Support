#pragma once

class Symbol;

class LineWin
{
public:
    LineWin();
    ~LineWin();

    int count;
    int winLineIndex;

    Symbol* WinningSymbol; // Copy of the symbol, owned pointer.

    int winAmount;
};

class ScatterWin
{
public:
    ScatterWin();
    ~ScatterWin();

    int count;
    int** winPositions; // int[reelPos][rowPos]

    Symbol* WinningScatter; // Copy of the symbol, owned pointer.

    int winAmount;
};

class SpecialWin
{
public:
    SpecialWin();
    ~SpecialWin();

    int FreeGamesWon;
};