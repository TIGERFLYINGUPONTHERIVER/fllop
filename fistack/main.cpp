#include "./fistack.hpp"

int main()
{
    FIStack<char> stack;

    while(1)
    {
        int i=0;
        while( i<1000 )     
        {
            stack.pushData( 'c' );
            ++i;
        }

        int j = 0;

        while( stack.getSize() > 0 )
        {
            stack.popData();
            cout << ++j << endl;
        }

        char ch;
        cin >> ch;
        if( ch == 'a' ) continue;
        else            break;

    }

    return 0;
}
