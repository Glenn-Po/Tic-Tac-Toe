//[]Tic-tac-toe

//TODO
//--reimplement tie checker
//--implement spectacular endgame display

#include "MACROS.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <cstdio>
#include <cctype>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include <limits.h>

#define INFINITY (2<<8)
#define MIN_SCORE -(2<<3)
#define MAX_SCORE -MIN_SCORE

//[]Oponents

#define RANDOM 2<<1
#define INTELLIGENT_COMPUTER  2<<2
#define TWO_PLAYER  2<<3

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::max;
using std::min;

void instructionManual();

int checkForWinner(vector< vector<int> >& states);

bool checkForTie(vector< vector<int> >& states);

bool canPlayAtThisPos(vector< vector<int> >& states, int pos){

	int x =((pos % 3) + 2)%3, y = ((pos+2) / 3) - 1;
	return states[x][y] == 0;
}

void showWelcomeScreen();

void displayAuthorInfo();

void writePlayerIcon(int , char);

void getGameInfo();//chooseChar();
//choosw intelligence or random, char

void drawBoard();

void updateBoard(vector< vector<int> >&  v, int position, int player);

void resetBoard(vector< vector<int> >& );

int runGame(vector< vector<int> >&, int);//main game funtion

void displayStatus(string msg, int type = 1 , int waitTime = 20);

void writePositions();

int getPosition(vector< vector<int> >&);

int getPlayerChoice(vector< vector<int> >&, const char);

int getComputerPlayPos(vector<vector<int> >& board);

bool displayGameEndOrContinue(int winner, int opponent);

int getBestMove(const vector< vector<int> >& states);

int chooseGameMode();


/****************************************************************************
 *                                                                          *
 * Function: main                                                           *
 *                                                                          *
 * Purpose : run and manage the game								        *
 *                                                                          *
 * History : Date      Reason                                               *
 *           --/--/--  Created                                              *
 *                                                                          *
 ****************************************************************************/

main(){

	//0 still empty
	//1 player
	//-1 computer
	/*
	int states[][3]={
		{0,  0,  0},
		{0,  0,  0},
		{0,  0,  0}
	};*/
	
	//showWelcomeScreen();
	clear_screen();
	
	vector< vector<int> >  board;
	board.clear();
	board.push_back(vector<int>(3,0));
	board.push_back(vector<int>(3,0));
	board.push_back(vector<int>(3,0));
	
	while(true)
	{
		//resetBoard(board);
		//instructionManual();
		//clear_screen();
		int opponent = chooseGameMode();
		clear_screen();
		drawBoard();
		writePositions();
		int winner = runGame(board, opponent);
		Sleep(2000);
    	clear_screen();
		if(displayGameEndOrContinue(winner, opponent))
			continue;
		else
			break;
	}
}



//function to display status eg, input error
int runGame(vector<vector<int> >& board, int opponent){

	bool gameOn = true;
	int winner = 0 , chosenPosition;
	
	//0 for tie, 1 for player -1 for computer
		
	const char PLAYER_ONE = 'O', PLAYER_TWO = 'X'; //case of human and computer
	
	char nextPlayer = PLAYER_ONE;
	
	if(opponent==TWO_PLAYER)
		displayStatus(string("Icons for Players| ONE=[") + PLAYER_ONE + "] TWO=["+PLAYER_TWO+"]", 1, 50);
	else
		displayStatus(string("Your icon is: [")+PLAYER_ONE+"]", 1, 50);

	
	displayStatus(string("Game is loading Up ")+string(10, '\xF9'), 1, 40);
	Sleep(500);

	while(gameOn)
	{
		winner = checkForWinner(board);
		if(winner or checkForTie(board))
		{
			gameOn = false;
			continue;
			//interestingly this two statements combine to from a break;
		}
		if(nextPlayer == PLAYER_ONE)
		{
			chosenPosition = getPlayerChoice(board, nextPlayer);
			updateBoard(board, chosenPosition, 1);
			writePlayerIcon(chosenPosition, nextPlayer);
            nextPlayer = PLAYER_TWO;
        	std::ostringstream status ;
            status << "[" << nextPlayer << "] Play";
            displayStatus(status.str());
		}
		else if(nextPlayer == PLAYER_TWO)
		{
			if(opponent==TWO_PLAYER)
				chosenPosition = getPlayerChoice(board, nextPlayer);
			else
				chosenPosition = opponent==INTELLIGENT_COMPUTER ? getBestMove(board) : getComputerPlayPos(board);
			
			updateBoard(board, chosenPosition, -1);
			Sleep(1500);//sleeo to slow down the game (computer reaction)
			writePlayerIcon(chosenPosition, nextPlayer);
			if(opponent!=TWO_PLAYER)
				Sleep(800);//sleeo to slow down the game and make it fun
            nextPlayer = PLAYER_ONE;
            std::ostringstream status ;
            status << "[" << nextPlayer << "] Play";
            displayStatus(status.str());
		}
		
	}
	return winner;
}



