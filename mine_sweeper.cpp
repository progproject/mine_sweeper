/*
  PT ASSIGHNMENT 2
  Submitted by : Arslan Kirmani ( 041 ), Waleed Ahmed ( 058 )
  Submitted to : Sami Ullah Kashif
*/
#include <iostream>
#include <time.h>
#include <iomanip>
#include "graphics.h"

using namespace std;

struct Board {

	int rows;
	int cols;
	int width;

};

struct gamePlay {

	int ** mine_sweeper;
	int ** mines;
	int row;
	int col;
	int noOfMines;
	int mineCounter;

};

void menu ( gamePlay &g, Board &b );
void initBoard( Board &b, gamePlay &g );
void drawBoard( Board &b );
void giveArray( int cols, int rows, gamePlay &g );
void fillMines( Board &b, gamePlay &g );
void takeValue( Board &b, gamePlay &g );
void calculateSurrounding( Board &b, gamePlay &g , int row, int col);
void unCoverMines( Board &b, gamePlay &g );
void unCover( Board &b, gamePlay &g, int row, int col );
void getLocation( Board &b, gamePlay &g );
int  Time ( gamePlay &g, int t );
int  *loadScore();
void showHighScore();
void saveScore( Board &b, gamePlay &g );

//Global Vairable
int t;

void gameEngine( Board &b, gamePlay &g)
{

	initBoard( b , g );
	//loadScore();
	fillMines( b, g );
	Time( g , t );

	while(1)
	{
		takeValue( b, g );
		saveScore( b, g );
	}

}

int main( ) {

	initwindow(600, 600, "Mine Sweeper");

	Board b;
	gamePlay g;

	menu( g, b);

	while (!kbhit( ))
	{
		delay( 200 );
	}


	return 0;

}//end main

void menu( gamePlay &g , Board &b )
{
	char choice = 0;

	//wall
	setfillstyle(8,RED );
	floodfill(350,350,WHITE);

	//heading
	setcolor( RED );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 4 );
	outtextxy( 300, 80, "MINE SWEEPER" );

	//Menu
	setcolor( RED );
	settextjustify( 1, 1 );
	settextstyle( 7, HORIZ_DIR, 4 );
	outtextxy( 300, 300, " Press 1 to Play Game   " );
	outtextxy( 300, 330, " Press 2 for High Score " );

	while(!kbhit())
	{
		delay(200);
	}

	choice = getch();
	cleardevice( );

	switch(choice) {
	case '1':
		{
			cleardevice ( );

			t = clock( );
			gameEngine( b, g );

			break;
		}
	case '2':
		{
			//highscore
		}
	default:
		{
			menu ( g , b );
		}

	}//switch ends


}//menu ends


void initBoard( Board &b, gamePlay &g ) {

	char buffer[10] = {'\0'};
	char takeInput[3] = {'\0'};



	// Take Rows from User
	setcolor( RED );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy( 280, 250, "Enter Number for Rows and Coloumns" );

	rectangle(170,300,400,350);

	kbhit();
	takeInput[0] = getch();

	if( !kbhit() )
	{

		takeInput[1] = getch();
		b.rows = atoi(takeInput);

	}
	else
		b.rows = takeInput[0] - 48;

	if(b.rows > 12)
	{

		initBoard( b, g );

	}
	else
	{

		b.cols = b.rows;

		settextjustify( 1, 2 );
		settextstyle( 10, HORIZ_DIR, 2 );
		outtextxy(280,315,itoa(b.rows,buffer,10));

		delay( 300 );

		cleardevice( );

		giveArray( b.cols, b.rows, g );
		drawBoard( b );

	}

}//end initBoard

void drawBoard( Board &b ) {

	cleardevice( );

	setcolor( WHITE );

	char buffer[10] = {'\0'};

	int x1 = 100;
	int y1 = 100;
	int y2 = 500;

	int i = 0;

	b.width = 200 / b.cols;

	// boundary
	rectangle(x1, y1, y2, y2);

	setfillstyle(SOLID_FILL, DARKGRAY);
	floodfill(x1 + 50, y1 + 50, WHITE );

	// Col
	//settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 1 );
	for(i = 0; i < b.cols - 1; i++)
	{
		setcolor( DARKGRAY );
		outtextxy(x1 + b.width,y1 - 20,itoa(i + 1,buffer,10));

		setcolor( BLACK );
		line(x1 += b.width, y1, x1 += b.width, y2);
	}
	setcolor( DARKGRAY );
	outtextxy(x1 + b.width,y1 - 20,itoa(i + 1,buffer,10));

	x1 = 100;

	// Rows
	for(i = 0; i < b.rows - 1; i++)
	{
		setcolor( DARKGRAY );
		outtextxy(x1 - 20 ,y1 + b.width,itoa(i + 1,buffer,10));

		setcolor( BLACK );
		line(x1 , y1 += b.width, y2, y1 += b.width);
	}
	setcolor( DARKGRAY );
	outtextxy(x1 - 20 ,y1 + b.width,itoa(i + 1,buffer,10));

}//end drawBoard

