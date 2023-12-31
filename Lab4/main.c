/* Pavel Dvas */

#include <stdio.h>
#include <conio.h>

#include "tree.h"

void GetStr( char *Str, int MaxLen )
{
  int i = 0;
  char ch;

  while ((ch = getchar()) != '\n')
    if (Str != NULL && i < MaxLen - 1)
      Str[i++] = ch;
  if (Str != NULL && i < MaxLen)
    Str[i] = 0;
}

void main( void )
{
  char FileName[MAX_STR];
  TREE *ExSys;

  ExSys = Init("pig", NULL, NULL);

  system("chcp 1251");

  while (1)
    switch (_getch())
    {
    case '0':
      ClearTree(&ExSys);
      exit(30);
      break;
    case '1':
      Session(&ExSys);
      break;
    case '2':
      printf("Enter file name: ");
      GetStr(FileName, MAX_STR);
      SaveTree(FileName, ExSys);
      break;
    case '3':
      printf("Enter file name: ");
      GetStr(FileName, MAX_STR);
      LoadTree(FileName, &ExSys);
      break;
    case '4':
      DrawTree(ExSys);
      printf("\n");
      break;
    }
  ClearTree(&ExSys);
}
