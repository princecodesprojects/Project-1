#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <windows.h>
int readEnterKey();
void swap(int *x,int *y);

//creating matrix
void createMatrix(int arr[][4])
{
    int n=15;
  int num[n],i,j;
  for(i=0;i<15;i++)
  num[i]=i+1; // These 1-15 number will be in th matrix

  srand(time(NULL));  // for random number generation

  int lastIndex=n-1,index;

  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
        if(lastIndex>=0)
        {
            index=rand()%(lastIndex+1); // idea : performing % operation by (lastIndex+1) to get index value
            arr[i][j]=num[index];// will give index , so put that num[index] number in matrix
            num[index] = num[lastIndex--]; // and replace last number with this indexed positioned number
                                           // and finally lastIndex--
        }
    }
  }
  arr[i - 1][j - 1] = 0; // last number is zero
}

//Game Rule

void gameRule(int arr[][4])
{
    system("cls");

    int i, j, k = 1;

    printf("                                MATRIX PUZZLE    \n\n\n");
    printf("                               RULE OF THIS GAME    \n\n");
    printf("1.You can move only 1 step at a time by arrow key\n");
    printf("          Move Up    : by Up arrow key\n");
    printf("          Move Down  : by Down arrow key\n");
    printf("          Move Left  : by Left arrow key\n");
    printf("          Move Right : by Right arrow key\n");
    printf("2.You can move number at empty position only\n\n");
    printf("3.For each valid move : your total number of move will decreased by 1\n");
    printf("4.Winning situation    : Number in 4*4 matrix should be in order from 1 to 15\n\n");
    printf("          winnign situation:\n");

    for(i=0;i<4;i++)
    {
        printf("| ");
        for(j=0;j<4;j++)
        {
            if(arr[i][j]!=0)
            printf("%2d | ",4*i+j+1);
            else
            printf("   |");
        }
        printf("\n");
    }

    printf("\n\n");
    printf("1.You can exit the game at any time by pressing \'E\' or \'e\' \n");
    printf("So try to win in minimum number of move\n\n");
    printf("Enter any key to start.......\n");

    int x=readEnterKey();
}

// Reads the user input character and return ascii value of that
int readEnterKey()
{
    char c;
    c=_getch();
    if(c==-32)
    c=_getch();

    return c;
}

// winning check by this function

int winner(int arr[][4])
{
    int i,j,k=1;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++,k++)
        {
            if(arr[i][j]!=k && k!=16)
            break;
        }
        if (j < 4)
            break;
    }
    if(j<4)
       return 0;
    return 1;
}

// showing matrix
void showMatrix(int arr[][4])
{
    int i,j;
    printf("--------------------\n");
    for(i=0;i<4;i++)
    {
        printf(" | ");
        for(j=0;j<4;j++)
        {
            if(arr[i][j]!=0)
            printf("%2d | ",arr[i][j]);
            else
            printf("   | ");
        }
        printf("\n");
    }
    printf("--------------------\n");
}

// shift up function

int shiftUp(int arr[][4])
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(arr[i][j]==0)
            break;

        }
        if(j<4)
        break;
    }
    if(i==3)
    return 0;

    //Successfully swapped two numbers !
    swap(&arr[i][j],&arr[i+1][j]);
    return 1; //success
}

int shiftDown(int arr[][4])
{
    int i,j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (i == 0) // shifting not possible
        return 0;
   swap(&arr[i][j],&arr[i-1][j]);
   return 1;//successfull
}

int shiftRight(int arr[][4])
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(arr[i][j]==0)
            break;
        }
        if(j<4)
        break;
    }
    if(i==0)
    return 0;
    swap(&arr[i][j],&arr[i][j-1]);
    return 1;
}

int shiftLeft(int arr[][4])
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(arr[i][j]==0)
            break;
        }
        if(j<4)
        break;
    }
    if(i==0)
    return 0;
    swap(&arr[i][j],&arr[i][j+1]);
    return 1;
}

// swap function to swap two numbers
void swap(int *x,int *y)
{
     *x=*x+*y;
    *y=*x-*y;
    *x=*x-*y;
    printf("");
}

int main()
{
    int arr[4][4]; //create matrix

    int maxTry=4;  //max try

    char name[30];
    printf("Player Name:");
    gets(name);
     
     system("cls");  //clear screen

     while(1)
     {
        createMatrix(arr); // calling function to create  matrix
        gameRule(arr);
        
        while(!winner(arr)) // checking for winning situation
        {

           system("cls");
            if (!maxTry) // for remaining zero move
                break;

                printf("\n\n  Player Name:  %s ,  Move remaining : %d\n\n", name, maxTry);

                showMatrix(arr); // show matrix

                int key=readEnterKey(); // this will return ascii code of user entered key

                switch(key)
                {
                   case 101://ascii of E
                   case 69://ascii of e
                   printf("\a\a\a\a\a\a\n     Thanks for Playing ! \n\a");
                printf("\nHit 'Enter' to exit the game \n");
                key = readEnterKey();
                return 0;

                case 72://arrow up 
                if(shiftUp(arr))
                maxTry--;
                break;
                case 80: // arrow down
                if (shiftDown(arr))
                    maxTry--;
                break;
                case 77: // arrow  right
                if (shiftRight(arr))
                    maxTry--;
                break;
                case 75: // arrow left
                if (shiftLeft(arr))
                    maxTry--;
                     break;

                     default:

                printf("\n\n      \a\a Not Allowed \a");
                }
        }

        if(!maxTry)
        printf("          You Lose\n");
        else
        printf("\n\a!!!!!!!!!!!!!Congratulations  %s for winning this game !!!!!!!!!!!!!\n\a",name);

        fflush(stdin); // Will clear the buffer

        char check;
        printf("\nWant to play again ? \n");
        printf("enter 'y' to play again:  ");
        scanf("%c", &check);

        // Leave the game here itself !
        if ((check != 'y') && (check != 'Y'))
            break;

          maxTry = 4;  
     }
     return 0;
}