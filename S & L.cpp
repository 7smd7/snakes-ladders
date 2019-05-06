#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
using namespace std;

int nPlayer;
int size;
int level;
int nSnake,nLadder;
int diceCounter;
int sixCounter;
int maxRank;

struct Player{
    string name;
    int position=0;
    bool valid=false;  //valid to login ground
    int rank=0;
    int diceCounter=0;
    int sixCounter=0;
};
Player *player;          //player dynamic array

struct Snake{
    int position;
    int desceding;
};
Snake *snake;

struct Ladder{
    int position;
    int asceding;
};
Ladder *ladder;

int Dice();
void writeName();
void setnPlayer();
void setSize();
void setLevel();
void showDice(int dice);
void setSnake();
void setLadder();
void printPositionSL(int iPosition);
void validSL();
void setName();
void getReport();
void printPositionP(int iPosition);
void table();
void checkSL(int iPlayer);
void showRank();
void refresh();
void save();
void load();
void input();


int main()
{
    int nS,nL;
    srand((unsigned)time(NULL));

    //intro
    writeName();
    getch();
    system("cls");

    cout<<"if you want to load a game, press enter";
    if(int(getch())==13)
        load();
    else
    {system("cls");

    //set player
    cout<<"enter the number of player: ";
    setnPlayer();
    player=new Player[nPlayer];
    setName();

    //set size of table

    cout<<"please enter the size of cells: ";
    setSize();

    //set level

    cout<<"do you want play on level 1 or 2? ";
    setLevel();
    system("cls");

    cout<<"please wait to make table...";


    //set number of S & L with value of level
    if (level==1 )
    {
    nS=1*size/3;
    nL=1*size/3;
    }
    else
    {
    nS=2*size/3;
    nL=1*size/3;
    }

    nSnake=nS;
    nLadder=nL;

    //S&L dynamic array

    snake=new Snake[nSnake];

    ladder=new Ladder[nLadder];

    setSnake();
    setLadder();
    validSL();      //check that never put two object in one cell

    diceCounter=nPlayer;   //diceCounter=nPlayer because when it start with lower than nPlayer we will have logical error
    sixCounter=0;
    maxRank=0;
    }

    int iPlayer;
    int dice;

    while(true)
    {
        refresh();

        iPlayer=(diceCounter-sixCounter)%nPlayer;

        //skip player for throw dice when some player finish the game
        while(player[iPlayer].rank>0)
            {
                iPlayer++;
                if(iPlayer>=nPlayer)
                    iPlayer=0;
            }

        cout<<player[iPlayer].name<<" please press enter to throw dice";
        input();
        dice=Dice();
        player[iPlayer].diceCounter++;
        diceCounter++;
        if(player[iPlayer].valid==false && player[iPlayer].diceCounter>dice)        // random set dice 6 for set valid login player
            dice=6;
        refresh();

        if (player[iPlayer].valid==true)
        {
            if (player[iPlayer].position+dice<=size*size)
                {
                    player[iPlayer].position+=dice;
                    refresh();
                    cout<<player[iPlayer].name<<"'s result:"<<endl;

                    if(player[iPlayer].position==size*size)
                    {
                        maxRank++;
                        player[iPlayer].rank=maxRank;

                        refresh();
                        cout<<player[iPlayer].name<<"'s result:"<<endl;
                        if(player[iPlayer].rank<nPlayer)
                            cout<<player[iPlayer].name<<" congratulations! you win the game with rank: "<<player[iPlayer].rank<<endl;
                        else
                        {
                            cout<<" sry! you lost the game ^_^\n\n";
                            cout<<"please enter a key to show score board...";
                            input();
                            system("cls");
                            cout<<"result of this game:\n";
                            showRank();
                            cout<<"\n\nenter a key to exit game...";
                            input();
                            exit(0);
                        }


                    }
                    else
                        checkSL(iPlayer);
                }
            else
                {
                    refresh();
                    cout<<player[iPlayer].name<<"'s result:"<<endl;
                    cout<<"sry! you can't move."<<endl;
                }


            if (dice==6)
            {
                cout<<"\acongratulations! you can throw dice again, because you get six\n";
                sixCounter++;
                player[iPlayer].sixCounter++;
            }
        }
        else if (dice==6)
            {
                cout<<player[iPlayer].name<<"'s result:"<<endl;
                cout<<"\acongratulations! you can login to game, because you get first six\n";
                player[iPlayer].valid=true;
                sixCounter++;
            }
        else
            {
                cout<<player[iPlayer].name<<"'s result:"<<endl;
                cout<<"***you get "<<dice<<", you can't move until get six***\n";
            }

        showDice(dice);

        cout<<endl;
        cout<<"press a key...(see the help of key)";
        input();
    }

    delete [] player;
    delete [] snake;
    delete [] ladder;

  return 0;
}

