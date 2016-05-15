#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <sstream>

using namespace std;

#define BITSIZE 7
stringstream ss;
bool first_sequence = true;

/**
 * Process a sequence of equal bits found in the binary set b.
 * The sequence is transformed properly in Chuck Norris encoding and added to the stringstream.
 * @param b		the bitnary set.
 * @param j		last index processed of the binary set.
 * @param one	<c>true</c> if this sequence is made of "1", <c>false</c> otherwise.
 * @param skip	<c>true</c> if we don't have to print the "declaration" of the sequence, since this sequence merge a previous one.
 * @param first	<c>true</c> if this is the first sequence inside the character we are processing
 */
void process_equal_sequence( bitset<BITSIZE> b, int& j, bool one, bool skip, bool first )
{
    if ( !skip )
    {
        string add = "";
		if ( first && !first_sequence )
			add += " ";
        if ( one )
            add += "0";
		else
			add += "00";
        
        ss << add << " ";
    }
    
    
    while ( j >= 0 && ( one == b.test(j) ) )
    {
        ss << "0";
        j--;
    }
}

int main()
{
    string MESSAGE;
	cout << "MESSAGE: ";
    getline( cin, MESSAGE );

    int last_bit = -1;
    for ( int i = 0; i < MESSAGE.length(); i++ )
    {
        int j = BITSIZE - 1;
        char c = MESSAGE.c_str()[i];
        bitset<BITSIZE> binary_c( c );
        cerr << "BIN(" << c << "): " << binary_c << endl;
        
        bool first = true;
        bool one = binary_c.test( j );
        while ( j >= 0 )
        {
			// We skip if is the first sequence analyzed and if the last bit of the previous char is equal the first bit of this char
			bool skip = first && (last_bit == binary_c[BITSIZE - 1]);
            process_equal_sequence( binary_c, j, one, skip, first );

            if ( j >= 0 )
                // Insert space
                ss << " ";

            // Then we switch
            one = !one;
            first = false;
        }

        // Update last bit
        last_bit = binary_c[0];
		first_sequence = false;
    }
    
    cout << "Chuck Norris Encoding: " << ss.str() << endl;
}
