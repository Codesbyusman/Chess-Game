#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <time.h>

using namespace std;

//declaring chess board globallay
const int rows = 8;
const int cols = 8;

char chessBoard[rows][cols] = {};

//globally declaring the postion variables and pointers of pieces position
int kingPosx    = 0;
int kingPosy    = 0;

int knight1Posx = 0;
int knight1Posy = 0;

int knight2Posx = 0;
int knight2Posy = 0;

char * kingPoint  = 0;
char * knight1Point = 0;
char * knight2Point = 0;

//for storing position by user
int rowPos = 0;
int colPos = 0;

//prototypes of function;
void start();
void startGame();
int menu();
void showBoard();
void boardPos(int , int , int , int , int , int , int[][2] , int[][2] , int[][2]); //seeing place on board

//input----position taker
void rowColTaker();

void initialPos();

//function to determine whether king is under attack of knights or not
int underAttack( int, int , int[][2] );

//for calculating the next moves
int possibleMovesKing( int , int , int[][2] );
int possibleMovesknight( int , int , int[][2] );

//demanding of next position
int nextPos_king();
int nextPos_knight();

//menu of selecting piece
int opponentMenu();

//seeing enter move is valid or not
int validPossible ( int , int , int[][2] );



int main()
{

	start();

	return 0;

}

//defining the start function --- start function is to take user choice of playing game or not
void start()
{

	char entered;

	//for assistance 
	int a = 0;

	do
	{
		if ( a==0 )
		{
			cout<<"\n\n\n\t\t\t Welcome to Chess Game "<<endl;
			cout<<"\n\t\t If you want to play the game enter s "<<endl;
			cout<<"\t\t     and to Exit the game enter e  "<<endl;
			
			cout<<"\n\t\t Enter the appropriate character : ";
			cin>>entered;
		}
		else
		{
		
			cout<<"\n\t\t          Inappropriate Entry "<<endl;
			cout<<"\t\t Again Enter the appropriate character : ";
			cin>>entered;
		}
		a++;
	}
	while ( entered != 's' && entered != 'e');

	switch(entered)
	{

		case 's' :
		{
			startGame();
			break;
		}
		default :
		{

		cout<<"\n\t\t\t\t Bye :) \n\n\n"<<endl;
		}

	}	
		
}


