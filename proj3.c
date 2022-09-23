#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

//global called in multiple places
int BoardPlacement[7][7];
int *BoardSpaceptr;
//One for the actual socket the other for the size
struct sockaddr_in Socket1;
struct sockaddr_in Socket2;
socklen_t Sizeadress;
int newsocket;
int ServerSocketet;
int clientsock;
int global_argc;
char **global_argv;
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
    close(ServerSocketet);
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
void Helper2(int i)
{
    if (i < 0 || i > 6)
    {
        printf("Not the right input");
        teardown();
    }
}
//returns values to make sure there valid
void AcceptInpt(int *p1RowVerify, int *p1ColumVerify)
{
    //I use temp just to store the actual numbers and not the adress so they can be checked
    int p1RowTemp = *p1RowVerify;
    int p1ColumTemp = *p1ColumVerify;

    // 9 is quit
    if (p1RowTemp == 9 || p1ColumTemp == 9)
    {
        printf("quit game");
        teardown();
    }

    Helper1(p1RowTemp);
    Helper1(p1ColumTemp);
}
void AcceptInpt2(int *p2RowVerify, int *p2ColumVerify)
{
    //I use temp just to store the actual numbers and not the adress so they can be checked

    int p2RowTemp = *p2RowVerify;
    int p2ColumTemp = *p2ColumVerify;

    // 9 is quit
    if (p2RowTemp == 9 || p2ColumTemp == 9)
    {
        printf("quit game");
        teardown();
    }

    Helper2(p2RowTemp);
    Helper1(p2ColumTemp);
}

