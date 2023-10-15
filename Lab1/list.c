/* Dvas Pavel, 5030102/20002 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int ListLength;

void DisplayTenMost( LIST *L )
{
  int N = ListLength;

  if (L == NULL)
    printf("<empty list>\n");
  else
    while (L != NULL)
    {
      while (N > 10)
        L = L->Next, N--;
      printf("%s %i\n", L->Str, L->StrLen);
      printf((L->Next == NULL) ? "\n" : "");
      L = L->Next;
    }
}

void DisplaySpecLen( LIST *L, int N )
{
  if (L == NULL)
    printf("<empty list>\n");
  else
    while (L != NULL)
    {
      if (L->StrLen == N)
      {
        printf("%s %i\n", L->Str, L->StrLen);
        printf((L->Next == NULL) ? "\n" : "");
      }
      L = L->Next;
    }
}

int AddToListSorted( LIST **L, char *NewStr, int NewStrLen )
{
  LIST *NewElement;

  if ((NewElement = malloc(sizeof(LIST))) == NULL)
    return 0;
  if ((NewElement->Str = (char *)malloc(NewStrLen)) == NULL)
    return 0;

  if (*L == NULL)
  {
    strcpy(NewElement->Str, NewStr);
    NewElement->StrLen = NewStrLen - 1;
    NewElement->Next = *L;
    *L = NewElement;
    ListLength++;

    return 1;
  }

  while ((*L)->Next != NULL && (*L)->StrLen < NewStrLen)
    L = &(*L)->Next;

  if ((*L)->StrLen < NewStrLen)
    L = &(*L)->Next;

  strcpy(NewElement->Str, NewStr);
  NewElement->StrLen = NewStrLen - 1;
  NewElement->Next = *L;
  *L = NewElement;
  ListLength++;
  return 1;
}

void DelFromListFront( LIST **L )
{
  LIST *Old = *L;

  if (*L == NULL)
    return;
  *L = (*L)->Next;
  free(Old->Str);
  ListLength--;
  Old->StrLen = 0;
  free(Old);
  Old = NULL;
}

void ClearList( LIST **L )
{
  if (*L == NULL)
    return;

  while (*L != NULL)
    DelFromListFront(L);
}