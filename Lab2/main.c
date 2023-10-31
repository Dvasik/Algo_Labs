/* Dvas Pavel, 5030102/20002 */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "list2.h"

void main( void )
{
  InitList();
  LoadDB("ab.db");
  AddToList("Dfff", "+71211804560");
  AddToList("Dvas", "+79211804560");
  AddToList("Danasenko", "+88005553535");
  AddToList("Aarr", "+123123123");
  AddToList("B", "+123123");
  AddToList("FFf", "+12315667");
  //DelFromList("Dvas", "+79211804560");
  SortList('D');
  FindContact("Dvas");
  FindContact("Danasenko");
  SaveDB("ab.db");
  ClearList();
  _getch();
}
