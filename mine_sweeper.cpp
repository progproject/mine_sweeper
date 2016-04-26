#include <iostream>
#include "graphics.h"
#include <time.h>

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

int main( ) {

	initwindow(600, 600, "Mine Sweeper");

	Board b;
	gamePlay g;

	initBoard( b, g );
	fillMines( b, g );

	while(1)
	{
		takeValue( b, g );
	}

	while (!kbhit( ))
	{
		delay( 200 );
	}


	return 0;

}//end main


void initBoard( Board &b, gamePlay &g ) {

	char buffer[10] = {'\0'};
	char takeInput[3] = {'\0'};

	// Take Rows from User
	setcolor( BLUE );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy( 280, 250, "Enter Number of Rows and Coloumns" );

	rectangle(170,300,400,350);

	kbhit();
	takeInput[0] = getch();

	if( kbhit() )
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

	setcolor( BLUE );
	rectangle(350,20,160,50);
	setcolor( RED );
	outtextxy(255,25,"Time :      /sec");

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

	//memset(g.mine_sweeper,0, ( rows * cols ) * sizeof( *g.mine_sweeper ) );

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
			cout << g.mine_sweeper[i][j] << " ";
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

}

void calculateSurrounding( Board &b, gamePlay &g, int row, int col ) {

	g.mineCounter = 0;

	for(int i = row - 1; i < row + 2; i++)
	{
		for(int j = col - 1 ; j < col + 2; j++)
		{

			if( i < 0 || i > b.rows - 1 || j < 0 || j > b.cols - 1 || (i == row && j == col))
				continue;

			if(g.mine_sweeper[ i ][ j ] != 0)
				g.mineCounter++;

		}
	}
}

void takeValue( Board &b, gamePlay &g ) {

	int t = 0;
	Time( g, t );

	char buffer[3] = {'\0'};
	char takeInput[3] = {'\0'};

	// User input area
	setcolor( CYAN );

	rectangle(20,540,220,575);

	outtextxy( 100 , 550, "Enter Row : ");
	//g.row = (getch( ) - 48) - 1 ;

	takeInput[0] = getch();

	if( kbhit() )
	{

		takeInput[1] = getch();
		g.row = atoi(takeInput) - 1;

	}
	else
		g.row = (takeInput[0] - 48) - 1;

	outtextxy( 180, 550, itoa(g.row + 1,buffer,10));

	outtextxy( 100 , 550, "Enter Col : ");
	//g.col = ( getch( ) - 48 ) - 1;
	
	takeInput[0] = getch();

	if( kbhit() )
	{

		takeInput[1] = getch();
		g.col = atoi(takeInput) - 1;

	}
	else
		g.col = (takeInput[0] - 48) - 1;

	outtextxy( 180, 550, itoa(g.col,buffer,10));

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

	delay( 500 );

}//end unCoverMines

void unCover( Board &b, gamePlay &g, int row , int col ) {

	int x = 100;
	int y = 100;

	if( row < 0 || row >= b.rows || col < 0 || col >= b.cols || g.mine_sweeper[ row ][ col ] == 109 ) {

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
		if( g.mineCounter == 0 )
		{

			unCover( b, g, row - 1, col );
			unCover( b, g, row, col - 1 );
			unCover( b, g, row + 1, col );
			unCover( b, g, row, col + 1 );
			unCover( b, g, row + 1, col + 1 );
			unCover( b, g, row - 1, col + 1 );
			unCover( b, g, row - 1, col - 1 );
			unCover( b, g, row + 1, col - 1 );

		}


		/*if( g.mineCounter > 0 )
		{
		char buffer[3] = {'\0'};
		int newRow = y + ( ( b.width * 2 ) *  row  );
		int newCol = x + ( ( b.width * 2 ) *  col );

		g.mine_sweeper [ row ][ col ] = g.mineCounter;
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		floodfill( newCol + 2, newRow + 2, BLACK );
		setcolor( BLUE );
		outtextxy( newCol + b.width, newRow + (b.width - 7), itoa(g.mineCounter,buffer,10));

		}*/
	}

	//debugging
	for(int i = 0; i < b.rows; i++)
	{
		for(int j = 0; j < b.cols; j++)
		{
			cout << g.mine_sweeper[i][j] << " ";
		}
		cout << endl;
	}

}//end unCover


int  Time ( gamePlay &g, int t )
{

	t = clock ( ) - t ; 

	/*while(1) {*/

	char buffer[10] = {'\0'};

	int T  = clock ( ) ;
	T /= CLOCKS_PER_SEC;

	setcolor( WHITE );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy( 260, 25, itoa(T,buffer,10));
	delay(200);


	/*}*/

	return t/CLOCKS_PER_SEC;

}//time ends