//reset game to unplayed state
void updateBoard(vector< vector<int> >&  v, int position, int player){
	int x =((position % 3) + 2)%3, y = ((position+2) / 3) - 1;
	v[x][y]= player;

}


void resetBoard(vector< vector<int> >&  v){
	for(int i = 0; i < 3; ++i)
	    for(int j = 0; j < 3; ++j)
	        v[i][j] = 0;
}


void instructionManual(){

	clear_screen();
	TEXTCOLOR(AQUA);
	cout<<"\n\n\n"
	"    ***********************************************************************\n"
	"    *                                                                     *\n"
	"    *                       HELP AND TIPS TO PLAY                         *\n"
	"    *                                                                     *\n"
	"    ***********************************************************************\n"
	"    *                                                                     *\n"
	"    *    -The grid appears initially filled with numbers                  *\n"
	"    *                                                                     *\n"
	"    *    -This numbers represent positions that you can choose to play in *\n"
	"    *                                                                     *\n"
	"    *    -You can choose a number representing a grid position by         *\n"
	"    *      entering the number at a prompt that will be indicated         *\n"              
	"    *                                                                     *\n"
	"    *                                                                     *\n"
	"    *    -IT IS ASSUMED THAT YOU KNOW HOW A GAME OF TIC-TAC-TOE WORKS     *\n"
	"    *                                                                     *\n"
	"    *                                                                     *\n"
	"    ***********************************************************************\n";
	
	cout<<"\n\n\nPress Any Key to continue\n\n";
	getch();
}


void showWelcomeScreen(){

    clear_screen();
	GOTOXY(20, 4);
	TEXTCOLOR(SHINYWHITE);
	
	char msg[] =
	"WELCOME TO A GAME OF TIC TAC TOE \n\n\n"
	"\tDEVELOPED BY: @Glenn-Po,\n\n\n"
	"\tThis is a small, simple CONSOLE-BASED game.\n\n"
 	"\t\tENSURE to run under DOS on a PC\n\n\n"
	"\tDisfruta el juego, Amigo";
	
	for(int i = 0; msg[i] != '\0' ;){
        TEXTCOLOR(SHINYWHITE);
        if(i >= 0 and i <= 32)
            BTEXTCOLOR(SHINYRED, BLUE);
		if(i >= 50 and i <= 50+34)
		    TEXTCOLOR(GREEN);
		cout << msg[i++];
		Sleep(20);
	}
	Sleep(2000);
	
	TEXTCOLOR(DEFAULT);
	cout << "\n\n\n\n\t\tHit Any Key To Continue . . .";
	getch();
}


