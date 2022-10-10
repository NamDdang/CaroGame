#ifndef COMMON_H
#define COMMON_H
#include <iostream>
using namespace std;
// Text Color
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT GRAY 7
#define DARK GRAY 8
#define LIGHT BLUE 9
#define LIGHT GREEN 10
#define LIGHT CYAN 11
#define LIGHT RED 12
#define LIGHT MAGENTA 13
#define YELLOW 14
#define WHITE 15
// Common
#define BOARD_SIZE 10
#define VX 1
#define VO 2
#define P1 RED 
#define P2 BLUE 
void SetColor(int ForgC);
void prompt(string s);
void prompt(string s, int Color);
#endif // COMMON_H