void writeName()
{

        cout<<"[..       [..            [..                                                            [.."<<endl;
        cout<<"[. [..   [...            [..                                                            [.."<<endl;
        cout<<"[.. [.. [ [..    [..     [..         [..     [... [.. [..  [... [.. [..      [..        [.."<<endl;
        cout<<"[..  [..  [..  [..  [..  [. [.     [..  [..   [..  [.  [..  [..  [.  [..  [..  [..  [.. [.."<<endl;
        cout<<"[..   [.  [.. [..    [.. [..  [.. [..   [..   [..  [.  [..  [..  [.  [.. [..   [.. [.   [.."<<endl;
        cout<<"[..       [..  [..  [..  [.   [.. [..   [..   [..  [.  [..  [..  [.  [.. [..   [.. [.   [.."<<endl;
        cout<<"[..       [..    [..     [..  [..   [.. [... [...  [.  [.. [...  [.  [..   [.. [... [.. [.."<<endl;
        cout<<endl;
        cout<<"[.....                                                         "<<endl;
        cout<<"[..   [..                                                  [.. "<<endl;
        cout<<"[..    [..   [..     [. [... [..   [..   [..     [.. [..       "<<endl;
        cout<<"[..    [.. [..  [..   [..     [.. [..  [..  [..   [..  [.. [.. "<<endl;
        cout<<"[..    [..[..   [..   [..       [...  [..   [..   [..  [.. [.. "<<endl;
        cout<<"[..   [.. [..   [..   [..        [..  [..   [..   [..  [.. [.. "<<endl;
        cout<<"[.....      [.. [... [...       [..     [.. [... [...  [.. [.. "<<endl;


}

int Dice()
{
    srand((unsigned)time(NULL));
    return rand()%6+1;
}

void setName(){
    cout<<"enter the player's name: ";
    for(int iPlayer=0; iPlayer<nPlayer; iPlayer++)
        {
        cin>>player[iPlayer].name;
        }
}

void getReport(){

    int maxLength=0;
    bool validPrintRank=false;
    for(int iPlayer=0; iPlayer<nPlayer; iPlayer++)          //for arrange score board
    {
        if(player[iPlayer].name.length()>maxLength)
            maxLength=player[iPlayer].name.length();
    }

    cout <<"     "<<"Name";
    for(int i=0;i<=maxLength;i++)
        cout<<" ";
    cout<<"Score";

    for(int iPlayer=0;iPlayer<nPlayer;iPlayer++)
        {
            if(player[iPlayer].rank>0)
                validPrintRank=true;
        }

    if (validPrintRank==true)
        cout<<"   "<<"Ranking";

    cout<<endl;

    char m;
    for(int iPlayer=0; iPlayer<nPlayer; iPlayer++) {
        m='A'+iPlayer;

        cout <<m<<"=>  "<<player[iPlayer].name;

        for(int i=0;i<=maxLength+6-player[iPlayer].name.length();i++)
            cout<<" ";

        cout<<player[iPlayer].position;

        if(player[iPlayer].rank>0)
            cout<<"       "<<player[iPlayer].rank;
        cout<<endl;

        }
    cout<<endl;
    cout<<"Dice counter: "<<diceCounter-nPlayer<<endl<<endl;
}

void printPositionP(int iPosition){
    char m;
    for(int iPlayer=0;iPlayer<nPlayer;iPlayer++)
    {
        if(iPosition==player[iPlayer].position)
        {
            m='A'+iPlayer;
            cout<<m;
        }

    }
}

void printPositionSL(int iPosition){

    for(int iSnake=0;iSnake<nSnake;iSnake++)
    {
        if(iPosition==snake[iSnake].position)
        {
            cout<<"$U"<<iSnake+1;
        }

        if(iPosition==snake[iSnake].position-snake[iSnake].desceding)
        {
            cout<<"$D"<<iSnake+1;
        }

    }

    for(int iLadder=0;iLadder<nLadder;iLadder++)
    {
        if(iPosition==ladder[iLadder].position)
        {
            cout<<"#D"<<iLadder+1;
        }

        if(iPosition==ladder[iLadder].position+ladder[iLadder].asceding)
        {
            cout<<"#U"<<iLadder+1;
        }

    }
}

void setnPlayer()
{
    char n[5];
    bool valid=false;
    while(valid==false)
    {
        cin>>n;
        if(atoi(n)>1 && atoi(n)<9 && isdigit(n[0]))
            valid=true;
        else
            cout<<"your input is invalid, try again\n";

    }
    nPlayer=atoi(n);
}

