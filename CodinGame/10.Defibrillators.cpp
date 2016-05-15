#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

#define PI 3.14159265
#define EARTH_RADIUS 6371

struct defibrillator_t
{
    int id; // A number identifying the defibrillator
    string name; // Name
    string address; // Address
    string phone; // Contact Phone number
    double longitude; // Longitude (degrees)
    double latitude; // Latitude (degrees)
};


double convert_double( string& s )
{
    int pos = s.find_last_of( ',' );
    // Change ',' in '.'
    if ( pos != -1 )
        s[pos] = '.';
        
    return stod( s );
}

int main()
{
    const string delimiter = ";";
    string LON;
    cin >> LON; cin.ignore();
    string LAT;
    cin >> LAT; cin.ignore();
    int N;
    cin >> N; cin.ignore();
    defibrillator_t def;
    
    // Convert LON, LAT in double
    double lon = convert_double( LON );
    double lat = convert_double( LAT );
    double min_distance = numeric_limits<double>::max();
    string answer;
    
    for ( int i = 0; i < N; i++ )
    {
        int start, end;
        double x, y, d;
        string token;
        string DEFIB;
        getline(cin, DEFIB);
        
        // Find first delimiter
        start = 0;
        end = DEFIB.find( delimiter );
        
        // Extract id
        token = DEFIB.substr( start, end - start );
        def.id = stoi( token );
        
        // Find second delimiter
        start = end + delimiter.length();
        end = DEFIB.find( delimiter, start );
        
        // Extract name
        token = DEFIB.substr( start, end - start );
        def.name = token;
        
        // Find third delimiter
        start = end + delimiter.length();
        end = DEFIB.find( delimiter, start );
        
        // Extract address
        token = DEFIB.substr( start, end - start );
        def.address = token;
        
        // Find fourth delimiter
        start = end + delimiter.length();
        end = DEFIB.find( delimiter, start );
        
        // Extract phone
        token = DEFIB.substr( start, end - start );
        def.phone = token;
        
        // Find fifth delimiter
        start = end + delimiter.length();
        end = DEFIB.find( delimiter, start );
        
        // Extract longitude
        token = DEFIB.substr( start, end - start );
        def.longitude = convert_double( token );
        
        // Find sixth delimiter
        start = end + delimiter.length();
        end = DEFIB.find( delimiter, start );
        
        // Extract latitude
        token = DEFIB.substr( start, end - start );
        def.latitude = convert_double( token );
        
        /* DEBUG
        cerr << def.id << " ; ";
        cerr << def.name << " ; ";
        cerr << def.address << " ; ";
        cerr << def.phone << " ; ";
        cerr << def.longitude << " ; ";
        cerr << def.latitude << " ; ";
        cerr << endl;
        */
        
        x = ( def.longitude - lon ) * cos ( ( lat + def.latitude ) / 2 * PI / 180.0 );
        y = def.latitude - lat;
        d = sqrt( x*x + y*y ) * EARTH_RADIUS;
        
        if ( d < min_distance )
        {
            min_distance = d;
            answer = def.name;
        }
    }
    
    cout << answer << endl;
	return 0;    
}
