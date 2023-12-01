/* Pavel Dvas  */

#define MAX_STR 102

typedef struct tagTREE TREE;
struct tagTREE
{
  char Text[MAX_STR];
  TREE *No, *Yes;
};

void GetStr( char *Str, int MaxLen );

void Session( TREE **T );

TREE * Init( char *Text, TREE *N, TREE *Y );

int SaveTree( char *FileName, TREE *T );
int LoadTree( char *FileName, TREE **T );

void DrawTree( TREE *T );
void ClearTree( TREE **T );

