#include "./piece.h"

/*  WARNINGS:
 *      101 :   filesystem will be alter by anything.
 *      108 :   when database's command not run well, \
 *              it not will change back.
 */

#define STATE   1

Piece::Piece()
{
    _file_depot.open( "../.data/depot", ios_base::in | ios_base::out | ios_base::app );
    _file_total.open( "../.data/total", ios_base::in | ios_base::out | ios_base::app );
    _file_exchange.open( "../.data/exchange", ios_base::in | ios_base::out | ios_base::app );

    if( !_file_depot.is_open() || !_file_total.is_open() || !_file_exchange.is_open() )
    {
        cout << "Piece create Error." << endl;
        exit(-1);
    }

    if( !_fisql_fllop.initFISql( "127.0.0.1", "root", "qwe123", "fllop" ) )
    {
        cout << "init sql error." << endl;
        exit(-1);
    }

    //  init total
    _total = 0;

    #pragma warning(BUGS:101)   //cannot forbid filesystem to change

    //open success. read data.
    for( int i=1; ; ++i )       //  filesystem cannot open by other ways.\
    otherwise it will auto add a \n. and i should be 2;
    {
        _file_total.seekg( -i, ios::end );
        char c;
        c = _file_total.peek();

        if( c == '&' )   break;
        //  first is pow(10, 1); sec pow(10, 2); thr pow(10,3);
        _total = _total + ( (c - 48 ) * pow(10, i-1) );
    }

    //local file system was not synchronize with the sql.
    if( _fisql_fllop.viewDatabase(STATE, "depot_list") != _total  )
    {
        cout << "local:" << _total << '\n';
        cout << "server:" << _fisql_fllop.viewDatabase(STATE, "depot_list") << '\n';
        cout << "Synchronize? Y/N: ";
        char c;
        cin >> c;
        if( c == 'Y' || c == 'y' )
        {
            _total = _fisql_fllop.viewDatabase( STATE, "depot_list" );
            _file_total << '&';
            _file_total << _total;
        }
        else
        {
            cout << "Error." << endl;
            exit( -1 );
        }
    }

    //all normal.
}

bool Piece::writeData()
{
    //delete old state.

    #pragma warning(BUGS:108)
    //BUG:  when the others method call it, it will rewrite. 
    if( _total != _fisql_fllop.viewDatabase( STATE, "depot_list" ) )
    {
        _fisql_fllop.setDatabase( "update depot_list set state = 0 where state = 1" );

        str = "insert into depot_list values(now()," + to_string( _total ) + "," +  _depot_buffer + "," + to_string(STATE) + ')' ;

        if( !_fisql_fllop.setDatabase( str.c_str() ) )
        {
            cout << "write depot_list error." << endl;
            exit( -1 );
        }
    }


    _file_total << '&';
    _file_total << _total;
    _file_depot << _depot_buffer;
    _file_depot << '\n';

    if( _exchange_buffer.size() > 0 )
    {
        _file_exchange << _exchange_buffer;
        _file_exchange << '\n';
    }
}

bool Piece::flushData()
{
    _depot_buffer = nullptr;
    _exchange_buffer = nullptr;

    // 已经过了_total在构造函数的处理，直接读取数据库
    _total = _fisql_fllop.viewDatabase( STATE, "depot_list" );
}

void Piece::autoAddNums()
{
    //  select date from depot_list where state = 1  &&  now();
    _timesfly  =  _fisql_fllop.FISql_Datediff();
    
    if( _timesfly == 0 )    return;

    _depot_buffer = "'时间过去了" + to_string(_timesfly) + "天，奖励数量:" + to_string(_timesfly) + "'";
    _total += _timesfly;

    writeData();

    cout << _depot_buffer << endl;
}

bool Piece::handAddNums( string reason, unsigned num )
{
    if( num <= 0 )      return false;

    _depot_buffer = "'" + reason + "，奖励数量：" + to_string( num ) + "'";

    char c;
    cout << "---" << _depot_buffer << "---\n";
    cout << "即将写入，确定？ Y/N:";
    cin >> c;
    if( c == 'Y' || c == 'y' )
    {
        _total += num;
        writeData();
    }
    else    _depot_buffer = ' ';
}

unsigned Piece::getNum()
{
    return _fisql_fllop.viewDatabase( STATE, "depot_list" );
}

/*
 *  present block
 */
unsigned Piece::numForCode( unsigned code )
{
    return _fisql_fllop.viewDatabase( code, "present_list" );
}

void Piece::viewAllData( string db_name )
{
    if( !_fisql_fllop.viewAllDatas( db_name ) )
    {
        cout << "view all data error\n";
        exit(0);
    }
}

bool Piece::presentDetail( unsigned code )
{
    // 检索present_list;
    cout << _fisql_fllop.viewDatabase(code) << endl;
}

bool Piece::presentExchange( unsigned code )
{
    unsigned num = _fisql_fllop.viewDatabase( code, "present_list" );
    if( num > _total )  return false;

    _total -= num;
   
    string command;
    command = "update present_list set (nums = (select nums from present_list where code = " + to_string(code) + " ) + 1) where code = " + to_string(code);

    _fisql_fllop.setDatabase( command.c_str() );

    str = _fisql_fllop.viewDatabase( "select now()" ) ;

    _exchange_buffer = str + '\n' + "花费" + to_string(code) + "成功兑换" +  (_fisql_fllop.viewDatabase( "select present from present_list where code = "+to_string(code)) );

    writeData();
}

//databases: present_list
bool Piece::insertPresent( string name, unsigned code, unsigned num )
{
}

bool Piece::delPresent( unsigned code )
{
}

Piece::~Piece()
{
    _file_depot.close();
    _file_total.close();
    _file_exchange.close();
}
