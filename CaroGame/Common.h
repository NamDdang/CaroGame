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
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15
// Common
#define BOARD_SIZE 10
#define VX 1
#define VO 2
#define P1 RED 
#define P2 BLUE 
void SetColor(int ForgC);
char* InputStringName(const int k);
bool isIPAddress(string ip);
#endif // COMMON_H
