#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

    // game loop
    while (1)
	{
        int spaceX;
        int spaceY;
        cin >> spaceX >> spaceY; cin.ignore();
        int max = -1;
        int index_max = -1;
        for (int i = 0; i < 8; i++)
        {
            int mountainH;
            // represents the height of one mountain, from 9 to 0.
            // Mountain heights are provided from left to right.
            cin >> mountainH;
            cin.ignore();
            
            if ( mountainH > max )
            {
                max = mountainH;
                index_max = i;
            }
        }
        
        if ( spaceX == index_max )
            cout << "FIRE" << endl;
        else
            cout << "HOLD" << endl;
    }
}
