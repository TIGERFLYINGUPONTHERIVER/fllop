#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main()
{
    fstream ff;
    ff.open("../.data/total", ios_base::in | ios_base::out | ios_base::app);

    for( int i=1; ; ++i )
    {
        ff.seekg( -i, ios::end );
        
        char c;
        c = ff.peek();

        cout << c << endl;

        if( c == '&' )  break;
    }

    return 0;
}