//defining the startGame function --- the whole game
void startGame()
{

	
	register int i , j;
	
	//initializing chess board by space
	for ( i=0 ; i<rows ; i++ )
	{
		for ( j=0 ; j<cols ; j++ )
		{
			chessBoard[i][j] = ' ';
		}
	}
	
	//to check being attackesd or not
	int check1 , check2;
	
	//for storing the possible moves of king
	int king_possible_moves[rows][2] = {};
	//for storing the possible moves of knight-1
	int knight1_possible_moves[rows][2] = {};
	//for storing the possible moves of knight-2
	int knight2_possible_moves[rows][2] = {};
		
	
	int funStore = 0;
	
	cout<<"\n\t\t::::::::::::::::: Chess Game :::::::::::::::::"<<endl;
	cout<<"\n\t\t\t-------- Save The King --------"<<endl;
	cout<<"\t\t\t----- From the Chess game -----"<<endl;
	
	
		funStore = 0;
		
		//validating that it is the knight section
		do 
		{
			//seeing if it is 5 or not in accordance to menu option
			funStore = menu();
		
		} while ( funStore != 5 ); //calling until knight is not selected
		
		//--------------------------------------------------------------- initial moves input --------------------------------------------------------------
		
		//showing the empty chess board
		showBoard();
		int a = 0;
		
		
	do//just validating the intitiallay king is not under attack
	{
		a = 0;
		
		//calling the intial position function
		//checking same positions are not given
		do
		{
			if ( a==0 )
			{
			
				initialPos();
			}
			else
			{
				cout<<"\n\t\t Two chess pieces cannot take the same positions "<<endl;
				cout<<"  \t\t\t:::::::: Enter again :::::::"<<endl;
				initialPos();
			}
			
			a++;
		}	
		while ( !((( ( kingPosx != knight1Posx ) || ( kingPosy != knight1Posy ) )  && (  ( kingPosx != knight2Posx ) || ( kingPosy != knight2Posy ) )) &&( ( ( knight1Posx != knight2Posx ) || ( knight1Posy != knight2Posy ) ) )));
		
		
		//----------------------------------- Initial Position --------------------------------------------------
		
		
		//possible moves of king
		possibleMovesKing( kingPosx , kingPosy , king_possible_moves);
		
		//possible moves of knight1
		cout<<"\n\t Next Posibble moves of knight-1 from current position ["<<knight1Posx+1<<","<<knight1Posy+1<<"] are : "<<endl;
		possibleMovesknight( knight1Posx , knight1Posy , knight1_possible_moves);
		
		//possible moves of knight2
		cout<<"\n\n\t Next Posibble moves of knight-2 from current position ["<<knight2Posx+1<<","<<knight2Posy+1<<"] are : "<<endl;
		possibleMovesknight( knight2Posx , knight2Posy , knight2_possible_moves);
		
		check1 = underAttack( kingPosx , kingPosy , knight1_possible_moves ); //1 that not under attack of knigt-1
		check2 = underAttack( kingPosx , kingPosy , knight2_possible_moves ); //same --- 1 for not under knight-2
		
		if ( check1 == 0 )
		{
			cout<<"\n\t\t\t King was under attack by Knight-1 "<<endl;
			cout<<"\t\t\t Enter the initial positions Again \n"<<endl;
		}
		
		if ( check2 == 0 )
		{
			cout<<"\n\t\t\t King was under attack by Knight-2 "<<endl;
			cout<<"\t\t\t Enter the initial positions Again \n"<<endl;
		}
		
		//loking in to board & making relation with array's board
		//showing all above stuff
		boardPos( kingPosx , kingPosy , knight1Posx , knight1Posy , knight2Posx , knight2Posy , king_possible_moves , knight1_possible_moves , knight2_possible_moves );
		showBoard();
		
		cout<<"\n\n          ---------- ---------- ---------- ---------- ---------- ---------- \n"<<endl;
	
	}
	while ( ( check1 != 1) || ( check2 != 1 )); //if underAttack returns 1 that mean king is not under attack
	
	//loking in to board & making relation with array's board
	//showing all above stuff
	boardPos( kingPosx , kingPosy , knight1Posx , knight1Posy , knight2Posx , knight2Posy , king_possible_moves , knight1_possible_moves , knight2_possible_moves );
	showBoard();
	
	char pressed;
	
	//----------------------------- For Other Moves ----------------------------------------------------------
	//keep doing till f is entered
	do
	{
	
		a = 0 ;
		
		//demanding next positions and doing all other things
		do
		{
		
			if ( a==0 )
			{
			
				nextPos_king();
				//validation of entered moves
				funStore = validPossible ( kingPosx  , kingPosy , king_possible_moves );
			}
			else
			{
				cout<<"\n\t\t Invalid Moves --- Enter a valid move for King" ;
				nextPos_king();
				//validation of entered moves
				funStore = validPossible ( kingPosx  , kingPosy , king_possible_moves );
			
			}
			
			a++;
			
		} while ( funStore != 1 ); //will demand again and again until validation function validates by returning the 1
		
		//new possible moves
		possibleMovesKing( kingPosx , kingPosy , king_possible_moves);
		
		//decalaration of dummy chess board
		char dumChessboard[8][8] = {};
		
		//assigning pointers values on the chess board
		kingPoint = &dumChessboard[kingPosx][kingPosy];
		knight1Point = &dumChessboard[knight1Posx][knight1Posy];
		knight2Point = &dumChessboard[knight2Posx][knight2Posy];
		
		//checking if address of knight-1 and king is same then king killed knight because this section is movement of king's move
		if ( kingPoint == knight1Point )
		{
			cout<<"\n\n\n\t\t :::::::::: Game is Ended ::::::::::::"<<endl;
			cout<<"\t\t   knight-1 is killed by king "<<endl;
			break;
		}
		
		//checking if address of knight-2 and king is same then king killed knight because this section is movement of king's move
		if ( kingPoint == knight2Point )
		{
			cout<<"\n\n\n\t\t :::::::::: Game is Ended ::::::::::::"<<endl;
			cout<<"\t\t   knight-2 is killed by king "<<endl;
			break;
		}
		
		//demanding next positions for knight and doing all other things
		//looking which was moved
		//if next position functions return 1 that is or knight-1 and 0 for knight-2
		int funStore1 = 1; 
		
		a =0 ;
		
		//if 1 is return knight-1 is dealed and 0 then knight-2
		funStore1 = nextPos_knight();
		
		if ( funStore1 == 1 )
		{
			do
			{
			
				if ( a==0 )
				{
				
					//demanding next position of knight
					//when function will return 1 that will be for first knight
					
					funStore =validPossible ( knight1Posx  , knight1Posy , knight1_possible_moves );
				
					
				
				}
				else
				{
					cout<<"\n\t\t Invalid Moves --- Enter a valid move for Knight piece" ;
					 nextPos_knight();
					//validation of entered moves
					funStore = validPossible ( knight1Posx  , knight1Posy , knight1_possible_moves );
				
				}
				
				a++;
				
			} while ( funStore != 1 ); //will demand again and again until validation function validates by returning the 1
			
		}
		else
		{
			do
			{
			
				if ( a==0 )
				{
				
					//demanding next position of knight
					//when function will return 1 that will be for first knight
		
					funStore = validPossible ( knight2Posx  , knight2Posy , knight2_possible_moves );
				
					
				
				}
				else
				{
					cout<<"\n\t\t Invalid Moves --- Enter a valid move for Knight piece" ;
					nextPos_knight();
					//validation of entered moves
					funStore = validPossible ( knight2Posx  , knight2Posy , knight2_possible_moves );
				
				}
				
				a++;
				
			} while ( funStore != 1 ); //will demand again and again until validation function validates by returning the 1
		}
		
		//new possible moves
		if ( funStore1 == 1 )
		{
			cout<<"\n\t\t Possible next moves of moved knight-1 are : "<<endl;
			possibleMovesknight( knight1Posx , knight1Posy , knight1_possible_moves);
		}
		else
		{
			cout<<"\n\t\t Possible next moves of moved knight-2 are : "<<endl;
			possibleMovesknight( knight2Posx , knight2Posy , knight2_possible_moves);
		}
		
		//assiging pointers the adresses on dummyCHess board as in under attack
		kingPoint = &dumChessboard[kingPosx][kingPosy];
		knight1Point = &dumChessboard[knight1Posx][knight1Posy];
		knight2Point = &dumChessboard[knight2Posx][knight2Posy];
		
		//if address of both king and knight is same then knight killed the king as knight moves portion
		if ( kingPoint == knight1Point )
		{
			cout<<"\n\n\n\t\t :::::::::: Game is Ended ::::::::::::"<<endl;
			cout<<"\t\t   king is killed by knight-1 "<<endl;
			break;
		}
		
		//if address of both king and knight is same then knight killed the king as knight moves portion
		if ( kingPoint == knight2Point )
		{
			cout<<"\n\n\n\t\t :::::::::: Game is Ended ::::::::::::"<<endl;
			cout<<"\t\t   king is killed by knight-2 "<<endl;
			break;
		}
		
		
		//----------------------------------------- showing final results ---------------------------------------------
		boardPos( kingPosx , kingPosy , knight1Posx , knight1Posy , knight2Posx , knight2Posy , king_possible_moves , knight1_possible_moves , knight2_possible_moves );
		showBoard();
		
		cout<<"\n\t        To play Further enter any character other than f "<<endl;
		cout<<"\t                  To finish the game enter f "<<endl;
		cout<<"\n\t Enter the appropriate option : ";
		cin>>pressed;
	
	}
	while( pressed != 'f' );

	cout<<endl<<endl;	
}


