#include "../contains/contains.h"
#include "./piece.h"

int main()
{
    FISql fisql;
    fisql.initFISql( "127.0.0.1", "root", "qwe123", "fllop" );

    Piece piece;
    piece.autoAddNums();
    
    string reason;
    unsigned num;

    cout << "REASON: ";
    cin >> reason;
    cout << "NUM: ";
    cin >> num;
    piece.handAddNums(reason, num);

    return 0;
}
