#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;


int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    
    // Allocate matrix
    // true -> presence of node, false -> empty cell
    bool** matrix = new bool*[height];
    for ( int i = 0; i < height; i++ )
        matrix[i] = new bool[width];
    
    for ( int i = 0; i < height; i++ )
    {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        
        for ( int j = 0; j < width; j++ )
            matrix[i][j] = ( line[j] == '0' ) ? true : false;
    }

    // cout << "0 0 1 0 0 1" << endl;
    // Three coordinates: a node, its right neighbor, its bottom neighbor
    
    for ( int i = 0; i < height; i++ )
    {
        for ( int j = 0; j < width; j++ )
            cerr << matrix[i][j] << " ";
        cerr << endl;
    }
    cerr << endl << endl;
    
    for ( int i = 0; i < height; i++ )
    {
        int j = 0;
        while ( j < width )
        {
            if ( matrix[i][j] )
            {
                int x = j, y = i;
                
                // (x1,y1) the coordinates of a node
                cout << x << " " << y << " ";
                
                // Skip until don't find true
                while ( ( x + 1 < width ) && !matrix[i][x + 1] ) x++;
                
                // (x2,y2) the coordinates of the closest neighbor on the right of the node
                if ( x + 1 < width )
                    cout << ( x + 1 ) << " " << y << " ";
                else
                    cout << "-1 -1 ";
                    
                // Skip until don't find true
                while ( ( y + 1 < height ) && !matrix[y + 1][j] ) y++;  
                
                // (x3,y3) the coordinates of the closest bottom neighbor
                if ( y + 1 < height )
                    cout << j << " " << ( y + 1 ) << endl;
                else
                    cout << "-1 -1" << endl;
                    
                // Skip false nodes
                j = x;
            }
            j++;
        }
    }
}
