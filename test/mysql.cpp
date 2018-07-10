#include <iostream>
#include <mysql/mysql.h>
#include <string>
using namespace std;

int main()
{
    MYSQL *connection;

    connection = mysql_init( NULL );
    if( !mysql_real_connect( connection, "localhost", "root", "qwe123", 
                          "test", 0, NULL, 0) )
    {
        cout << "connect error.\n";
    }

    if( mysql_query( connection, "show tables like 'sspresent'" ) )
    {
        cout << "query error.\n";
    }

    string str;

    MYSQL_RES       *result;
    MYSQL_ROW       row;
    
    result = mysql_store_result( connection );

    for( int i=0; i<mysql_field_count(connection); ++i )
    {
        row = mysql_fetch_row( result );
        if( row <= 0 )  break;
        for( int j=0; j<mysql_num_fields(result); ++j )
        {
            str = str + row[j];
        }
        cout << '\n';
    }
    
    if( str.length() == 0 )
    {
        cout << "didn't find it\n";
    }
    

    mysql_free_result( result );

    return 0;
}
