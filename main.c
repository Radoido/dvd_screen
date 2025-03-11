#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

// MACRO
#define NO_COLISION 0
#define DOWN_COLISION 1
#define UP_COLISION 2
#define RIGHT_COLISION 3
#define LEFT_COLISION 4
//------------
#define MOVE_XUP_YUP 1
#define MOVE_XDOWN_YUP 2
#define MOVE_XUP_YDOWN 3
#define MOVE_XDOWN_YDOWN 4

// STRUCTURE
typedef struct
{
    int x;
    int y;
    int oldX;
    int oldY;
    char colision;
    char currentMove;

} movePar;

void SetConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void SetCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char a[1] = "0";

COORD getTerminalResolution()
{
    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        // Get the screen resolution (width and height)
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        COORD coord = {width, height};

        // Print the resolution
        return coord;
    }
    else
    {
        printf("Failed to get console screen buffer info.\n");
    }
}

char checkColision(int x, int y)
{
    COORD coord = getTerminalResolution();

    if (x == coord.X - 1)
    {
        return RIGHT_COLISION;
    }
    else if (x == 0)
    {
        return LEFT_COLISION;
    }
    else if (y == coord.Y - 1)
    {
        return DOWN_COLISION;
    }
    else if (y == 0)
    {
        return UP_COLISION;
    }

    return NO_COLISION;
}

movePar moveXUpYUp(movePar par)
{
    char colision;

    while (1)
    {
        Sleep(25);
        SetCursorPosition(par.oldX, par.oldY);
        par.oldX = par.x;
        par.oldY = par.y;
        printf(" ");
        par.x++;
        par.y++;
        par.oldX = par.x;
        par.oldY = par.y;
        SetCursorPosition(par.x, par.y);
        printf("%s", a);
        colision = checkColision(par.x, par.y);
        if (colision != NO_COLISION)
        {
            par.colision = colision;
            par.currentMove = MOVE_XUP_YUP;
            return par;
        }
    }
}

movePar moveXUpYDown(movePar par)
{
    char colision;

    while (1)
    {
        Sleep(25);
        SetCursorPosition(par.oldX, par.oldY);
        par.oldX = par.x;
        par.oldY = par.y;
        printf(" ");
        par.x++;
        par.y--;
        par.oldX = par.x;
        par.oldY = par.y;
        SetCursorPosition(par.x, par.y);
        printf("%s", a);
        colision = checkColision(par.x, par.y);
        if (colision != NO_COLISION)
        {
            par.colision = colision;
            par.currentMove = MOVE_XUP_YDOWN;
            return par;
        }
    }
}

movePar moveXDownYUp(movePar par)
{
    char colision;

    while (1)
    {
        Sleep(25);
        SetCursorPosition(par.oldX, par.oldY);
        par.oldX = par.x;
        par.oldY = par.y;
        printf(" ");
        par.x--;
        par.y++;
        par.oldX = par.x;
        par.oldY = par.y;
        SetCursorPosition(par.x, par.y);
        printf("%s", a);
        colision = checkColision(par.x, par.y);
        if (colision != NO_COLISION)
        {
            par.colision = colision;
            par.currentMove = MOVE_XDOWN_YUP;
            return par;
        }
    }
}

movePar moveXDownYDown(movePar par)
{
    char colision;

    while (1)
    {
        Sleep(25);
        SetCursorPosition(par.oldX, par.oldY);
        par.oldX = par.x;
        par.oldY = par.y;
        printf(" ");
        par.x--;
        par.y--;
        par.oldX = par.x;
        par.oldY = par.y;
        SetCursorPosition(par.x, par.y);
        printf("%s", a);
        colision = checkColision(par.x, par.y);
        if (colision != NO_COLISION)
        {
            par.colision = colision;
            par.currentMove = MOVE_XDOWN_YDOWN;
            return par;
        }
    }
}

COORD move(int x, int y)
{
    movePar par = {x, y, x, y, NO_COLISION, MOVE_XUP_YUP};
    par = moveXUpYUp(par);

    while (1)
    {

        if (par.colision == LEFT_COLISION && par.currentMove == MOVE_XDOWN_YUP)
        {
            par = moveXUpYUp(par);
        }
        else if (par.colision == LEFT_COLISION && par.currentMove == MOVE_XDOWN_YDOWN)
        {
            par = moveXUpYDown(par);
        }
        else if (par.colision == RIGHT_COLISION && par.currentMove == MOVE_XUP_YUP)
        {
            par = moveXDownYUp(par);
        }
        else if (par.colision == RIGHT_COLISION && par.currentMove == MOVE_XUP_YDOWN)
        {
            par = moveXDownYDown(par);
        }
        else if (par.colision == UP_COLISION && par.currentMove == MOVE_XUP_YDOWN)
        {
            par = moveXUpYUp(par);
        }
        else if (par.colision == UP_COLISION && par.currentMove == MOVE_XDOWN_YDOWN)
        {
            par = moveXDownYUp(par);
        }
        else if (par.colision == DOWN_COLISION && par.currentMove == MOVE_XUP_YUP)
        {
            par = moveXUpYDown(par);
        }
        else if (par.colision == DOWN_COLISION && par.currentMove == MOVE_XDOWN_YUP)
        {
            par = moveXDownYDown(par);
        }
    }
}

int main()
{
    system("cls");

    COORD resol = getTerminalResolution();

    // Set the console text color to light green
    SetConsoleColor(10); // 10 is light green
    SetCursorPosition(resol.X / 2, resol.Y / 2);

    printf("O");

    move(resol.X / 2, resol.Y / 2);

    // Reset color to default
    SetConsoleColor(7); // 7 is the default color
}
