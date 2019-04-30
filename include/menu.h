#ifndef MENU_H_
#define MENU_H_

void clearScreen();

void printLineWithText(const char* text);
void printHastagLine();

int getOption();

void pressAnyKeyToContinue();
void printOptionWIP();
void printOptionInvalid();

#endif // MENU_H_
