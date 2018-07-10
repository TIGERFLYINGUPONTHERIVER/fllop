#ifndef     __PIECE__H__
#define     __PIECE__H__
#include "../fisql/fisql.h"
#include "../contains/contains.h"
//#include "../fisql/fisql.hpp"
//#include "../fistack/fistack.hpp"

class Piece
{
public:
    Piece();
    ~Piece();
    //num
    void        autoAddNums();
    bool        handAddNums(string reason, unsigned num);
    unsigned    getNum();
    //present
    unsigned    numForCode(unsigned code);
    void        viewAllData(string db_name);
    bool        presentDetail(unsigned code);
    bool        presentExchange(unsigned code);
    
    //present database
    bool        insertPresent(string name, unsigned code, unsigned num);
    bool        delPresent(unsigned code);

    //write && flush
    bool        writeData();
    bool        flushData();

private:
    fstream     _file_depot;
    fstream     _file_total;
    fstream     _file_exchange;

    FISql       _fisql_fllop;

    unsigned    _total;

    //
    string      str;    //buffer

    string      _depot_buffer;
    string      _exchange_buffer;

    unsigned    _timesfly;
};

#endif      //__PIECE__H__mZ