//defining the menu function
int menu()
{

	//for assistance
	int a = 0;

	//taking the input from the user
	int enteredChoice = 0;

	do
	{

		if ( a == 0 )
		{

			cout<<"\n\t Please Select the Chess piece that you want to play with king"<<endl;
			cout<<"\n\t\t\t\t 1 for King "<<endl;
			cout<<"\t\t\t\t 2 for Queen "<<endl;
			cout<<"\t\t\t\t 3 for Bishop "<<endl;
			cout<<"\t\t\t\t 4 for Rook"<<endl;
			cout<<"\t\t\t\t 5 for Knight"<<endl;

			cout<<"\n\t\t   Enter the appropriate option : ";
			cin>>enteredChoice;
		}
		else
		{
			
			cout<<"\n\t  Please Enter the choise again --- Entered was inappropriate"<<endl;
			cout<<"\t Please Select the Chess piece that you want to play with king"<<endl;
			cout<<"\n\t\t\t\t 1 for King "<<endl;
			cout<<"\t\t\t\t 2 for Queen "<<endl;
			cout<<"\t\t\t\t 3 for Bishop "<<endl;
			cout<<"\t\t\t\t 4 for Rook"<<endl;
			cout<<"\t\t\t\t 5 for Knight"<<endl;

			cout<<"\n\t\t   Enter the appropriate option : ";
			cin>>enteredChoice;
		}

		a++;
		
		

	} while ( !(enteredChoice>0 && enteredChoice<6) );
	
	
	//checking which choice selected
	switch (enteredChoice)
	{
		case 5 :
		{
			cout<<"\n\t\t\t Knight Piece is Selected "<<endl;
			cout<<"\t\t You are going to play with King and Two Knights  "<<endl;
			break;
		}
		
		default :
		{
			cout<<"\n\t\t\t Knight Piece is not Selected "<<endl;
			cout<<"\n\t\t\t Again Choose the Piece from Menu "<<endl;
			cout<<"\t\t In this Section You can only play with King and Knight "<<endl;

		}
		
	}
	
	return enteredChoice;
	
}