void setSize()
{
    char input[5];
    bool valid=false;
    while(valid==false)
    {
        cin>>input;
        if(atoi(input)>2 && atoi(input)<=10 && isdigit(input[0]))
            valid=true;
        else
            cout<<"your input is invalid, try again\n";

    }
    size=atoi(input);
}

void setLevel()
{
    char input[5];
    bool valid=false;
    while(valid==false)
    {
        cin>>input;
        if((atoi(input)==1 || atoi(input)==2) && isdigit(input[0]))
            valid=true;
        else
            cout<<"your input is invalid, try again\n";

    }
    level=atoi(input);
}

void setLadder()
{
    srand((unsigned)time(NULL));
    for(int iLadder=0; iLadder<nLadder; iLadder++)
        {
            ladder[iLadder].position=rand()%(size*size-size)+1;
        }
    for(int iLadder=0; iLadder<nLadder; iLadder++)
        {
           int inf=size-ladder[iLadder].position%size;
           do{
            if(inf<size)
                ladder[iLadder].asceding=rand()%(size*size/3)+inf+2;
            else
                ladder[iLadder].asceding=rand()%(size*size/3)+2;
           }while(ladder[iLadder].position+ladder[iLadder].asceding>=size*size);
        }
}

void setSnake()
{
    srand((unsigned)time(NULL));
    for(int iSnake=0; iSnake<nSnake; iSnake++)
        {
            snake[iSnake].position=rand()%(size*size-size-1)+size+1;
        }
    for(int iSnake=0; iSnake<nSnake; iSnake++)
        {
            int inf=snake[iSnake].position%size;
            do{
            if(inf>0)
                snake[iSnake].desceding=rand()%(size*size/3)+inf+2;
            else
                snake[iSnake].desceding=rand()%(size*size/3)+size+2;
            }while(snake[iSnake].position-snake[iSnake].desceding<=0);
        }
}

void validSL()
{
    int *checkBox;
    checkBox=new int[size*size];

    while(1)
    {
        bool valid=true;

        for(int iCell=0;iCell<size*size;iCell++)
        {
            checkBox[iCell]=0;
        }

        for(int iSnake=0;iSnake<nSnake;iSnake++)
        {
            checkBox[snake[iSnake].position]++;
            checkBox[snake[iSnake].position-snake[iSnake].desceding]++;
        }

        for(int iLadder=0;iLadder<nLadder;iLadder++)
        {
            checkBox[ladder[iLadder].position]++;
            checkBox[ladder[iLadder].position+ladder[iLadder].asceding]++;
        }

        for(int iCell=0;iCell<size*size;iCell++)
        {
            if (checkBox[iCell]>1)
            {
                valid=false;
            }
        }


        if (valid==true) break;
        else
        {
           setSnake();
           setLadder();
        }
    }

    delete [] checkBox;
}

void checkSL(int iPlayer)
{
    for(int iSnake=0;iSnake<nSnake;iSnake++)
    {
        if(snake[iSnake].position==player[iPlayer].position)
        {
            cout<<"\aoops! a snake bit you, so press a key to fall ^_^\n";
            player[iPlayer].position-=snake[iSnake].desceding;
        }
    }

    for(int iLadder=0;iLadder<nLadder;iLadder++)
    {
        if (ladder[iLadder].position==player[iPlayer].position)
        {
            cout<<"\ayoohooo! you are on ladder, so press a key to go up :)\n";
            player[iPlayer].position+=ladder[iLadder].asceding;
        }
    }

}

void showDice(int dice){

    cout<<"your dice=> (";

    switch (dice)
    {
        case 1: cout<<".";
        break;

        case 2: cout<<":";
        break;

        case 3: cout<<":.";
        break;

        case 4: cout<<"::";
        break;

        case 5: cout<<"::.";
        break;

        case 6: cout<<":::";
        break;
    }

    cout<<")\n";
}

void showRank()
{
    for(int iRank=1;iRank<=nPlayer;iRank++)
    {
        cout<<iRank<<". ";
        for(int iPlayer=0;iPlayer<nPlayer;iPlayer++)
        {
            if(player[iPlayer].rank==iRank)
                cout<<player[iPlayer].name<<" with throw dice "<<player[iPlayer].diceCounter<<" times and get six "<<player[iPlayer].sixCounter<<" times"<<endl;
        }
    }
}