int chooseGameMode(){
	
	
    int position_y[] = {5+1, 7+1,9+1};
    TEXTCOLOR(SHINYWHITE);
	cout<<"\n\n\n\t\tChoose your opponent: \n\n\n";
    TEXTCOLOR(VIOLET);
	cout << "\t\t Another HUMAN        \xF0\n\n";
	cout << "\t\t Random COMPUTER      \xE0\n\n";
	cout << "\t\t Intelligent COMPUTER \x5\n\n";
	
    string items[]={
    	" Another HUMAN        \xF0",
		" Random COMPUTER      \xE0",
		" Intelligent COMPUTER \5"
    };
    
    int choices[]={
    	TWO_PLAYER,
		RANDOM,
		INTELLIGENT_COMPUTER
	};
    
    TEXTCOLOR(OLIVE);
	GOTOXY(50, 5), cout <<"PRESS ";
	GOTOXY(50, 7), cout<<  "  -The <\x1E> and <\x1F> arrow keys";
	GOTOXY(50, 9), cout<<  " 	 or <W> and <S> to MOVE   ";
	GOTOXY(50, 11), cout<<  "  -[ENTER]/[RETURN] to CHOOSE ";
	int ch,cur_pos = 0, former_pos =0;
	//first blitting
	BTEXTCOLOR(VIOLET, WHITE);
	GOTOXY(8, position_y[cur_pos%8]), cout << "\t" << items[cur_pos%3];// '\xDB';
	TEXTCOLOR(LIGHTAQUA);
	GOTOXY(40, 3), cout << "["<<std::left << items[cur_pos%3] << "]";
	TEXTCOLOR(DEFAULT);

	while(true){
		if(kbhit()){//key press detected?
			ch = getch();
			if(not ch){//arrow key or function key was pressed?
				ungetch(ch);
				ch = getch();
			}
				switch(ch){
					case 119://'w'
					case 57:// 'W'
					case 72:// up arrow key
						former_pos =cur_pos;//reset
						cur_pos==0?cur_pos=2:cur_pos--; //new position
							//trying to avoid negative array indices
						break;
					case 115: //'s'
					case 53:// 'S'
					case 80:// dowm arrow key
						former_pos = cur_pos;//reset
						cur_pos++;//new position
						break;
					//current highlighted choice was chosen
					//don't know which character code will be caught because
					//windows return = '\r\n';
						//windows return ='\r\n'
						////so '\r' is read first before '\n'

					case '\r':
					case '\n'://for fun maybe , who knows?
					   	Sleep(1000);//1 secon wait and continue
					   	fflush(stdin);
					//	GOTOXY(2, 24),cout<<"\t\tPress <ENTER> to continue";
						//getch();
					    return (choices[cur_pos%3]);
				}
				//if data changed , then blit
    			TEXTCOLOR(VIOLET);
				GOTOXY(8, position_y[former_pos%3]), cout << "\t" << items[former_pos%3];
				BTEXTCOLOR(VIOLET, WHITE);
				GOTOXY(8, position_y[cur_pos%3]), cout << "\t" << items[cur_pos%3];// '\xDB';
				TEXTCOLOR(LIGHTAQUA);
				GOTOXY(40, 3), cout << "[" <<std::left << items[cur_pos%3] <<"]";
				TEXTCOLOR(DEFAULT);

     		}
		}
}


void drawBoard(){

	TEXTCOLOR(AQUA);
	const int GRID_HEIGHT(18);//16
	const int GRID_WIDTH (19+5);//20
	int counter, i, j;
	
	GOTOXY(0,4);
	
	std::cout << "\t";//8 spaces
	
	for(i = 0;  i < GRID_WIDTH + 1;  ++i)
		std::cout << "*";// just print line
		//cout<<'-';// just print line  -second choice

	std::cout << std::endl;
	
	for( i = 1; i <= GRID_HEIGHT; ++i){
        std::cout << "\t";//16 spaces
		for(counter = 0, j = 0; counter < GRID_WIDTH+1, j < GRID_WIDTH + 1; ++counter, ++j)
		{
	        if(i%6)
			{// when i%4!=0 signifying it is not a horizontal line
			      if(counter == ((j/8)*8))// making use of integer division truncation in(j/5)
			            std::cout << "*";//cout<<'|';// just print line  -second choice

			      else std::cout << ' ';

	         }
	    	else std::cout << "*";//cout<<'-';// just print line  -second choice

		}
		std::cout << std::endl;
	}
}


void writePositions(){

	TEXTCOLOR(SILVER);
	
	int fxpos=12, fypos =  7, count = 1;
	
	for(int k = 0; k < 3; ++k)
		for(int i=0; i < 3; ++i)
			GOTOXY(fxpos+i*8, (fypos+k*6)), cout << count++;

}


void writePlayerIcon(int position, char playerIcon){

	int COLOR = playerIcon == 'X'? SHINYRED : GREEN;
	TEXTCOLOR(COLOR);
	
	int fxpos = 12, fypos =  7, count = 1,
	xOffset =((position % 3) + 2)% 3, yOffset = ((position+2) / 3) - 1;
	
	GOTOXY(fxpos + xOffset * 8, (fypos+yOffset*6)), cout << playerIcon;
}


int checkForWinner(vector< vector<int> >& states){

    for (int i = 0; i < 3; ++i)//rows
        if (states[i][0] == states[i][1] and states[i][1] == states[i][2] and
            states[i][1] != 0)
                return states[i][1];//but should probebly return the winningxter
        
    for (int i = 0; i <3; ++i)//columns
         if (states[0][i] == states[1][i] and states[1][i] == states[2][i] and
            states[1][i] != 0)
                return states[1][i];

    if (states[0][0] == states[1][1] and states[1][1] == states[2][2]
		and states[1][1] != 0)//leading diagonal
		        return states[1][1];
    
    if (states[2][0] == states[1][1] and states[1][1] == states[0][2]
		and states[1][1] != 0)//alternate diagonal
		        return states[2][0];
	return 0;
}