void showBoard()
{

	register int i , j;
	//for number presentation
	cout<<"\n\n\n\t\t    ";
	for ( i=0 ; i<cols ; i++ )
	{
		cout<<setw(4)<<i+1<<" ";
	}
	cout<<endl;
	
	cout<<"\t\t    ";
	for ( i=0 ; i<cols ; i++ )
	{
		cout<<" ____";
	}
	
	for ( i=0 ; i<rows ; i++ )
	{
		
		cout<<endl<<"\t\t  "<<i+1<<" ";
				
		for(  j=0 ; j<cols ; j++)
		{
			cout<<"|"<<chessBoard[i][j]<<setw(5)<<"|\b";
		}
		cout<<"|"<<endl<<"\t\t    ";
		
		for (  j=0 ; j<cols; j++ )
		{
			cout<<"|"<<setw(6)<<"____|\b";
		}
		
		cout<<"|";
		
	}
	
	cout<<endl<<endl;
	
	cout<<"\n\t     k is for king, n is for First-Knight & N is for Second-Knight"<<endl;
	cout<<"\n\t              \"*\" is possible moves of king "<<endl;
	cout<<"\t         \":\" is possible moves of knight-1 --- \"n\" "<<endl;
	cout<<"\t          \"#\" is possible moves of knight-2 --- \"N\" "<<endl;
	
}


