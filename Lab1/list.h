/* Dvas Pavel, 5030102/20002 */

typedef struct tagLIST LIST;

struct tagLIST
{
  char *Str;
  int StrLen;
  LIST *Next;
};

void DisplayTenMost( LIST *L );

void DisplaySpecLen( LIST *L, int N );

int AddToListSorted( LIST **L, char *NewStr, int NewStrLen );
void DelFromListFront( LIST **L );

void ClearList( LIST **L );