//!!Check the logic of this function again
bool isNotATie(int pos1, int pos2, int pos3){

	//cthis function checks for a tie in a line that you could win in
	bool conditionForATie = not ((pos1 == pos2 and pos1 != 0) or
					 (pos1 == pos3 and pos1 != 0) or
					 (pos3 == pos2 and pos3 != 0))  ;
					 
	return conditionForATie ;
}

//checks for a not tie area

bool checkForTie(vector< vector<int> >& states){

	//check all the rows
    for (int i = 0; i < 3; ++i)
        if (isNotATie(states[i][0], states[i][1], states[i][2]))
                return false;

	//check all the columns
    for (int i = 0; i <3; ++i)
        if (isNotATie(states[0][i], states[1][i], states[2][i]))
                return false;
                
    // check in the leading diagonal
    if (isNotATie(states[0][0], states[1][1], states[2][2]))
                return false;

    //check the alternate diagonal
    
    if (isNotATie(states[0][2], states[1][1], states[2][0]))
                return false;

	//if code reaches here obviously no tie

    return true;
}

//this has to make sure that the position has not been chosen alreay
int getPosition(vector< vector<int> >& states){

	char BACKSPACE = '\b', RETURN = '\r'; 
	
	bool posGotten = false, readyToSubmit = false,
	    consoleIsCurrentlyDisplayingNum = false;
	    
	char pos = 0;
	
	TEXTCOLOR(GREEN);
	GOTOXY(40, 7), cout << "Enter a position to play: [   ]";
	GOTOXY(40+28, 7);
	TEXTCOLOR(LIGHTAQUA);
	
	while(not posGotten or not readyToSubmit)
	{
		if(kbhit())
		{
			char ch = getch();
			
			if(std::isdigit(ch) and not posGotten and ch != '0'
					and not consoleIsCurrentlyDisplayingNum)
			{
                cout << ch;
				pos = ch;
				consoleIsCurrentlyDisplayingNum = true;
				posGotten = true;
			}
			else if(ch == BACKSPACE and consoleIsCurrentlyDisplayingNum)
			{
				consoleIsCurrentlyDisplayingNum = false;
                posGotten = false;
                cout << BACKSPACE << " " << BACKSPACE;
			}
			else if(ch == RETURN and posGotten)
			{
			    readyToSubmit = true;
			    if(canPlayAtThisPos(states, pos-'0'))
				;
				else
				{
					displayStatus(string("This Position is unavailable"), -1, 40);
				    readyToSubmit = posGotten = false;
				    GOTOXY(40+29, 7);
					TEXTCOLOR(LIGHTAQUA);
				}
			}
		} //end if(kbhit())
	}
	
	GOTOXY(40, 7), cout << string(5, '\t');
	return pos-'0';
}


//[] for two player game
//this has to make sure that the position has not been chosen alreay
int getPlayerChoice(vector< vector<int> >& states, const char player){

	char BACKSPACE = '\b', RETURN = '\r'; 
	
	bool posGotten = false, readyToSubmit = false,
	    consoleIsCurrentlyDisplayingNum = false;
	    
	char pos = 0;
	
	TEXTCOLOR(GREEN);
	GOTOXY(40, 7), cout << "Your Turn : " << player;
	GOTOXY(40, 9), cout << "Enter a position to play: [   ]";
	GOTOXY(40+28, 9);
	TEXTCOLOR(LIGHTAQUA);
	
	while(not posGotten or not readyToSubmit)
	{
		if(kbhit())
		{
			char ch = getch();
			
			if(std::isdigit(ch) and not posGotten and ch != '0'
					and not consoleIsCurrentlyDisplayingNum)
			{
                cout << ch;
				pos = ch;
				consoleIsCurrentlyDisplayingNum = true;
				posGotten = true;
			}
			else if(ch == BACKSPACE and consoleIsCurrentlyDisplayingNum)
			{
				consoleIsCurrentlyDisplayingNum = false;
                posGotten = false;
                cout << BACKSPACE << " " << BACKSPACE;
			}
			else if(ch == RETURN and posGotten)
			{
			    readyToSubmit = true;
			    if(canPlayAtThisPos(states, pos-'0'))
				;
				else
				{
					displayStatus(string("This Position is unavailable"), -1, 40);
				    readyToSubmit = posGotten = false;
				    GOTOXY(40+29, 9);
					TEXTCOLOR(LIGHTAQUA);
				}
			}
		} //end if(kbhit())
	}
	
	GOTOXY(40, 7), cout << string(5, '\t');
	return pos-'0';
}