void boardPos ( int kx , int ky , int k1x, int k1y, int k2x, int k2y , int kPosmv[][2] , int kn1Posmv[][2] , int kn2Posmv[][2])
{

	register int i , j;
	
	//initializing chess board by space
	for ( i=0 ; i<rows ; i++ )
	{
		for ( j=0 ; j<cols ; j++ )
		{
			chessBoard[i][j] = ' ';
		}
	}
	
	   kingPoint = &chessBoard[kx][ky];
	knight1Point = &chessBoard[k1x][k1y];
	knight2Point = &chessBoard[k2x][k2y];
	
	
	//by help of pointer ---- showing the positions
	   *kingPoint = 'K';
	*knight1Point = 'n';
	*knight2Point = 'N';
	
	int a =0;
	int b = 0;
	
	//showing possible moves of king
	for( i=0 ; i<8 ; i++)
	{
		for( j=0 ;j<2 ; j++ )
		{
			if ( j==0 )
			{
				a = kPosmv[i][j] -1; //taking values of row no
int underAttack( int, int , int[][2] );
			}
			else
			{
				b = kPosmv[i][j]-1; //taking values next to first element
			}
		}
		
		if( (chessBoard[a][b] == ' ') && ( a>=0 && a<=7 ) &&  ( b>=0 && b<=7 )  ) //' ' ------- showing space
		{
			chessBoard[a][b] = '*';
		}
			
	}
	
	//showing possible moves of knight-1
	for( i=0 ; i<8 ; i++)
	{
		for( j=0 ;j<2 ; j++ )
		{
			if ( j==0 )
			{
				a = kn1Posmv[i][j] -1; //taking values of row no
			}
			else
			{
				b = kn1Posmv[i][j]-1; //taking values next to first element
			}
		}
		
		if ((chessBoard[a][b] == ' ' ) && ( a>=0 && a<=7 ) &&  ( b>=0 && b<=7 ) ) //' ' ------- showing space
		{
			chessBoard[a][b] = ':';
		} 
			
	}
	
	//showing possible moves of knight-2
	for( i=0 ; i<8 ; i++)
	{
		for( j=0 ;j<2 ; j++ )
		{
			if ( j==0 )
			{
				a = kn2Posmv[i][j] -1; //taking values of row no
			}
			else
			{
				b = kn2Posmv[i][j]-1; //taking values next to first element
			}
		}
		
		if( (chessBoard[a][b] == ' '  ) && ( a>=0 && a<=7 ) &&  ( b>=0 && b<=7 ) )//' ' ------- showing space
		{
			chessBoard[a][b] = '#';
		}
			
	}
			
	
}


//definition
void rowColTaker()
{

	int enteredRow = 0;
	int enteredCol = 0;

	int a = 0;
	do
	{
		
		if ( a==0 )
		{
			cout<<"\n\t\t\t\t    Row Number : ";
			cin>>enteredRow;
			cout<<"\t\t\t\t Column Number : ";
			cin>>enteredCol;
		}
		else
		{
			cout<<"\n\t   Rows and Columns can not be less than 8 or greater than 8 \n\t\t\t\t Enter again "<<endl;
			cout<<"\n\t\t\t\t    Row Number : ";
			cin>>enteredRow;
			cout<<"\t\t\t\t Column Number : ";
			cin>>enteredCol;
		}
		
		a++;
			
	} while ( !((enteredRow>=1 && enteredRow<=8) && (enteredCol>=1 && enteredCol<=8)) );

	//transfering pos to global scope
	rowPos = enteredRow;
	colPos = enteredCol;

}


