#include <iostream>
#include <sqlite3.h>

using namespace std;

int main() {
    sqlite3 *db;

    cout << "正在连接数据库..." << endl;

    int rc = sqlite3_open("data/library.db", &db);

    if (rc) {
        cout << "数据库打开失败！" << endl;
        return 0;
    }

    cout << "数据库打开成功！" << endl;

    char *errMsg;

    // 创建用户表
    const char *sql_user =
        "CREATE TABLE IF NOT EXISTS user ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "password TEXT NOT NULL,"
        "role INTEGER);";

    sqlite3_exec(db, sql_user, 0, 0, &errMsg);

    // 创建图书表
    const char *sql_book =
        "CREATE TABLE IF NOT EXISTS book ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT,"
        "author TEXT,"
        "publisher TEXT,"
        "category TEXT,"
        "total INTEGER,"
        "remain INTEGER);";

    sqlite3_exec(db, sql_book, 0, 0, &errMsg);

    // 创建借阅表
    const char *sql_borrow =
        "CREATE TABLE IF NOT EXISTS borrow ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "userid INTEGER,"
        "bookid INTEGER,"
        "borrow_time TEXT,"
        "return_time TEXT,"
        "status INTEGER);";

    sqlite3_exec(db, sql_borrow, 0, 0, &errMsg);

    cout << "三张表创建完成！" << endl;

    sqlite3_close(db);

    return 0;
}