void displayStatus(string msg, int type , int waitTime){

	//1 for normal - green
	//0 for warning warning   -green
	//-1 for
	
	int color = type == 1?SHINYGREEN : type == -1?SHINYRED : SHINYYELLOW;
	TEXTCOLOR(color);
	GOTOXY(8,2);
	for(int i = 0; i < msg.length(); ++i)
	{
		cout << msg[i];
		Sleep(waitTime);
	}
	
	Sleep(100);
	GOTOXY(8,2), cout << string(msg.length()+2, ' ');
	TEXTCOLOR(DEFAULT);
}

int spotter(int ,int);

int getComputerPlayPos(vector<vector<int> >& board){

	//no need to check for valid position as the tie checher will do so
	vector<int> possibleSpots;
	
	for(int i = 0; i < 3; ++i)
	    for(int j = 0; j < 3; ++j)
	        if (board[i][j] == 0)
			{
				int spot = spotter(i, j);
	            possibleSpots.push_back(spot);
			}
	//return a random move choice
	srand(time(NULL));
	return possibleSpots[rand()%possibleSpots.size()];
}

//covert (i, j) to single index
int spotter(int i  , int j){

	for(int mx = 1; mx<=9; ++mx)
		if((((mx%3)+2)%3) == i and j == ((mx+2)/3-1))//
			return mx;
	//cannot reach here??
	return 1;
}


//make spectaular display
//boxing animation of text with color:
//red for lose, green for win, yellow for draw
// and with respective emojis

//message smaal: "you", big:"msg; lose, win, tie"  + for win, - for lose | for draw
bool displayGameEndOrContinue(int winner, int opponent){

	string message;
	switch(winner)
	{
		case 0:
			message = "Game is a TIE";
			break;
		case 1:
			message = "Player O WINs";
			if(opponent != TWO_PLAYER)
				message = "You [O] Win";
			break;
		case -1:
			message = "Player X WINs";
			if(opponent != TWO_PLAYER)
				message = "Computer [X] Wins";
	}
	
	//annimate the message
	clear_screen();
	BTEXTCOLOR(SHINYGREEN, SHINYWHITE);
	GOTOXY(30, 6), cout << "\333\333\333\333\333\333\333\333\333\333\333\333\333\333\333\333";
	GOTOXY(30, 7), cout << "    " << message << "    ";
	GOTOXY(30, 8), cout << "\333\333\333\333\333\333\333\333\333\333\333\333\333\333\333\333";
	getch();
	getch();
	clear_screen();
	//prompt to play again
	
	char doYouWantToPlayAgain = 'n';
	TEXTCOLOR(SHINYGREEN);
	GOTOXY(14, 10), std::cout << "Do You Want To Play Again [y/n]: ";
	TEXTCOLOR(LIGHTAQUA);

	//implement this here
	
	while( (doYouWantToPlayAgain = getch()) and
			(tolower(doYouWantToPlayAgain) !='n' and
			tolower(doYouWantToPlayAgain) != 'y'));
	
			cout << doYouWantToPlayAgain
			;
    //doYouWantToPlayAgain = getche();
    
	switch(doYouWantToPlayAgain)
	{
		case 'y':
		case 'Y':
			Sleep(500);
			return true;
		case 'n':
		case 'N':
			clear_screen();
			TEXTCOLOR(SHINYGREEN);
			GOTOXY(14, 10), cout << "GOOD BYE | \2\2\n\n See You Next Time!!!!";
			Sleep(1000);
			TEXTCOLOR(DEFAULT);
			cout << "\n\n\n\n\t\t"
			    << " Hit Any key to exit the console";
			getch();
			return false;
		default:
			clear_screen();
			TEXTCOLOR(SHINYRED);
			GOTOXY(14, 10), cout << "Unknown Choice!!!!!!!!!!";
			Sleep(1000);
			TEXTCOLOR(DEFAULT);
			cout << "\n\tEXITING......\n\n\n\t\t"
			    << " Hit Any key to exit the console";
			getch();
			return false;
	}
}