//defining the intial position function
void initialPos()
{


	cout<<"\n\t\t       Enter the initial positions of Pieces "<<endl;

	cout<<"\n\t     Initial Position of King By giving row and column Number  "<<endl;
	//calling row col taking function
	rowColTaker();

	//asiigning to the globallay declared positions
	//because index will be one less and to deal with index
	kingPosx    = rowPos-1;
	kingPosy    = colPos-1;

	cout<<"\n\t\t Initial Position Of King = ["<<rowPos<<","<<colPos<<"]"<<endl;
	
	cout<<"\n\t     Initial Position of Knight-1 By giving row and column Number  "<<endl;
	//calling row col taking function
	rowColTaker();
	//asiigning to the globallay declared positions
	knight1Posx = rowPos-1;
	knight1Posy = colPos-1;
	
	cout<<"\n\t\t Initial Position Of Knight-1 = ["<<rowPos<<","<<colPos<<"]"<<endl;

	cout<<"\n\t     Initial Position of Knight-2 By giving row and column Number  "<<endl;
	//calling row col taking function
	rowColTaker();
	//asiigning to the globallay declared positions
	knight2Posx = rowPos-1;
	knight2Posy = colPos-1;
	
	cout<<"\n\t\t Initial Position Of Knight-2 = ["<<rowPos<<","<<colPos<<"]"<<endl;

}

int nextPos_king()
{

	cout<<"\n\t\t :::::::::::: My Turn ( kings move) ::::::::::"<<endl;
	cout<<"\n\t     Give Position of King By giving row and column Number  "<<endl;
	//calling row col taking function
	rowColTaker();
	kingPosx    = rowPos-1;
	kingPosy    = colPos-1;
		
	return 0;
	
}

int nextPos_knight()
{
	int a = 0;
	
	switch ( opponentMenu())
	{
		case 1 :
		{
			cout<<"\n\t     Give Position of Knight-1 By giving row and column Number  "<<endl;
			//calling row col taking function
			rowColTaker();
			knight1Posx    = rowPos-1;
			knight1Posy    = colPos-1;
			
			a= 1;
			
			break;
		}
		default :
		{
			cout<<"\n\t     Give Position of Knight-2 By giving row and column Number  "<<endl;
			//calling row col taking function
			rowColTaker();
			knight2Posx    = rowPos-1;
			knight2Posy    = colPos-1;
			
			a = 0;
		}
	}

	return a;
	
}

int validPossible ( int xPos , int yPos , int possibleMv[][2] )
{
	
	register int i , j;
	
	//returning the 0 in a if not valid and 1 in a if valid
	int a = 0;
	
	//declaring two pointers
	int * pointX = &xPos;
	*pointX = *pointX + 1;
	
	int * pointY = &yPos;
	*pointY = *pointY + 1;
	
	//assigning pointer a 2-d array
	int (* pointer)[2] = possibleMv;
	
	//going to use pointer as arrays
	
	for ( i=0 ; i<rows ; i++ )
	{
		 	j=0 ;
		
			
			//1 is added in x and y position because they were index and material store is the actual position
			//so adding 1 makes that again real position from index of array
			if( pointer[i][j] == *pointX ) 
			{
				if ( (pointer[i][j+1] == *pointY ) )
				{
					a = 1;
					break;
				}
			}
			else
			{
			
				a = 0;	
			}
		
	}

	return a;
}

int opponentMenu()
{
	int selected;
	
	do
	{
	
		cout<<"\n\t\t :::::::::::: Oponnents Turn ( knight move) ::::::::::"<<endl;
		cout<<"\n\t\t            slecect the piece you want to move "<<endl;
		
		cout<<" \n\t\t                 1 for small n Knight "<<endl;
		cout<<" \n\t\t                 2 for small N Knight "<<endl;
		
		cout<<"\n\t   Enter the appropriate option : ";
		cin>>selected;
	}
	while ( !(selected>0 && selected<3) );
	
	return selected;
}

