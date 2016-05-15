#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	// the number of points used to draw the surface of Mars.
    int surfaceN; 
    cin >> surfaceN; cin.ignore();

    for (int i = 0; i < surfaceN; i++)
	{
		// X coordinate of a surface point. (0 to 6999)
        int landX;
		// Y coordinate of a surface point.
		// By linking all the points together in a sequential fashion, you form the surface of Mars.
        int landY; 
        cin >> landX >> landY; cin.ignore();
    }

    while (1)
	{
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power;
		cin.ignore();
        
        if ( vSpeed <= -40 )
            cout << "0 4" << endl;
        else
            cout << "0 0" << endl;
    }
}