/*##############################################################################
Win: If you have two in a row, play the third to get three in a row.

Block: If the opponent has two in a row, play the third to block them.

Fork: Create an opportunity where you can win in two ways.

Block Opponent's Fork:

Option 1: Create two in a row to force the opponent into defending, as long as it doesn't result in them creating a fork or winning. For example, if "X" has a corner, "O" has the center, and "X" has the opposite corner as well, "O" must not play a corner in order to win. (Playing a corner in this scenario creates a fork for "X" to win.)

Option 2: If there is a configuration where the opponent can fork, block that fork.

Center: Play the center.

Opposite Corner: If the opponent is in the corner, play the opposite corner.

Empty Corner: Play an empty corner.

Empty Side: Play an empty side.
#################################################################################################
*/


int sudoAIPositionFinder(vector< vector<int> >& board){
	
	vector<int> possibleSpots;
	
	for(int i = 0; i < 3; ++i)
	    for(int j = 0; j < 3; ++j)
	        if (board[i][j] == 0)
			{
				int spot = spotter(i, j);
	            possibleSpots.push_back(spot);
			}
	//return a calculate move choice
	
	//choice operator : evade loose Vs Go for win
	
	int xOffset = 0, yOffset = 0;
	//search for valid spot
	//example board
	//   1 -1  0
	//   0  0  1
	//  -1  0  1
	
	//flatten the states vector
		int definitvelyCalculatedSpot = 0;//dummy
	
	return possibleSpots[definitvelyCalculatedSpot];
}

///absolute ai position finder using minimax
///unbeatable

int minimaxAISpotFinder(vector< vector<int> > board, int depth, int player);

int getBestMove(const vector< vector<int> >& board){

	vector<int>  emptySpots;

	for(int i = 0; i < 3; ++i)
	    for(int j = 0; j < 3; ++j)
	        if (board[i][j] == 0)
			{
	            emptySpots.push_back(spotter(i, j));
			}
			
			
	int bestMove;
	
	int bestScore = -INFINITY;
	
	for(int i = 0; i < emptySpots.size(); i++)
	{
		
		int spot = emptySpots.at(i);
		
		vector <vector<int> > boardCopy(board);
		
		//play at this spot and pass the states to minimax
		updateBoard(boardCopy, spot, -1);
		
		int score = minimaxAISpotFinder(boardCopy, 0, 1);
		
		//infact if the score is 1 i should just proceed and play... right?
		if(score > bestScore)
		{
			bestScore = score;
			bestMove = spot;
		}
	}
		
	return bestMove;
}


//return the score
//depth: 0 at first
//player: -1 for computer, 1 for human
int minimaxAISpotFinder(vector< vector<int> > board, int depth, int player)
{
	//check for tie or win [terminal state]
	int winner = checkForWinner(board);
	//the score correlates negatively with the value (base on 
	//the fact that the computer is maximising
	if(winner){
		if(winner == -1)//computer
			return MAX_SCORE - depth;
		else
			return MIN_SCORE + depth;
	}
	if(checkForTie(board))return 0;
	
	//not terminal
	
	bool isMaximising = (player == -1); //ie computer
	
	vector<int>  emptySpots;
	for(int i = 0; i < 3; ++i)
	    for(int j = 0; j < 3; ++j)
	        if (board[i][j] == 0)
			{
	            emptySpots.push_back(spotter(i, j));
			}
	
	
	if(isMaximising)
	{
		int bestScore = -INFINITY;
		for(int i = 0; i < emptySpots.size(); i++)
		{
			int spot = emptySpots.at(i);
			///
			vector <vector<int> > boardCopy(board);
		
			updateBoard(boardCopy, spot, player);
			///
			int score = minimaxAISpotFinder(boardCopy, depth+1, -player);
			bestScore = max(bestScore, score);
		}
		
		return bestScore;
	}
	else
	{
		int bestScore = INFINITY;
		for(int i = 0; i < emptySpots.size(); i++)
		{
			int spot = emptySpots.at(i);
			///
			vector <vector<int> > boardCopy(board);
		
			updateBoard(boardCopy, spot, player);
			///
			int score = minimaxAISpotFinder(boardCopy, depth+1, -player);
			bestScore = min(bestScore, score);
		}
		
		return bestScore;
	
	}
	
}

