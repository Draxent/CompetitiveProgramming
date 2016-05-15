#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int road; // the length of the road before the gap.
    cin >> road; cin.ignore();
    int gap; // the length of the gap.
    cin >> gap; cin.ignore();
    int platform; // the length of the landing platform.
    cin >> platform; cin.ignore();
    bool jump = false;

    // game loop
    while (1) {
        int speed; // the motorbike's speed.
        cin >> speed; cin.ignore();
        int coordX; // the position on the road of the motorbike.
        cin >> coordX; cin.ignore();
        
        cerr << "road: " << road << ", gap: " << gap << ", platform: " << platform << endl;
        cerr << "speed: " << speed << ", coordX: " << coordX << endl;
        
		// THIS SOLUTION DOES NOT CONSIDER ALL POSSIBLE CASE:
		// IF GOING TO FAST THE MOTORBIKE DO NOT REACH EXACTLY THE END OF ROAD, TE SPEED == GAP IS NOT SUFFICIENT TO JUMP THE GAP
		// so it should be considered looking to the remaining turns before the jump, and other variables
		// in order to understand the action to do
		// in particular shold be used a preprocessing phase in which every action is decided and is generated
		// knowing the speed and coordX its enougth to caluclate everything from the first round.
        if ( !jump )
        {
            if ( coordX + speed > road )
            {
                cout << "JUMP" << endl;
                jump = true;
            }
            else
            {
                if ( speed <= gap )
                    cout << "SPEED" << endl;
                else if ( speed > gap + 1 )
                    cout << "SLOW" << endl;
                else
                    cout << "WAIT" << endl;
            }
        }
        else
            cout << "SLOW" << endl;
    }
}
