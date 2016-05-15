#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define ALPHABET_SIZE 27
#define MAX_L 30
#define MAX_H 30
#define MAX_N 200

int index( const char c )
{
    switch( c )
    {
        case 'a': case 'A': return  0;
        case 'b': case 'B': return  1;
        case 'c': case 'C': return  2;
        case 'd': case 'D': return  3;
        case 'e': case 'E': return  4;
        case 'f': case 'F': return  5;
        case 'g': case 'G': return  6;
        case 'h': case 'H': return  7;
        case 'i': case 'I': return  8;
        case 'j': case 'J': return  9;
        case 'k': case 'K': return 10;
        case 'l': case 'L': return 11;
        case 'm': case 'M': return 12;
        case 'n': case 'N': return 13;
        case 'o': case 'O': return 14;
        case 'p': case 'P': return 15;
        case 'q': case 'Q': return 16;
        case 'r': case 'R': return 17;
        case 's': case 'S': return 18;
        case 't': case 'T': return 19;
        case 'u': case 'U': return 20;
        case 'v': case 'V': return 21;
        case 'w': case 'W': return 22;
        case 'x': case 'X': return 23;
        case 'y': case 'Y': return 24;
        case 'z': case 'Z': return 25;
        default: return 26;
    }
}

int main()
{
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    
    // Initialize array of letters
    char letters[ALPHABET_SIZE][MAX_H][MAX_L];
    for ( int i = 0; i < H; i++ )
    {
        string ROW;
        getline( cin, ROW );
        
        for ( int k = 0; k < ALPHABET_SIZE; k++ )
        {
            for ( int j = 0; j < L; j++ )
                letters[k][i][j] = ROW[k*L + j];
        }
    }
    
    // print the letters on screen
    for ( int i = 0; i < H; i++ )
    {
        for ( int k = 0; k < T.length(); k++ )
        {
            for ( int j = 0; j < L; j++ )
                cout << letters[index(T[k])][i][j];
        }
        cout << endl;
    }
}