void giveArray( int cols, int rows, gamePlay &g ) {

	//Array for game table
	g.mine_sweeper = new int * [ rows ];

	for(int i = 0; i < rows; i++) 
	{
		g.mine_sweeper[i] = new int[cols];
	}

	//Array for Mines
	g.noOfMines = rows;
	g.mines = new int * [ 2 ];

	for(int i = 0; i < 2; i++) 
	{
		g.mines[i] = new int[ g.noOfMines ];
	}

	//Initialize arrays
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			g.mine_sweeper[i][j] = 0;
		}
	}

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < g.noOfMines; j++)
		{
			g.mines[i][j] = 0;
		}
	}

}//end giveArray

void fillMines( Board &b, gamePlay &g ) {

	srand(time ( NULL ) );

	// fill board with mines

	for(int i = 0; i < g.noOfMines; i++)
	{

		int row = rand( ) % b.rows;
		int col = rand( ) % b.cols;

		g.mine_sweeper[row][col] = 'm';

		g.mines[ 0 ][ i ] = row;
		g.mines[ 1 ][ i ] = col;
	}

	// debugging
	for(int i = 0; i < b.rows; i++)
	{
		for(int j = 0; j < b.cols; j++)
		{
			cout << setw( 3 ) << g.mine_sweeper[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	//mines
	cout << "mines :" << endl;
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < g.noOfMines; j++)
		{
			cout << g.mines[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}//end fillMines

void calculateSurrounding( Board &b, gamePlay &g, int row, int col ) {

	g.mineCounter = 0;

	for(int i = row - 1; i < row + 2; i++)
	{
		for(int j = col - 1 ; j < col + 2; j++)
		{

			if( i <= 0 || i > b.rows - 1 || j <= 0 || j > b.cols - 1 || (i == row && j == col))
				continue;

			if(g.mine_sweeper[ i ][ j ] == 109)
				g.mineCounter++;

		}
	}
}//end calculateSurrounding

void takeValue( Board &b, gamePlay &g ) {

	char buffer[3] = {'\0'};
	char takeInput[3] = {'\0'};

	// User input area
	setcolor( CYAN );

	//rectangle(20,540,220,575);

	outtextxy( 100 , 550, "Enter Row : ");
	//g.row = (getch( ) - 48) - 1 ;

	takeInput[0] = getch();

	if( !kbhit() )
	{

		takeInput[1] = getch();
		g.row = atoi(takeInput) - 1;

	}
	else
		g.row = (takeInput[0] - 48) - 1;

	outtextxy( 180, 550, itoa(g.row + 1,buffer,10));

	outtextxy( 400 , 550, "Enter Col : ");
	//g.col = ( getch( ) - 48 ) - 1;

	takeInput[0] = getch();

	if( !kbhit() )
	{

		takeInput[1] = getch();
		g.col = atoi(takeInput) - 1;

	}
	else
		g.col = (takeInput[0] - 48) - 1;

	outtextxy( 480, 550, itoa(g.col + 1 ,buffer,10));

	getLocation( b, g );

}

void getLocation( Board &b, gamePlay &g ) {

	if ( g.mine_sweeper[g.row][g.col] == 109 ) {

		unCoverMines( b, g );

	} else {

		unCover( b, g , g.row, g.col);
	}
}//end getLocation


void unCoverMines( Board &b, gamePlay &g ) {

	int x = 100;
	int y = 100;
	int newCol = 0;
	int newRow = 0;


	for(int i = 0; i < g.noOfMines; i++)
	{

		newRow = y + ( ( b.width * 2 ) *  g.mines[0][i]  );
		newCol = x + ( ( b.width * 2 ) *  g.mines[1][i] );

		setcolor( BLACK );
		setfillstyle(SOLID_FILL, RED);
		floodfill( newCol + 2, newRow + 2, BLACK );

		setcolor( BLACK );
		setfillstyle(4, BLACK);
		circle(newCol + b.width, newRow + b.width, 7);
		floodfill( newCol + b.width, newRow + b.width, BLACK );

	}

	delay( 500 );

	cleardevice( );

	setcolor( 4 );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 4 );
	outtextxy( 300, 250, "GAME OVER" );

	// TIME
	char buffer[10]={'\0'};
	int T = Time (g,t);

	
	setcolor( BLUE );
	rectangle(170,50,500,80);
	setcolor( RED );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy(320,55,"Time Escaped :      /sec");

	setcolor( CYAN );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy( 370, 55, itoa(T,buffer,10));
	delay(1000);
	cleardevice();
	menu(g,b);

}//end unCoverMines

void unCover( Board &b, gamePlay &g, int row , int col ) {

	int x = 100;
	int y = 100;

	if( row <= 0 || row > b.rows || col <= 0 || col > b.cols || g.mine_sweeper[ row ][ col ] == 109 ) {

		return;

	} else {

		if( g.mine_sweeper[ row ][ col ] == 0)
		{

			calculateSurrounding( b, g, row, col );

			if( g.mineCounter == 0 )
			{

				int newRow = y + ( ( b.width * 2 ) *  row  );
				int newCol = x + ( ( b.width * 2 ) *  col );

				g.mine_sweeper [ row ][ col ] = g.mineCounter;
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				floodfill( newCol + 2, newRow + 2, BLACK );

				unCover( b, g, row - 1, col );
				unCover( b, g, row, col - 1 );
				unCover( b, g, row + 1, col );
				unCover( b, g, row, col + 1 );
				unCover( b, g, row + 1, col + 1 );
				unCover( b, g, row - 1, col + 1 );
				unCover( b, g, row - 1, col - 1 );
				unCover( b, g, row + 1, col - 1 );

			}
			else if( g.mineCounter > 0 )
			{
				char buffer[3] = {'\0'};
				int newRow = y + ( ( b.width * 2 ) *  row  );
				int newCol = x + ( ( b.width * 2 ) *  col );

				g.mine_sweeper [ row ][ col ] = g.mineCounter;
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				floodfill( newCol + 2, newRow + 2, BLACK );
				setcolor( BLUE );
				outtextxy( newCol + b.width, newRow + (b.width - 7), itoa(g.mineCounter,buffer,10));

			}

		}

		// Recursive Call
		/*if( g.mineCounter == 0 )
		{

			unCover( b, g, row - 1, col );
			unCover( b, g, row, col - 1 );
			unCover( b, g, row + 1, col );
			unCover( b, g, row, col + 1 );
			unCover( b, g, row + 1, col + 1 );
			unCover( b, g, row - 1, col + 1 );
			unCover( b, g, row - 1, col - 1 );
			unCover( b, g, row + 1, col - 1 );

		}*/

	}

	////debugging
	//for(int i = 0; i < b.rows; i++)
	//{
	//	for(int j = 0; j < b.cols; j++)
	//	{
	//		cout << g.mine_sweeper[i][j] << " ";
	//	}
	//	cout << endl;
	//}

}//end unCover


int  Time ( gamePlay &g, int t )
{
	char buffer[10] = {'\0'};

	int T  = clock ( ) - t ;
	T /= CLOCKS_PER_SEC;

	return T;

}//time ends

int *loadScore()
{

	int score[5] = {0};
	int * scores = score;

	FILE * fp = fopen( "score.txt", "r" );

	if(fp == NULL)
	{
		cout << "File not found" << endl;
		exit(1);
	}

	while(!feof(fp))
	{
		for(int i = 0; i < 5; i++)
		{
			fscanf(fp,"%s",&score[i]);
		}
	}

	return score;

}//end loadScore

void saveScore( Board &b, gamePlay &g )
{

	int gameCheck = 0;
	int time = Time ( g, t );

	for(int i = 0; i < b.rows ; i++)
	{
		for(int j = 0; j < b.cols; j++)
		{

			if(g.mine_sweeper[i][j] != 0 && g.mine_sweeper[i][j] != 109)
			{
				gameCheck++;
			}
			
		}
	}

	if( gameCheck == (b.rows * b.cols) - b.rows)
	{

		FILE * fp;

		if(fp == NULL)
		{
			fp = fopen( "score.txt", "w" );
		}
		else
			fp = fopen( "score.txt", "a" );

		fprintf(fp,"%d\n",time);

		delay(300);

		cleardevice();

		menu(g,b);

	}

}//end saveScore

void showHighScore( )
{

	int * score = loadScore();

	for(int i = 0; i < 5; i++)
	{
		cout << i <<" :" << score[i] << endl;
	}

}//end showHighScore
