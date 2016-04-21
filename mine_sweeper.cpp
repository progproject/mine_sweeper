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
	int row;
	int col;
	//int mines;

};

void initBoard( Board &b, gamePlay &g );
void drawBoard( Board &b );
void giveArray( int cols, int rows, gamePlay &g );
void initGameBoard( Board &b, gamePlay &g );
void takeValue( gamePlay &g );


int main( ) {

	initwindow(600, 600, "Mine Sweeper");

	Board b;
	gamePlay g;

	initBoard( b, g );
	initGameBoard( b, g );
	takeValue( g );

	while (!kbhit( ))
	{
		delay( 200 );
	}


	return 0;

}//end main


void initBoard( Board &b, gamePlay &g ) {

	char buffer[10] = {'\0'};

	// Take Rows from User
	setcolor( BLUE );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy( 300, 250, "Enter Number of Rows" );

	rectangle(170,300,400,350);

	b.rows = getch() - 48;

	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy(280,315,itoa(b.rows,buffer,10));

	delay( 300 );

	cleardevice( );

	// Take Columns from User
	setcolor( RED );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy( 300, 250, "Enter Number of columns" );

	rectangle(170,300,400,350);

	b.cols = getch( )  - 48;

	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy(280,315,itoa(b.cols,buffer,10));

	giveArray( b.cols, b.rows, g );
	drawBoard( b );

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
		outtextxy(x1 + b.width,y1 - 20,itoa(i,buffer,10));

		setcolor( BLACK );
		line(x1 += b.width, y1, x1 += b.width, y2);
	}
	setcolor( DARKGRAY );
	outtextxy(x1 + b.width,y1 - 20,itoa(i,buffer,10));

	x1 = 100;
	
	// Rows
	for(i = 0; i < b.rows - 1; i++)
	{
		setcolor( DARKGRAY );
		outtextxy(x1 - 20 ,y1 + b.width,itoa(i,buffer,10));

		setcolor( BLACK );
		line(x1 , y1 += b.width, y2, y1 += b.width);
	}
	setcolor( DARKGRAY );
	outtextxy(x1 - 20 ,y1 + b.width,itoa(i,buffer,10));

}//end drawBoard

void giveArray( int cols, int rows, gamePlay &g ) {
	
	g.mine_sweeper = new int * [rows];

	for(int i = 0; i < rows; i++) 
	{
		g.mine_sweeper[i] = new int[cols];
	}

	//memset(g.mine_sweeper,0,sizeof(int) * rows);

	// Debugging
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			g.mine_sweeper[i][j] = 0;
			cout << g.mine_sweeper[i][j] << " ";
		}
		cout << endl;
	}
}//end giveArray


void initGameBoard( Board &b, gamePlay &g ) {

	srand(time ( NULL ) );

	int mines = 0;

	// fill board with mines
	if( b.rows > 0 && b.rows < 5)
		mines = 2;
	else if ( b.rows > 5)
		mines = 5;

	for(int i = 0; i < b.rows - mines; i++)
	{
	
		int row = rand( ) % b.rows;
		int col = rand( ) % b.cols;

		g.mine_sweeper[row][col] = 'm';

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

}

void takeValue( gamePlay &g ) {

	char buffer[10] = {'\0'};

	// User input area
	setcolor( CYAN );

	rectangle(20,540,220,575);

	outtextxy( 100 , 550, "Enter Row : ");
	g.row = getch( ) - 48;
	outtextxy( 180, 550, itoa(g.row,buffer,10));

	outtextxy( 100 , 550, "Enter Col : ");
	g.col = getch( ) - 48;
	outtextxy( 180, 550, itoa(g.col,buffer,10));

}