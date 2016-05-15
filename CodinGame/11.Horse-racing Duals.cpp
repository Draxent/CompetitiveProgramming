#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_SIZE 100000
#define MAX_STRENGTH 10000000

int main()
{
    int N;
    cin >> N; cin.ignore();
    
    int strengths[MAX_SIZE];
    for ( int i = 0; i < N; i++ )
    {
        int Pi;
        cin >> Pi; cin.ignore();
        
        strengths[i] = Pi;
    }
    
    // Sort Array
    sort( strengths, strengths + N );
    
    int min_gap = MAX_STRENGTH;
    for ( int i = 0; i < N - 1; i++ )
    {
        int gap = strengths[i + 1] - strengths[i];
        min_gap = ( gap < min_gap ) ? gap : min_gap;
    }
    
    cout << min_gap << endl;
}
