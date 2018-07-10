#include "../contains/contains.h"

#ifndef     __FISql__H__
#define     __FISql__H__

/* 成功连接数据库后
 * 如该数据库没有该db_name，则自动创建，默认名字是present_list, depot_list
 *
 */

class FISql
{
public:
    FISql();
    ~FISql();
    bool        initFISql(string host, string user, string pwd, 
                          string db_name, string present_tb, string depot_tb);
    //直接写命令
    bool        setDatabase(string command);

    string      viewDatabase(string command);
    string      viewDatabase(unsigned code);        //view present list.

    //返回present_list的code-num   depot_list中的state-total
    unsigned    viewDatabase(unsigned code, string db_name);


    bool        viewAllDatas(string db_name);

    //获取当前时间与最后一次存储时间过了多少天

    unsigned    FISql_Datediff();

    /* -1       present_list not exist  */
    /* -2       depot_list not exist    */
    /* -3       all not exist           */
    /* 0        exist                   */
    int        isExist();

private:
    MYSQL           *connection;
    MYSQL_ROW       row;
    MYSQL_RES       *result;

    string          _present_tb;
    string          _depot_tb;
};

#endif
