/* Dvas Pavel, 5030102/20002 */

#define MAX_NAME_SIZE 100
#define PHONE_LENGTH 13

typedef struct tagCONTACT CONTACT;

struct tagCONTACT
{
  char SurName[MAX_NAME_SIZE];
  char PhoneNum[PHONE_LENGTH];
  CONTACT *Next, *Prev;
};

typedef struct LIST
{
  char Letter;

  CONTACT *Head;
} LIST;

void InitList( void );

int AddToList( char *NewSurName, char *NewPhoneNum );
void DelFromList( char *OldSurName, char *OldPhoneNum );

char * FindContact( char *SurName );

void SortList( char C );

int SaveDB( char *FileName );
int LoadDB( char *FileName );

void ClearList( void );
