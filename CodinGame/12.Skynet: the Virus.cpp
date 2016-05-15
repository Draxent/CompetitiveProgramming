#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> gateways;

/**
 * Check if the programmer has lost to find a solution to the problem.
 * @param SI	the index of the node where the Skynet agent is.
 */
bool check_lost( int SI )
{
	for ( int EI : gateways )
	{
		if ( EI == SI )
			return true;
	}
	return false;
}

int main()
{
	ifstream input("input.txt");
	ifstream game("game.txt");

    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    input >> N >> L >> E; 
	input.ignore();

	cout << "N = " << N << ", L = " << L << ", E = " << E << endl;
    
    for (int i = 0; i < L; i++)
    {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        input >> N1 >> N2; input.ignore();

		cout << "N1 = " << N1 << ", N2 = " << N2 << endl;

    }
    for (int i = 0; i < E; i++)
    {
		int EI;
        input >> EI;
		gateways.push_back( EI );
		input.ignore();

		cout << "EI = " << EI << endl;
    }

    // game loop
    while ( true )
    {
        // The index of the node on which the Skynet agent is positioned this turn
        int SI;
        game >> SI; game.ignore();
	
		cout << "SI = " << SI << endl;

		if ( check_lost( SI ) )
			break;
    }

	cout << "LOST THE GAME !! " << endl;
	return 0;		
}