void table()
{
    char V3right=204;
    char V3left=185;
    char H3up=202;
    char H3down=203;
    char vertical=186;
    char horizental=205;
    char cornerDR=188;
    char cornerDL=200;
    char cornerUR=187;
    char cornerUL=201;
    char middle=206;
    int iPosition;
    bool first=true;

        for(int row=1;row<=size;row++)
        {

            if(first==true)
            {
                cout<<cornerUL;
                for(int i=1;i<size;i++)
                    cout<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<H3down;
                cout<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<cornerUR;
                first=false;
            }
            else
            {
                cout<<V3right;
                for(int i=1;i<size;i++)
                    cout<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<middle;
                cout<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<V3left;
            }
            cout<<endl<<vertical;

            if (row%2==size%2)
            {
                iPosition=size*size-size*row;
                for(int i=1;i<=size;i++)
                {
                iPosition++;
                cout<<iPosition<<" ";
                printPositionSL(iPosition);
                cout<<"\t"<<vertical;
                }

                cout<<endl<<vertical;

                iPosition=size*size-size*row;
                for(int i=1;i<=size;i++)
                {iPosition++;printPositionP(iPosition);
                cout<<"\t"<<vertical;}
            }

            if (row%2!=size%2)
            {
                iPosition=size*size-size*(row-1)+1;
                for(int i=1;i<=size;i++)
                {
                iPosition--;
                cout<<iPosition<<" ";
                printPositionSL(iPosition);
                cout<<"\t"<<vertical;
                }

                cout<<endl<<vertical;

                iPosition=size*size-size*(row-1)+1;
                for(int i=1;i<=size;i++)
                {iPosition--;printPositionP(iPosition);
                cout<<"\t"<<vertical;}
            }

            cout<<endl;

        }

        cout<<cornerDL;
        for(int i=1;i<size;i++)
            cout<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<H3up;
        cout<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<horizental<<cornerDR;

        cout<<endl;
        cout<<"HELP"<<endl;
        cout<<"Character=> $:Snake #:Ladder U:Up D:Down"<<endl;
        cout<<"key=> S:(Save)   L:(Load a Game)   N:(New Game)   E:(Exit)   Else:(Dice)"<<endl<<endl;

}

void refresh(){
    system("cls");
    table();
    getReport();
}

void save(){
    string saveFile;
    cout<<"\ntake a name for game's save: ";
    cin>>saveFile;
    ofstream save;
    save.open (saveFile+".SL");
    if (save.is_open())
        {
            save <<size<<"\t"<<level<<"\t"<<diceCounter<<"\t"<<sixCounter<<"\t"<<maxRank<<endl;
            save <<nPlayer<<endl;
            for(int i = 0 ; i<nPlayer ; i++)
                save <<player[i].name <<"\t"<< player[i].position <<"\t"<< player[i].valid <<"\t"<< player[i].rank <<"\t"<< player[i].diceCounter <<"\t"<< player[i].sixCounter<<endl;
            save <<nSnake<<endl;
            for(int i = 0 ; i<nSnake ; i++)
                save <<snake[i].position <<"\t"<< snake[i].desceding<<endl;
            save <<nLadder<<endl;
            for(int i = 0 ; i<nLadder ; i++)
                save <<ladder[i].position <<"\t"<< ladder[i].asceding;
            save.close();
        }
    else cout << "Unable to open file";
}

void load(){
    string loadFile;
    cout<<"\nwrite the name of your saved file: ";
    cin>>loadFile;
    ifstream load;
    load.open(loadFile+".SL");
    if (load.is_open())
      {
        load >>size>>level>>diceCounter>>sixCounter>>maxRank;
        load >>nPlayer;
        player=new Player[nPlayer];
        for(int i = 0 ; i<nPlayer ; i++)
            load >>player[i].name >> player[i].position >> player[i].valid >> player[i].rank >> player[i].diceCounter >> player[i].sixCounter;
        load >>nSnake;
        snake=new Snake[nSnake];
        for(int i = 0 ; i<nSnake ; i++)
            load >>snake[i].position >> snake[i].desceding;
        load >>nLadder;
        ladder=new Ladder[nLadder];
        for(int i = 0 ; i<nLadder ; i++)
            load >>ladder[i].position >> ladder[i].asceding;
        load.close();
        }
    else cout << "Unable to open file";
}


void input(){

    switch(getch()){

        case 'e':
        case 'E':
            system("cls");
            exit(0);
            break;

        case 's':
        case 'S':
            save();
            cout<<"saved successfully! do you want continue? if no press enter else another key...";
            if(getch()==13)
                exit(0);
            break;

        case 'l':
        case 'L':
            load();
            cout<<"load successfully! press another key to continue...";
            getch();
            break;

        case 'n':
        case 'N':
            system("cls");
            main();
            break;
    }
}


