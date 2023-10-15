/* Dvas Pavel, 5030102/20002 */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "list.h"

void main( void )
{
  FILE *F;
  char ch;
  char *str;
  int str_len, cap = 10, i;
  LIST *L = NULL;

  if ((F = fopen("test.txt", "r")) == NULL)
    return;

  do
  {
    ch = fgetc(F);
    str_len = 0;
    if ((str = (char *)malloc(cap)) == NULL)
      return;
    while (ch != '\n' && ch != EOF)
    {
      str[str_len++] = ch;

      if (str_len >= cap)
      {
        cap *= 2;
        str = (char *)realloc(str, cap);
      }
      ch = fgetc(F);
    }
    str[str_len++] = '\0';
    AddToListSorted(&L, str, str_len);
    free(str);
  } while (ch != EOF);

  DisplayTenMost(L);

  printf("Check if string with specific length exists: ");
  scanf("%i", &i);
  DisplaySpecLen(L, i);
  fclose(F);
  ClearList(&L);
  _getch();
}