int possibleMovesKing( int kx , int ky , int kingPsm[][2] )
{

	//array is for storing the possible moves
	//kingPsm------king possible moves
	//this will store positions that will be then checked
	//first column is x-component and second is y-component

	
	//ckx and cky are current positions 
	//1 is added in kx and ky as they were reffering to indexes
	int ckx = kx+1;
	int cky = ky+1;
	
	cout<<"\n\t Next Posibble moves of king from current position ["<<kx+1<<","<<ky+1<<"] are : "<<endl;
	cout<<"\n\t    ";
	
	//checks are just applied to make sure possible moves are nt outside of chess board
	if ( ( ckx-1 >0 && ckx-1 < 9 ) && ( cky-1 >0 && cky-1 < 9 ) )
	{
		cout<<"["<<ckx-1<<","<<cky-1<<"]"<<"  ";
		
		//storing values in array
		kingPsm[0][0] = ckx-1;
		kingPsm[0][1] = cky-1;
	}
	
	if ( ( ckx-1 >0 && ckx-1 < 9 ) && ( cky >0 && cky < 9 ) )
	{
		cout<<"["<<ckx-1<<","<<cky  <<"]"<<"  ";
		
		//storing values in array
		kingPsm[1][0] = ckx-1;
		kingPsm[1][1] = cky;
	}
	
	if ( ( ckx-1 >0 && ckx-1 < 9 ) && ( cky+1 >0 && cky+1 < 9 ) )
	{	
		cout<<"["<<ckx-1<<","<<cky+1<<"]"<<"  ";
		
		//storing values in array
		kingPsm[2][0] = ckx-1;
		kingPsm[2][1] = cky+1;
	}
	
	
	if ( ( ckx >0 && ckx < 9 ) && ( cky-1 >0 && cky-1 < 9 ) )
	{
		cout<<"["<<ckx  <<","<<cky-1<<"]"<<"  ";
		
		//storing values in array
		kingPsm[3][0] = ckx;
		kingPsm[3][1] = cky-1;
	
	}
	
	if ( ( ckx >0 && ckx < 9 ) && ( cky+1 >0 && cky+1 < 9 ) )
	{
	
		cout<<"["<<ckx  <<","<<cky+1<<"]"<<"  ";
		
		//storing values in array
		kingPsm[4][0] = ckx;
		kingPsm[4][1] = cky+1;
	}
	
	if ( ( ckx+1 >0 && ckx+1 < 9 ) && ( cky-1 >0 && cky-1 < 9 ) )
	{
	
		cout<<"["<<ckx+1<<","<<cky-1<<"]"<<"  ";
		
		//storing values in array
		kingPsm[5][0] = ckx+1;
		kingPsm[5][1] = cky-1;
	
	}
	
	if ( ( ckx+1 >0 && ckx+1 < 9 ) && ( cky >0 && cky < 9 ) )
	{
		
		cout<<"["<<ckx+1<<","<<cky  <<"]"<<"  ";
		
		//storing values in array
		kingPsm[6][0] = ckx+1;
		kingPsm[6][1] = cky;
	}
	
	
	if ( ( ckx+1 >0 && ckx+1 < 9 ) && ( cky+1 >0 && cky+1 < 9 ) )
	{
		cout<<"["<<ckx+1<<","<<cky+1<<"]"<<endl;
		
		//storing values in array
		kingPsm[7][0] = ckx+1;
		kingPsm[7][1] = cky+1;
	
	}
	
	
	return 0;
	
}

