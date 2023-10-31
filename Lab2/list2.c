/* Dvas Pavel, 5030102/20002 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list2.h"

LIST Base[26];

void InitList( void )
{
  int i;

  for (i = 0; i < 26; i++)
    Base[i].Letter = 'A' + i;
}

int AddToList( char *NewSurName, char *NewPhoneNum )
{
  CONTACT *NewElement;
  int ind;

  if ((NewElement = malloc(sizeof(CONTACT))) == NULL)
    return 0;

  strcpy(NewElement->PhoneNum, NewPhoneNum);
  strcpy(NewElement->SurName, NewSurName);

  ind = NewElement->SurName[0] - 'A';

  if (ind < 0 || ind > 25)
    return 0;

  NewElement->Next = Base[ind].Head;
  if (Base[ind].Head != NULL)
    Base[ind].Head->Prev = NewElement;
  NewElement->Prev = NULL;
  Base[ind].Head = NewElement;
  return 1;
}

int AddToListBack( char *NewSurName, char *NewPhoneNum )
{
  CONTACT *NewElement, *OldFirst, **Curr;
  int ind;

  if ((NewElement = malloc(sizeof(CONTACT))) == NULL)
    return 0;

  strcpy(NewElement->PhoneNum, NewPhoneNum);
  strcpy(NewElement->SurName, NewSurName);

  ind = NewElement->SurName[0] - 'A';

  if (ind < 0 || ind > 25)
    return 0;

  Curr = &Base[ind].Head;

  OldFirst = NULL;

  while ((*Curr) != NULL)
  {
    OldFirst = *Curr;
    Curr = &(*Curr)->Next;
  }

  NewElement->Next = NULL;
  if (OldFirst != NULL)
    OldFirst->Next = NewElement;
  NewElement->Prev = OldFirst;
  *Curr = NewElement;
  return 1;
}

void DelFromList( char *OldSurName, char *OldPhoneNum )
{
  CONTACT *Prev = NULL, *Curr;
  int ind;

  ind = OldSurName[0] - 'A';

  if (ind < 0 || ind > 25)
    return;

  Curr = Base[ind].Head;

  while (Curr != NULL)
  {
    if (strcmp(Curr->SurName, OldSurName) == 0 && strcmp(Curr->PhoneNum, OldPhoneNum) == 0)
    {
      if (Prev == NULL)
      {
        Base[ind].Head = Curr->Next;
        Base[ind].Head->Prev = Curr->Prev;
      }
      else
      {
        Prev->Next = Curr->Next;
        if (Curr->Next != NULL)
          Curr->Next->Prev = Curr->Prev;
      }
      free(Curr);
      Curr = NULL;
      return;
    }
    Prev = Curr;
    Curr = Curr->Next;
  }
}

char * FindContact( char *SurName )
{
  int ind;
  CONTACT *Curr;

  ind = SurName[0] - 'A';

  if (ind < 0 || ind > 25)
    return NULL;

  Curr = Base[ind].Head;

  while (Curr != NULL)
  {
    if (strcmp(Curr->SurName, SurName) == 0)
      return Curr->PhoneNum;
    Curr = Curr->Next;
  }
  return NULL;
}

int SaveDB( char *FileName )
{
  FILE *F;
  int i;
  CONTACT *Curr;

  if ((F = fopen(FileName, "wb")) == NULL)
    return 0;

  for (i = 0; i < 26; i++)
  {
    Curr = Base[i].Head;
    while (Curr != NULL)
    {
      fwrite(Curr, sizeof(CONTACT), 1, F);
      Curr = Curr->Next;
    }
  }

  fclose(F);
  return 1;
}

int LoadDB( char *FileName )
{
  FILE *F;
  CONTACT Curr;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;

  while (!feof(F))
  {
    if (fread(&Curr, sizeof(Curr), 1, F) == 1)
      AddToListBack(Curr.SurName, Curr.PhoneNum);
  }

  fclose(F);
  return 1;
}

void SortList( char C )
{
  int ind;
  CONTACT *Curr;

  ind = C - 'A';

  if (ind < 0 || ind > 25)
    return;

  Curr = Base[ind].Head;

  while (Curr != NULL)
  {
    CONTACT *min = Curr, *tmp = Curr->Next;

    while (tmp != NULL)
    {
      if (strcmp(min->SurName, tmp->SurName) > 0)
        min = tmp;
      tmp = tmp->Next;
    }

    if (min != Curr)
    {
      char tmpSN[MAX_NAME_SIZE], tmpPN[PHONE_LENGTH];

      strcpy(tmpSN, Curr->SurName);
      strcpy(tmpPN, Curr->PhoneNum);

      strcpy(Curr->SurName, min->SurName);
      strcpy(Curr->PhoneNum, min->PhoneNum);

      strcpy(min->SurName, tmpSN);
      strcpy(min->PhoneNum, tmpPN);
    }
    
    Curr = Curr->Next;
  }
}

void ClearList( void )
{
  int i;

  for (i = 0; i < 26; i++)
  {
    CONTACT **Curr = &Base[i].Head;

    if (*Curr == NULL)
      return;
    while ((*Curr)->Prev != NULL)
      Curr = &(*Curr)->Prev;
    while (*Curr != NULL)
    {
      CONTACT *tmp;

      tmp = *Curr;
      *Curr = (*Curr)->Next;
      if (*Curr == NULL)
      {
        free(tmp);
        return;
      }
      else
        free(tmp);
    }
  }
}