int updatwState(int *p1RowVerify, int *p1ColumVerify)
{
    //multiple checkdisc for my sake to track which one is doing what
    int WinCode = 420;
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
    //reason for temp was to make sure it got number and not the adress to the number.
    int p1RowTemp = *p1RowVerify;
    int p1ColumTemp = *p1ColumVerify;
    BoardPlacement[p1RowTemp][p1ColumTemp] = p1;
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
                    return WinCode;
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
            if (BoardPlacement[j][i] == 1)
            {
                checkDisc3++;

                if (checkDisc3 == 4)
                {
                    printf("p1 Vertical win");
                    return WinCode;
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
            if (BoardPlacement[i][j] == 1 && BoardPlacement[i + 1][j + 1] == 1 && BoardPlacement[i + 2][j + 2] == 1 && BoardPlacement[i + 3][j + 3] == 1)
            {
                checkDisc5++;

                if (checkDisc5 == 1)
                {
                    printf("p1 Diagnal  win");
                    return WinCode;
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
            if (BoardPlacement[i][j] == 1 || BoardPlacement[i][j] == 2)
            {
                checkDiscFull++;
                if (checkDiscFull == 49)
                {
                    printf("Board is Full No More moves Available");
                    return WinCode;
                }
            }
            else
            {
                checkDiscFull = 0;
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
                    return WinCode;
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
            if (BoardPlacement[j][i] == 2)
            {
                checkDisc4++;

                if (checkDisc4 == 4)
                {
                    printf("p2 Vertical  win");
                    return WinCode;
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
            if (BoardPlacement[i][j] == 2 && BoardPlacement[i + 1][j + 1] == 2 && BoardPlacement[i + 2][j + 2] == 2 && BoardPlacement[i + 3][j + 3] == 2)
            {
                checkDisc6++;
                printf("%d  p2 Diagnal:\n", checkDisc6);
                if (checkDisc6 == 1)
                {
                    printf("p2 Diagnal  win");
                    return WinCode;
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
                    return WinCode;
                }
            }
            else
            {
                checkDiscFull = 0;
            }
    }
}
int updatwState2(int *p2RowVerify, int *p2ColumVerify)
{
    //multiple checkdisc for my sake to track which one is doing what
    int WinCode = 420;
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
    int p2RowTemp = *p2RowVerify;
    int p2ColumTemp = *p2ColumVerify;
    BoardPlacement[p2RowTemp][p2ColumTemp] = p2;
    // Array is not empty there are place holders find a way to get rid of them or tell them too look for 1 and 2
    // Horizontal should just check if four of the same is next to each other

    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 7; j++)
            if (BoardPlacement[i][j] == 2)
            {
                checkDisc2++;

                if (checkDisc2 == 4)
                {
                    printf("p2 horizontal win\n");
                    return WinCode;
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
            if (BoardPlacement[j][i] == 2)
            {
                checkDisc4++;

                if (checkDisc4 == 4)
                {
                    printf("p2 Vertical  win\n");
                    return WinCode;
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
            if (BoardPlacement[i][j] == 2 && BoardPlacement[i + 1][j + 1] == 2 && BoardPlacement[i + 2][j + 2] == 2 && BoardPlacement[i + 3][j + 3] == 2)
            {
                checkDisc6++;

                if (checkDisc6 == 1)
                {
                    printf("p2 Diagnal  win\n");
                    return WinCode;
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
                    printf("Board is Full No More moves Available\n");
                    return WinCode;
                }
            }
            else
            {
                checkDiscFull = 0;
            }
    }
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 7; j++)
            if (BoardPlacement[i][j] == 1)
            {
                checkDisc++;

                if (checkDisc == 4)
                {
                    printf("p1 horizontal win\n");
                    return WinCode;
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
            if (BoardPlacement[j][i] == 1)
            {
                checkDisc3++;

                if (checkDisc3 == 4)
                {
                    printf("p1 Vertical win\n");
                    return WinCode;
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
            if (BoardPlacement[i][j] == 1 && BoardPlacement[i + 1][j + 1] == 1 && BoardPlacement[i + 2][j + 2] == 1 && BoardPlacement[i + 3][j + 3] == 1)
            {
                checkDisc5++;

                if (checkDisc5 == 1)
                {
                    printf("p1 Diagnal  win\n");
                    return WinCode;
                }
            }
            else
            {
                checkDisc5 = 0;
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

void Intiteclient()
{
    //client

    struct sockaddr_in Clientadr;
    ((clientsock = socket(AF_INET, SOCK_STREAM, 0)) < 0);

    Clientadr.sin_family = AF_INET;
    Clientadr.sin_port = htons(atoi(global_argv[2]));
    if (inet_pton(AF_INET, global_argv[1], &Clientadr.sin_addr) <= 0)
    {
        printf("Invalid address \n");
        exit(0);
    }

    if (connect(clientsock, (struct sockaddr *)&Clientadr, sizeof(Clientadr)) < 0)
    {
        printf("Connection Failed \n");
        exit(0);
    }
}

void Initserver()
{
    //server
    printf("making new server\n");

    int ServerSocketet = socket(PF_INET, SOCK_STREAM, 0);
    if (ServerSocketet == -1)
    {
        printf("Socket creation error.\n");
        exit(0);
    }
    Socket1.sin_port = htons(8080);
    Socket1.sin_addr.s_addr = INADDR_ANY;
    Socket1.sin_family = AF_INET;
    int YouBetterBind = bind(ServerSocketet, (struct sockaddr *)&Socket1, sizeof(Socket1));

    printf("The Server IP is:%s\n", inet_ntoa(Socket1.sin_addr));
    if ((listen(ServerSocketet, 1)) == -1)
    {
        printf("I cant hear nothing\n");
        exit(0);
    }
    Sizeadress = sizeof(Socket2);

    if ((newsocket = accept(ServerSocketet, (struct sockaddr *)&Socket2, (socklen_t *)&Sizeadress)) < 0)
    {
        printf("accept");
        exit(0);
    }
}

int main(int argc, char *argv[])
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
    int buff[1000];
    int buff2[1000];
    int Win1 = 0;
    int Win2 = 0;
    global_argc = argc;
    global_argv = argv;
    if (argc < 2)
    {
        //Server function
        Initserver();
        while (1)
        {
            // here is p1 choices
            printf("Player 1 choose your row and colum please\n");
            scanf("%d", &p1Row);
            scanf("%d", &p1Colum);
            AcceptInpt(&p1Row, &p1Colum);
            Win1 = updatwState(&p1Row, &p1Colum);
            //here is send and reecive
            read(newsocket, buff, 1000);
            read(newsocket, buff2, 1000);
            send(newsocket, &p1Row, 1000, 0);
            send(newsocket, &p1Colum, 1000, 0);
            AcceptInpt2(buff, buff2);
            Win2 = updatwState2(buff, buff2);
            Display();

            if ((Win1 == 420) || (Win2 == 420))
            {

                teardown();
            }
        }
    }
    else
    {
        //client Function
        Intiteclient();

        while (1)
        {
            //here is where p2 gives input
            printf("Player 2 choose your row and colum please\n");
            scanf("%d", &p2Row);
            scanf("%d", &p2Colum);
            AcceptInpt2(&p2Row, &p2Colum);
            Win1 = updatwState2(&p2Row, &p2Colum);
            //send and receive portion of project
            send(clientsock, &p2Row, 1000, 0);
            send(clientsock, &p2Colum, 1000, 0);
            read(clientsock, buff, 1000);
            read(clientsock, buff2, 1000);
            AcceptInpt(buff, buff2);
            Win2 = updatwState(buff, buff2);
            Display();
            //win if win code is recieved it tearsdown
            if ((Win1 == 420) || (Win2 == 420))
            {

                teardown();
            }
        }
    }
    return 0;
}
