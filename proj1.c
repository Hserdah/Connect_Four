#include <stdio.h>
#include <stdlib.h>
void Names(char name1[100], char name2[100])
{
	//This function should just store the names incase we wish to call them later
}
//the flow start game go to accept->update->display

const char AcceptInpt(const char storechoice)
{
	//array for valid letters
	char AcceptLetter[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'Q'};
	int result;
	do
	{
		for (int i = 0; i < 8; i++)
		{
			//is the letter valid?
			if (storechoice == AcceptLetter[i])
			{
				result = (storechoice);

				break;
			}
		}
		//I end the game if user is malicious and want to put a whole bunch of charecters overiding memory
		if (result != storechoice)
		{
			printf("hey man look A-G is the choices and Q is quit everything else ends the game srry");
			exit(0);
		}

	} while (result != storechoice);
	return storechoice;
}
//if A then win, else B-G continue the loop,Also Q would send quit game
const char updatwState(char choice)
{
	do
	{
		if (choice == 'A')
		{
			//win
			break;
		}
		if (choice == 'Q')
		{

			break;
		}
	} while (choice == 'A' || choice == 'Q');
	return choice;
}
void Display(char board)
{

	if (board == 'A')
	{
		printf("Winner winner chicken dinner\r\n");
	}
	//ends game here so loop can be uninterrupted
	if (board == 'Q')
	{
		printf("destroying game\r\n");
		exit(0);
	}
}
//all this does is just print results
//i.e "you win!" if user has chosen A

int main()
{
	//gm as in game master
	// namechoice0 and namechoice00 is to diffrentiate the variables at top fuction
	//gave them a 100 just in case name is really long or user is trying to break the game
	char gmchoice;
	char name0[100];
	char name00[100];
	char namechoice0;
	char ret1;
	char ret2;
	printf("What is the name of player one?");
	scanf("%s", name0);
	printf("What is the name of player two?");
	scanf("%s", name00);
	Names(name0, name00);
	printf("Do you want to start the game? y/n");
	gmchoice = getchar();
	scanf("%c", &gmchoice);
	if (gmchoice == 'y')
	{
		printf("works\r\n");
		//loop is right here
		//I know you can skip ret1 and ret2 but it was easier fo me to assign variables for output and pass them.
		do
		{
			namechoice0 = getchar();
			scanf("%c", &namechoice0);
			ret1 = AcceptInpt(namechoice0);
			ret2 = updatwState(ret1);
			Display(ret2);
		} while (namechoice0 != 'A');
		//ends the game if you decide to play amoung us instead
	}
	if (gmchoice == 'n')
	{
		printf("goodbye");
		exit(0);
	}
	return 0;
}
