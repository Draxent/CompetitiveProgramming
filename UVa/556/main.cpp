#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>

#define NUM_DIRECTIONS 4
#define NUM_RESULTS 5
#define WALL -1
#define MILLISECONDS 1000
#define TIME_MILLISECONDS 200
#define WAIT_PRINT (TIME_MILLISECONDS * MILLISECONDS)
#define PRINT_MAZE false

using namespace std;

class Maze
{
public:
	Maze( size_t rows, size_t columns, size_t* result ) : rows(rows), columns(columns)
	{
		// At the beginning all cells are unvisited
		result[0] = rows*columns;

		// Allocate the rows ( plus the border )
		maze = new int8_t*[rows + 2];

		// First row is a wall
		maze[0] = new int8_t[columns + 2];
		for ( size_t j = 0; j < columns + 2; j++ )
			maze[0][j] = WALL;

		// Build the central maze
		for ( size_t i = 1; i <= rows; i++ )
		{
			// Allocate the columns ( plus the border )
			maze[i] = new int8_t[columns + 2];

			// First column is a wall
			maze[i][0] = WALL;
			// Insert the other walls into the maze
			for ( size_t j = 1; j <= columns; j++ )
			{
				// Read a character
				char c;
				cin >> c;
				// If the character is 1 means that there is a wall
				if ( c == '1' )
				{
					maze[i][j] = WALL;
					// Remove all walls from the result of unvisited cell
					result[0]--;
				}
				else maze[i][j] = 0;
			}
			// Last column is a wall
			maze[i][columns + 1] = WALL;
		}

		// Last row is a wall
		maze[rows + 1] = new int8_t[columns + 2];
		for ( size_t j = 0; j < columns + 2; j++ )
			maze[rows + 1][j] = WALL;
	}

	inline int8_t get( size_t i, size_t j ){ return maze[i+1][j+1]; }
	inline void set( size_t i, size_t j, int8_t value ){ maze[i+1][j+1] = value; }

	void print( )
	{
		// Clear screen
		cout << "\033[2J\033[1;1H";

		for ( size_t i = 1; i <= rows; i++)
		{
			for ( size_t j = 1; j <= columns; j++ )
				cout << setw(2) << static_cast<int16_t>(maze[i][j]) << " ";
			cout << endl;
		}
		cout << endl;
		usleep( WAIT_PRINT );
	}

	~Maze()
	{
		for ( size_t i = 0; i < rows + 2; i++ )
			delete maze[i];
		delete maze;
	}

private:
	size_t rows, columns;
	int8_t** maze;
};

typedef enum
{
	E, // East
	N, // North
	W, // West
	S, // South
} direction_t;

class Mouse
{
public:
	size_t X, Y; // position of the mouse
	direction_t Dir; // direction of the mouse

	Mouse() { }

	inline void turnL()
	{
		switch ( Dir )
		{
			case E: Dir = N; break;
			case N: Dir = W; break;
			case W: Dir = S; break;
			case S: Dir = E; break;
			default: exit(1);
		}
	}

	inline void turnR()
	{
		switch ( Dir )
		{
			case E: Dir = S; break;
			case N: Dir = E; break;
			case W: Dir = N; break;
			case S: Dir = W; break;
			default: exit(1);
		}
	}

	// We just turn left since there was a wall in front of us, so we don't need to check it again
	void searchDirectionRec( int8_t* neighbours )
	{
		// There is a wall on its right hand, and in front there is not a wall
		if ( neighbours[Dir] != WALL )
			return;
		else // It cannot go neither right nor forward, so it turn left
		{
			turnL();
			searchDirectionRec( neighbours );
		}
	}

	// Keep always the wall on its right hand. neighbours[4] = { valE, valN, valW, valS }
	void searchDirection( int8_t* neighbours )
	{
		// If there is not a Wall on its right hand, turn right
		if ( neighbours[(Dir+NUM_DIRECTIONS-1)%NUM_DIRECTIONS] != WALL )
			turnR();
		else if ( neighbours[Dir] != WALL ) // There is a wall on its right hand, and in front there is not a wall
			return;
		else // It cannot go neither right nor forward, so it turn left
		{
			turnL();
			searchDirectionRec( neighbours );
		}
	}

	void move( Maze& maze, size_t* result )
	{
		// We are get out of the cell, so we increment the number of times we visited it
		int8_t old = maze.get( Y, X );
		maze.set( Y, X, old + 1 );
		result[old]--;
		result[old+1]++;

		// Make the real movement towards the chosen direction
		switch( Dir )
		{
			case E: X++; break;
			case N: Y--; break;
			case W: X--; break;
			case S: Y++; break;
			default: exit(1);
		}
	}
};

void printResult( size_t* result )
{
	for ( int i = 0; i < NUM_RESULTS; i++ )
		cout << setw(3) << result[i];
	cout << endl;
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	// For debugging with redirection
	// std::ifstream in( "/home/draxent/Scrivania/Contests/556/input0.txt" );
	// std::cin.rdbuf( in.rdbuf() );

	// Number of rows and columns of the maze
	size_t rows, columns;
	// The mouse object
	Mouse mouse;
	/*
	 * Results:
	 * [0] -> number of not visited cell
	 * [1] -> number of cell visited once
	 * [2] -> number of cell visited twice
	 * [3] -> number of cell visited thrice
	 * [4] -> number of cell visited four times
	 */
	size_t result[NUM_RESULTS];
	// Neighbours value
	int8_t neighbours[NUM_DIRECTIONS];

	while ( true )
	{
		// Reset result
		for ( int i = 0; i < NUM_RESULTS; i++ )
			result[i] = 0;

		// Read maze size
		cin >> rows;
		cin >> columns;

		// Exit if they are both zeros
		if ( rows == 0 && columns == 0 )
			break;

		// Starting position of the mouse
		mouse.Dir = E;
		mouse.Y = rows - 1;
		mouse.X = 0;

		// The maze data structure
		Maze maze( rows, columns, result );
#if PRINT_MAZE
		maze.print();
#endif

		// Repeat until it return in the starting position
		do
		{
			// Extract Neighbours values
			neighbours[0] = maze.get( mouse.Y, mouse.X+1);
			neighbours[1] = maze.get( mouse.Y-1, mouse.X );
			neighbours[2] = maze.get( mouse.Y, mouse.X-1);
			neighbours[3] = maze.get( mouse.Y+1, mouse.X );

			// The mouse search the first allowed direction
			mouse.searchDirection( neighbours );

			// The mouse move in the chosen direction
			mouse.move( maze, result );

#if PRINT_MAZE
			maze.print();
#endif
		} while ( !(( mouse.Y == rows - 1 ) && ( mouse.X == 0 )) );

		printResult( result );
	}

	return 0;
}