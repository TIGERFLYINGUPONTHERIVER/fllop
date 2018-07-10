
databases:
	fllop : 
		present_list : tinytext present, smallint code, smallint times

class & include:
	contains: contain cpps title that must contains.
		including:  <iostream> <string> <mysql/mysql.h> <cstdlib>
			using namespace std;

	fisql:	base on mysql.
		//	write commond with your own.
		bool 		FISql::init(string host, string user, string pwd, string db_name)
		bool 		FISql::setDatabase(string command)	print out.
		string 		FISql::viewDatabase(string command)	return.
		unsinged	FISql::viewDatabase(unsinged int)	return.
		bool 		FISql::viewAllDatas(string command)	print out

	fistack:
		bool		FIStack<>
# fllop
