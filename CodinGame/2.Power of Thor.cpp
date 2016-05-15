include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();
    int thorX = initialTX, thorY = initialTY;
    string directionX = "", directionY = "";

    // game loop
    while (1)
	{
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();
        
        if ( thorX > lightX )
            directionX = "W";
        else if ( thorX < lightX )
            directionX = "E";
        else
            directionX = "";
            
        if ( thorY > lightY )
            directionY = "N";
        else if ( thorY < lightY )
            directionY = "S";
        else
            directionY = "";
            
        if ( directionX == "W" ) thorX--;
        else if ( directionX == "E" ) thorX++;

        if ( directionY == "N" ) thorY--;
        else if ( directionY == "S" ) thorY++;

        cout << directionY << directionX << endl;
    }
}
