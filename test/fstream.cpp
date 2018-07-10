#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    fstream _file_dd;
    _file_dd.open( "../.data/total", ios_base::in | ios_base::out | ios_base::app );

    if( !_file_dd.is_open() )
    {
        return 0;
    }

    char c;

    int i = -2;


    while( c!= '&' )
    {
        _file_dd.seekg( i, ios::end );
        c = _file_dd.peek();
        if( c == ':' ) break;
        cout << c << endl;

        --i;
    }

    return 0;
}
