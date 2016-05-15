#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

void str2lower( string& s )
{
    transform( s.begin(), s.end(), s.begin(), ::tolower );
}

int main()
{
    unordered_map<string,string> map;
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();
    
    for ( int i = 0; i < N; i++ )
    {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();
        
        // Trasfrom extension to lower
        str2lower( EXT );
        
        // Insert in map
        std::pair<string, string> pair( EXT, MT );
        map.insert( pair );
    }
    
    for ( int i = 0; i < Q; i++ )
    {
        string FNAME; // One file name per line.
        getline( cin, FNAME );
        
        // Extract extension
        int pos = FNAME.find_last_of(".");
        
        // Extension not found
        if ( pos == -1 )
        {
            cout << "UNKNOWN" << endl;
            continue;
        }
        
        string ext = FNAME.substr( pos + 1 );
        // Trasfrom extension to lower
        str2lower( ext );
        
        unordered_map<string, string>::const_iterator got = map.find( ext );
        
        if ( got == map.end() )
            cout << "UNKNOWN" << endl;
        else
            cout << got->second << endl;
    }

	return 0;
}
