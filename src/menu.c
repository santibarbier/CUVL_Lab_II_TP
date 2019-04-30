#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"

// COMO USAR 'conditional preprocessor directives'
// https://codeforwin.org/2018/11/c-preprocessor-directives-include-define-undef-conditional-directives.html

#define OS_LINUX 0
#define OS_WINDOWS 1

#define OS OS_WINDOWS

#if OS == OS_LINUX
#include <unistd.h>   //_getch
#include <termios.h>  //_getch
char getch() // copypaste ni idea si funciona
{
    // https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
}
#elif OS == OS_WINDOWS
    // something
    #include <conio.h> // getch
#endif // OS

void clearScreen()
{
    system("cls");
}

// porque supuestamente fflush() es un asco y ademas no esta en linux
//void cleanStdin()
//{
//    // https://stackoverflow.com/questions/17318886/fflush-is-not-working-in-linux
//    int c;
//    do {
//        c = getchar();
//    } while (c != '\n' && c != EOF);
//}

void printLineWithText(const char* text)
{
	char line1[80+1];
	memset(line1, '\0', 81);
	*line1='#';
	*(line1+79) = '#';
	strncat(line1+1, text, strlen(text));
	int i=0;
	while(i<80){
		if(*(line1+i) == '\0'){
			*(line1+i) = ' ';
		}
		i++;
	}
	printf("%s\n", line1);
}

void printHastagLine()
{
	char line[80+1];
	memset(line, '\0', 81);
	memset(line, '#', 80);
	printf("%s\n", line);
}

int getOption()
{
//	int option = 1; // le' ponemo' 1 porque 0 es pa' salir
//	scanf("%d", &option);
//	printHastagLine();
    int option = getch() - '0'; // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
	return option;
}

void pressAnyKeyToContinue()
{
    printf("Presione una tecla para continuar.");
//    getchar();
    getch();
}

void printOptionWIP()
{
    printf("\n\tMenu en construccion.\n\t");
    pressAnyKeyToContinue();
}

void printOptionInvalid()
{
    printf("\n\tOpcion no valida.\n\t");
    pressAnyKeyToContinue();
}
