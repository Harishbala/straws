//Code credit: Following code has been constructed using codes from following web pages
//https://www.sqlite.org/quickstart.html
//https://gist.github.com/enile8/2424514
//set tabstop=2 shiftwidth=2 expandtab
    
#include<iostream>
#include<sqlite3.h>

static int callback(void *notUsed, int argc, char** argv, char **azColName)
{
    int i;
    for(i = 0; i < argc; i++)
    {
        std::cout<<azColName[i]<<" = ";
        if(argv[i])
            std::cout<<argv[i];
        else
            std::cout<<"null";
        std::cout<<"\n";
    }
    return 0;
}    

int main()
{
    sqlite3 *db;
    int rc = sqlite3_open("sqlite_world.db", &db);
    if( rc )
    {
        std::cout<<"Failed to open database : "<<sqlite3_errmsg(db)<<"\n";
        sqlite3_close(db);
    }
    else
    {
        std::cout<<"Opened database successfully\n\n";
    }

    
    char* err_msg;
    rc = sqlite3_exec(db, "create table test(id int, name varchar(255))", callback, 0, &err_msg);
    if(rc == SQLITE_OK)
    {
        std::cout<<"Table created!\n";
    }
    else
    {
        std::cout<<"Table creation failed\n";
    }
    
    sqlite3_exec(db,"insert into test (id, name) values (1, 'Newton')", callback, 0, &err_msg);

    sqlite3_exec(db, "select id from test", callback, 0, &err_msg);
    sqlite3_close(db);
    return 0;
}