int possibleMovesknight( int k1x , int k1y , int knight1Psm[][2] )
{

	//will be use for both of knight
	//k1x and k1y ---- positions of first knight or second
	//array is for storing the possible moves
	//knight1Psm------knight-1/2 possible moves
	//this will store positions that will be then checked
	//first column is x-component and second is y-component

	//since k1x and k1y are indexes thus-------ck1y shows current position
	int ck1x = k1x + 1;
	int ck1y = k1y + 1;

		cout<<"\n\t    ";
		
	if ( ( ck1x-2 >0 && ck1x-2 < 9 ) && ( ck1y-1 >0 && ck1y-1 < 9 ) )
	{
		
		cout<<"["<<ck1x-2<<","<<ck1y-1<<"]"<<"  ";

		//storing values in array
		knight1Psm[0][0] = ck1x-2;
		knight1Psm[0][1] = ck1y-1;

	}
	
		
	if ( ( ck1x-2 >0 && ck1x-2 < 9 ) && ( ck1y+1 >0 && ck1y+1 < 9 ) )
	{
	
		cout<<"["<<ck1x-2<<","<<ck1y+1<<"]"<<"  ";

		//storing values in array
		knight1Psm[1][0] = ck1x-2;
		knight1Psm[1][1] = ck1y+1;
	}
	
	
	if ( ( ck1x+2 >0 && ck1x+2 < 9 ) && ( ck1y+1 >0 && ck1y+1 < 9 ) )
	{

		cout<<"["<<ck1x+2<<","<<ck1y+1<<"]"<<"  ";

		//storing values in array
		knight1Psm[2][0] = ck1x+2;
		knight1Psm[2][1] = ck1y+1;
	
	}
	
	if ( ( ck1x+2 >0 && ck1x+2 < 9 ) && ( ck1y-1 >0 && ck1y-1 < 9 ) )
	{
		cout<<"["<<ck1x+2<<","<<ck1y-1<<"]"<<"  ";

		//storing values in array
		knight1Psm[3][0] = ck1x+2;
		knight1Psm[3][1] = ck1y-1;
	}
	
	if ( ( ck1x+1 >0 && ck1x+1 < 9 ) && ( ck1y-2 >0 && ck1y-2 < 9 ) )
	{
	
		cout<<"["<<ck1x+1<<","<<ck1y-2<<"]"<<"  ";

		//storing values in array
		knight1Psm[4][0] = ck1x+1;
		knight1Psm[4][1] = ck1y-2;

	}
	
	if ( ( ck1x+1 >0 && ck1x+1 < 9 ) && ( ck1y+2 >0 && ck1y+2 < 9 ) )
	{
		cout<<"["<<ck1x+1<<","<<ck1y+2<<"]"<<"  ";

		//storing values in array
		knight1Psm[5][0] = ck1x+1;
		knight1Psm[5][1] = ck1y+2;

	}
	
	if ( ( ck1x-1 >0 && ck1x-1 < 9 ) && ( ck1y+2 >0 && ck1y+2 < 9 ) )
	{
	
		cout<<"["<<ck1x-1<<","<<ck1y+2<<"]"<<"  ";

		//storing values in array
		knight1Psm[6][0] = ck1x-1;
		knight1Psm[6][1] = ck1y+2;

	}
	
	if ( ( ck1x-1 >0 && ck1x-1 < 9 ) && ( ck1y-2 >0 && ck1y-2 < 9 ) )
	{
	
		cout<<"["<<ck1x-1<<","<<ck1y-2<<"]"<<endl;

		//storing values in array
		knight1Psm[7][0] = ck1x-1;
		knight1Psm[7][1] = ck1y-2;

	}
		
	return 0;

}

int underAttack ( int attackedPosx , int attackedPosy , int attacker_moves[][2] )
{

	int a ,b;
	int returnValue = 1;
	register int i ,j ;
	//creating dummy chess-board
	int dummy_chessBoard [rows][cols] = {};

	//making position of thing to be attacked
	int * const position_pointer = &dummy_chessBoard[attackedPosx][attackedPosy];

	//pointer for checking
	int * check_pointer = 0;

	//another for attacker
	for ( i=0 ; i<rows ; i++ )
	{

		
		j=0 ;
		a = attacker_moves[i][j];
		b = attacker_moves[i][j+1];
		
		if ( a > 0 && b > 0 )
		{
		//shows that accessing the index
		check_pointer = &dummy_chessBoard[a-1][b-1]; 
		}
		
		//if checking has same address as position then the piece is being attacked by the attacker
		if ( check_pointer == position_pointer )
		{	
			returnValue = 0 ;
			break;
		}
		
	}



	return returnValue ;
}















