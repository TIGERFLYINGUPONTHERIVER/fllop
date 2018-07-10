#include "fisql.h"

FISql::FISql()
{
    connection = mysql_init( NULL );
}

FISql::~FISql()
{
    mysql_close( connection );
}

bool FISql::initFISql( string host, string user, string pwd, string db_name , string present_tb="present_list", string depot_tb="depot_list")
{
    if( !mysql_real_connect( connection, host.c_str(), user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0 ) )
    {
        cout << "connect error." << endl;
        return false;
    }

    _present_tb = present_tb;
    _depot_tb = depot_tb;

    mysql_set_character_set( connection, "utf8" );

    /* make sure tables is exist. */
    int exist = isExist();
    if( exist == -1 )
    {
        cout << "TABLES: " << present_tb << " isn't exist.\n";
        exit( -1 );
    }else if( exist == -2 )
    {
        cout << "TABLES: " << depot_tb << " isn't exist.\n";
        exit( -1 )
    }else if( exist == -3 )
    {
        cout << "TABLES: " << present_list << " and " << 
        depot_tb << " not exist.\n";
        exit( -1 );
    }

    return true;
}

bool FISql::setDatabase( string command )
{
    if( mysql_query( connection, command.c_str() ) )
    {
        cout << "query error." << endl;
        return false;
    }

//    cout << "执行结果:\n" << command << endl;

    return true;
}

string FISql::viewDatabase( string command )
{
    if( mysql_query( connection, command.c_str() ) )
    {
        cout << "viewDatabase error." << endl;
        exit(-1);
    }

    string str;

    result = mysql_store_result( connection );
    for( int i=0; i<mysql_field_count(connection); ++i )
    {
        row = mysql_fetch_row(result);
        if( row <= 0 )      break;
        for( int j=0; j<mysql_num_fields(result); ++j )
        {
            str = str + row[j] + ' ';
//            cout << row[j] << endl;
            str = str + '\n';
        }
        str = str + '\n';
    }

    mysql_free_result( result );

    return str;
}

unsigned FISql::viewDatabase( unsigned code, string db_name )
{
    string dbstring;
    if( db_name == _present_tb )
        dbstring = "select nums from" + _present_tb + "where code = " 
                    + to_string(code);
    else if( db_name == _depot_tb && (code == 0 || code == 1) )
        dbstring = "select total from " + _depot_tb + " where state = " 
                    + to_string(code);
    else{
        cout << "input error.\n";
        exit(-1);
    }

    if( mysql_query( connection, dbstring.c_str() ) )
    {
        cout << "viewDatabase error." << endl;
        exit(-1);
    }

    int nc = 0;
    
    result = mysql_store_result( connection );
    for(int i=0; i<mysql_field_count(connection); ++i)
    {
        row = mysql_fetch_row( result );
        if( row<=0 )        break;
        for( int j=0; j<mysql_num_fields(result); ++j )
        {
            //提取数字
            nc = atoi(row[j]);
        }
    }

    mysql_free_result( result );

    return nc;
}

bool FISql::viewAllDatas( string db_name )
{
    if( db_name != _present_tb || db_name != _depot_tb )  return false;

    string command = "select * from " + db_name;

    //success return 0, else return !0
    if( mysql_query( connection, command.c_str() ) )
    {
        cout << "viewAllDatas error." << endl;
        return false;
    }

    result = mysql_store_result( connection );
    for( int i=0; i<mysql_field_count(connection); ++i )
    {
        row = mysql_fetch_row( result );
        if( row <= 0 )  break;

        for( int j=0; j<mysql_num_fields(result); ++j )
        {
            cout << row[j] << ' ';
        }
        cout << '\n';
    }

    mysql_free_result( result );

    return true;
}

unsigned FISql::FISql_Datediff()
{
    string s = "select datediff((select date from depot_list where state = 1), now())";

    unsigned num = 0;

    if( mysql_query( connection, s.c_str() ) )
    {
        cout << " query date error." << endl;
        exit( -1 );
    }

    result = mysql_store_result( connection );

    for( int i=0; i<mysql_field_count(connection); ++i )
    {
        row = mysql_fetch_row( result );
        if( row <= 0 )      break;

        for( int j=0; j<mysql_num_fields(result); ++j )
        {
            // cmath头文件      fabs() 绝对值 
            num = num*10 + abs( atoi(row[j]) );
        }
    }
    mysql_free_result( result );

    return num;
}

string FISql::viewDatabase( unsigned code )
{
    // 检索present_list表段数据，返回供显示
    //
    string str;

    str = "select * from " + _present_tb + " where code = " 
            + to_string(code);

    if( code != 0 )
    {
        if( mysql_query( connection, str.c_str() ))
        {
            cout << "query error." << endl;
            exit( -1 );
        }

        result = mysql_store_result( connection );
        for(int i=0; i<mysql_field_count(connection); ++i)
        {
            row = mysql_fetch_row( result );
            if( row <= 0 )      break;
            for(int j=0; j<mysql_num_fields(result); ++j)
            {
                str = str + row[j];
            }
            str = str + '\n';
        }

        mysql_free_result( result );

        return str;
    }
    else    exit( -1 );
}

int FISql::isExist()
{
    /* auto run. make sure _present_tb && _depot_tb is exist */
    bool prestate = true;
    bool depstate = true;

    string str;
    string existSTR;
    MYSQL_RES       *stateRES;
    MYSQL_RES       *stateROW;

    for( int x=0; x<2; ++x )
    {
        if( x=0 )   
                    str = "show databases like " + "'" + _present_tb + "'";
        else if( x=1 )        
                    str = "show databases like " + "'" + _depot_tb + "'";

        mysql_query( connection, str.c_str() );
        stateRES = mysql_store_result( connection );

        for( int i=0; i<mysql_field_count(connection), ++i )
        {
            row = mysql_fetch_row( result );
            if( row <= 0 )  break;
            for( int j=0; j<mysql_num_fields(result); ++j )
            {
                existSTR = existSTR + row[j];
            }
        }

        if( existSTR.length() == 0 && x == 0 )  prestate = false;
        if( existSTR.length() == 0 && x == 1 )  depstate = false;
    }

    if( prestate && depstate )      return 0;
    if( !prestate && depstate )     return -1;
    if( prestate && !depstate )     return -2;
    if( !prestate && !depstate )    return -3;
}
