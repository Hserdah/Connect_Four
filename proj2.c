#include <stdio.h>
#include <stdlib.h>
//global called in multiple places
int BoardPlacement[7][7];
int *BoardSpaceptr;

int *Initialization()
{
	//making space for the game in memory
	int **BoardSpace = (int **)malloc(7 * sizeof(int *));
	for (int i = 0; i < 7; i++)
	{
		BoardSpace[i] = (int *)malloc(7 * sizeof(int));

		return BoardSpace[i];
	}
}

void teardown()
{
	exit(0);
	free(BoardSpaceptr);
}
//quits game if not valid
//used to not fluff the project
void Helper1(int i)
{
	if (i < 0 || i > 6)
	{
		printf("Not the right input");
		teardown();
	}
}

//returns values to make sure there valid
void AcceptInpt(int *p1RowVerify, int *p1ColumVerify, int *p2RowVerify, int *p2ColumVerify)
{
	//I use temp just to store the actual numbers and not the adress so they can be checked
	int p1RowTemp = *p1RowVerify;
	int p1ColumTemp = *p1ColumVerify;
	int p2RowTemp = *p2RowVerify;
	int p2ColumTemp = *p2ColumVerify;

	// 9 is quit
	if (p1RowTemp == 9 || p1ColumTemp == 9 || p2RowTemp == 9 || p2ColumTemp == 9)
	{
		printf("quit game");
		teardown();
	}

	Helper1(p1RowTemp);
	Helper1(p1ColumTemp);
	Helper1(p2RowTemp);
	Helper1(p2ColumTemp);
}

void updatwState(int *p1RowVerify, int *p1ColumVerify, int *p2RowVerify, int *p2ColumVerify)
{
	//multiple checkdisc for my sake to track which one is doing what
	int i;
	int j;
	int checkDisc = 0;
	int checkDisc2 = 0;
	int checkDisc3 = 0;
	int checkDisc4 = 0;
	int checkDisc5 = 0;
	int checkDisc6 = 0;
	int checkDiscFull = 0;
	int p1 = 1;
	int p2 = 2;
	//reason for temp was to make sure it got number and not the adress to the number.
	int p1RowTemp = *p1RowVerify;
	int p1ColumTemp = *p1ColumVerify;
	int p2RowTemp = *p2RowVerify;
	int p2ColumTemp = *p2ColumVerify;
	BoardPlacement[p1RowTemp][p1ColumTemp] = p1;
	BoardPlacement[p2RowTemp][p2ColumTemp] = p2;
	// Array is not empty there are place holders find a way to get rid of them or tell them too look for 1 and 2
	// Horizontal should just check if four of the same is next to each other
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
			if (BoardPlacement[i][j] == 1)
			{
				checkDisc++;

				if (checkDisc == 4)
				{
					printf("p1 horizontal win");
					teardown();
				}
			}
			else
			{
				checkDisc = 0;
			}
	}
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
			if (BoardPlacement[i][j] == 2)
			{
				checkDisc2++;

				if (checkDisc2 == 4)
				{
					printf("p2 horizontal win");
					teardown();
				}
			}
			else
			{
				checkDisc2 = 0;
			}
	}
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
			if (BoardPlacement[j][i] == 1)
			{
				checkDisc3++;

				if (checkDisc3 == 4)
				{
					printf("p1 Vertical win");
					teardown();
				}
			}
			else
			{
				checkDisc3 = 0;
			}
	}
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
			if (BoardPlacement[j][i] == 2)
			{
				checkDisc4++;

				if (checkDisc4 == 4)
				{
					printf("p2 Vertical  win");
					teardown();
				}
			}
			else
			{
				checkDisc4 = 0;
			}
	}
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
			if (BoardPlacement[i][j] == 1 && BoardPlacement[i + 1][j + 1] == 1 && BoardPlacement[i + 2][j + 2] == 1 && BoardPlacement[i + 3][j + 3] == 1)
			{
				checkDisc5++;

				if (checkDisc5 == 1)
				{
					printf("p1 Diagnal  win");
					teardown();
				}
			}
			else
			{
				checkDisc5 = 0;
			}
	}

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
			if (BoardPlacement[i][j] == 2 && BoardPlacement[i + 1][j + 1] == 2 && BoardPlacement[i + 2][j + 2] == 2 && BoardPlacement[i + 3][j + 3] == 2)
			{
				checkDisc6++;
				printf("%d  p2 Diagnal:\n", checkDisc6);
				if (checkDisc6 == 1)
				{
					printf("p2 Diagnal  win");
					teardown();
				}
			}
			else
			{
				checkDisc6 = 0;
			}
	}

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
			if (BoardPlacement[i][j] == 1 || BoardPlacement[i][j] == 2)
			{
				checkDiscFull++;
				if (checkDiscFull == 49)
				{
					printf("Board is Full No More moves Available");
					teardown();
				}
			}
			else
			{
				checkDiscFull = 0;
			}
	}
}

void Display()
{
	int i;
	int j;
	for (i = 6; i >= 0; i--)
	{
		printf("  ");
		for (j = 0; j < 6; j++)
		{
			printf("|");
			if (BoardPlacement[i][j] == 0)
				printf(" ");
			else if (BoardPlacement[i][j] == 1)
				printf("x");
			else if (BoardPlacement[i][j] == 2)
				printf("o");
		}
		printf("|\n");
	}
}

int main()
{
	//gm as in game master
	// namechoice0 and namechoice00 is to diffrentiate the variables at top fuction
	//gave them a 100 just in case name is really long or user is trying to break the game
	char gmchoice;
	char name0[100];
	char name00[100];
	char namechoice0;
	int p1Row;
	int p1Colum;
	int p2Row;
	int p2Colum;
	char ret1;
	char ret2;
	printf("What is the name of player one?");
	scanf("%s", name0);
	printf("What is the name of player two?");
	scanf("%s", name00);
	printf("Do you want to start the game? y/n:");
	gmchoice = getchar();
	scanf("%c", &gmchoice);
	if (gmchoice == 'y')
	{
		printf("works\r\n");
		do
		{
			printf("If Wanting to quit or choosing any numbers below 1 or above 7 WILL QUIT THE GAME BE WARNED\n");
			printf("9 ends the game if you don't want to play anymore\n");
			printf("Player 1 choose your row and colum please\n");
			scanf("%d", &p1Row);
			scanf("%d", &p1Colum);
			printf("Player 2 choose your row and colum please\n");
			scanf("%d", &p2Row);
			scanf("%d", &p2Colum);
			AcceptInpt(&p1Row, &p1Colum, &p2Row, &p2Colum);
			updatwState(&p1Row, &p1Colum, &p2Row, &p2Colum);
			Display();
		} while (1);
	}
	if (gmchoice == 'n')
	{
		printf("goodbye");
		exit(0);
	}
	return 0;
}
