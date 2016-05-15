#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void action( string temps, int start, int end, int& closest_to_zero )
{
    string token = temps.substr( start, end - start );
    int num = stoi( token );
    
    if ( abs(num) < abs(closest_to_zero) )
        closest_to_zero = num;
    else if ( (abs(num) == abs(closest_to_zero)) && (num > 0) )
        closest_to_zero = num;  
}
            

int main()
{
    const string delimiter = " ";
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);

    if ( n == 0 )
        cout << "0" << endl;
    else
    {
        int closest_to_zero = 5527;
        
        int start = 0;
        int end = temps.find( delimiter );
        while ( end != string::npos )
        {
            action( temps, start, end, closest_to_zero );
            start = end + delimiter.length();
            end = temps.find( delimiter, start );
        }
        action( temps, start, end, closest_to_zero );

        cout << closest_to_zero << endl;
    }
}
