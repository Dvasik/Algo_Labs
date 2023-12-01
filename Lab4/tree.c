/* Pavel Dvas */

#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "tree.h"

TREE * Init( char *Text, TREE *N, TREE *Y )
{
  TREE *T = malloc(sizeof(TREE));

  if (T == NULL)
    return NULL;

  strncpy(T->Text, Text, MAX_STR - 1);
  T->No = N;
  T->Yes = Y;
  return T;
}

void DrawTree( TREE *T )
{
  if (T == NULL)
  {
    printf("*");
    return;
  }
  printf("%s(", T->Text);
  DrawTree(T->Yes);
  printf(",");
  DrawTree(T->No);
  printf(")");
}

void Session( TREE **T )
{
  char key, Qst[MAX_STR], Ans[MAX_STR];

  if (*T == NULL)
    return;
  
  while (1)
  {
    printf("%s?\n", (*T)->Text);
    key = _getch();
    printf(key == 'Y' || key == 'y' ? "Yes\n" : "No\n");
    if ((key == 'Y' || key == 'y') && ((*T)->Yes == NULL))
    {
      printf("Your answer is: %s\n", (*T)->Text);
      return;
    }
    if ((*T)->Yes != NULL)
      key == 'Y' || key == 'y' ? (T = &(*T)->Yes) : (T = &(*T)->No);
    else
    {
      printf("Then enter a new definition:");
      GetStr(Qst, MAX_STR);
      printf("Enter the correct answer:");
      GetStr(Ans, MAX_STR);
      *T = Init(Qst, *T, Init(Ans, NULL, NULL));
      return;
    }
  }
}

void SaveTreeRec( FILE *F, TREE *T )
{
  if (T == NULL)
    return;
  fwrite(T, sizeof(TREE), 1, F);
  SaveTreeRec(F, T->No);
  SaveTreeRec(F, T->Yes);
}

int SaveTree( char *FileName, TREE *T )
{
  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
    return 0;

  SaveTreeRec(F, T);
  fclose(F);
  return 1;
}

void LoadTreeRec( FILE *F, TREE **T )
{
  TREE tr;

  if (fread(&tr, sizeof(TREE), 1, F) != 1)
    return;

  *T = Init(tr.Text, NULL, NULL);
  if (tr.No != NULL)
    LoadTreeRec(F, &(*T)->No);
  if (tr.Yes != NULL)
    LoadTreeRec(F, &(*T)->Yes);
}

int LoadTree( char *FileName, TREE **T )
{
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;

  LoadTreeRec(F, T);
  fclose(F);
  return 1;
}

void ClearTree( TREE **T )
{
  if (*T != NULL)
  {
    ClearTree(&(*T)->Yes);
    ClearTree(&(*T)->No);
    free(*T);
    *T = NULL;
  }
}

