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

int main( ) {

	initwindow(600, 600, "Mine Sweeper");

	Board b;
	gamePlay g;

	initBoard( b, g );
	fillMines( b, g );
	takeValue( b, g );

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
	outtextxy( 300, 250, "Enter Number of Rows" );

	rectangle(170,300,400,350);

	takeInput[0] = getch();
	/*takeInput[1] = getch();

	if( takeInput[1] != 0 )
	{
		b.rows = atoi(takeInput);
	}
	else
		b.rows = takeInput[0] - 48;*/

	b.rows = takeInput[0] - 48;

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

	takeInput[0] = getch();
	/*takeInput[1] = getch();

	if( takeInput[1] != '/0' )
	{
		b.cols = atoi(takeInput);
	}
	else
		b.cols = takeInput[0] - 48;*/

	b.cols = takeInput[0] - 48;
	
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy(280,315,itoa(b.cols,buffer,10));

	delay( 300 );

	cleardevice( );

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

	for( int i = 0; i < b.rows; i++ )
    {
        for( int j = 0; j < b.cols; j++ )
        {
            
			if(i < 0 || i > b.rows - 1 || j < 0 || j > b.cols - 1 || ( i == row && j == col ) )
                continue;

			if( g.mine_sweeper[i][j] != 109 )
				g.mine_sweeper[i][j]++;

			cout << g.mine_sweeper[i][j] << " ";

        }
		cout << endl;
    }

	/*for(int i = 0; i < b.rows; i++)
	{
		for(int j = 0; j < b.cols; j++)
		{
			cout << g.mine_sweeper[i][j] << " ";
		}
		cout << endl;
	}*/

}

void takeValue( Board &b, gamePlay &g ) {

	char buffer[10] = {'\0'};

	// User input area
	setcolor( CYAN );

	rectangle(20,540,220,575);

	outtextxy( 100 , 550, "Enter Row : ");
	g.row = getch( ) - 48;
	outtextxy( 180, 550, itoa(g.row,buffer,10));
	//fillellipse( 180, 550, 180 + 5, 550 + 2);

	outtextxy( 100 , 550, "Enter Col : ");
	g.col = getch( ) - 48;
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

		setcolor( RED );
		setfillstyle(SOLID_FILL, RED);
		rectangle( newCol, newRow, newCol + (b.width * 2 ), newRow + ( b.width * 2 ) );
		floodfill( newCol + 2, newRow + 2, RED );


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

	int newRow = y + ( ( b.width * 2 ) *  row  );
	int newCol = x + ( ( b.width * 2 ) *  col );

	setcolor( RED );
	setfillstyle(SOLID_FILL, RED);
	//floodfill( newCol + 2, newRow + 2, RED );

	if( row < 0 || row >= b.rows || col< 0 || col >= b.cols ) {

        return;

    } else {

		if( g.mine_sweeper[ g.row ][ g.col ] == 0)
        {

            unCover( b, g, row - 1, col );

			rectangle( newCol, newRow, newCol + (b.width * 2 ), newRow + ( b.width * 2 ) );

            unCover( b, g, row, col - 1 );
            unCover( b, g, row + 1, col );
            unCover( b, g, row, col + 1 );
            unCover( b, g, row + 1, col + 1 );
            unCover( b, g, row - 1, col + 1 );
            unCover( b, g, row - 1, col - 1 );
            unCover( b, g, row + 1, col - 1 );

        }
    }

}//end unCover
