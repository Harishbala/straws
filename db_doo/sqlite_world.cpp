#include<iostream>
#include<sqlite3.h>

int main()
{
    sqlite3 *db;
    int rc = sqlite3_open("sqlite_world", &db);
    if( rc )
    {
        sqlite3_close(db);
    }
    return 0;
}
