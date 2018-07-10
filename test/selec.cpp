#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    fd_set rd;
    struct timeval tv;
    int err;

    FD_ZERO( &rd );
    FD_SET( 0, &rd );

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    err = select( 1, &rd, NULL, NULL, &tv );

    if( err == 0 )  cout << "time out\n";
    else if( err == -1 )
        cout << "error\n";
    else
    cout << "success\n";

    return 0;
}
