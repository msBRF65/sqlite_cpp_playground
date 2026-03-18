#include <sqlite3.h>

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// ref: https://sqlite.org/quickstart.html

std::mutex db_mutex;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL")
              << std::endl;
  }
  std::cout << std::endl;
  return 0;
}

int thread(std::vector<std::string> sql_vec) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  std::cout << "Hello, SQLite!" << std::endl;
  rc = sqlite3_open_v2("/home/dev/sqlite_cpp_playground/database/test.db", &db,
                       SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  std::cout << "Opened database successfully" << std::endl;

  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    return (1);
  }

  for (const auto &sql : sql_vec) {
    db_mutex.lock();
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    db_mutex.unlock();
    if (rc != SQLITE_OK) {
      std::cerr << "SQL command failed: " << sql << std::endl;
      std::cerr << "SQL error: " << zErrMsg << std::endl;
      sqlite3_free(zErrMsg);
    }
  }

  sqlite3_close(db);
  std::cout << "Closed database successfully" << std::endl;

  return 0;
}

int main() {
  std::vector<std::string> sql_vec1, sql_vec2;
  sql_vec1.push_back(
      "CREATE TABLE IF NOT EXISTS COMPANY("
      "ID INT PRIMARY KEY     NOT NULL,"
      "NAME           TEXT    NOT NULL,"
      "AGE            INT     NOT NULL,"
      "ADDRESS        CHAR(50),"
      "SALARY         REAL );");
  sql_vec1.push_back(
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
      "VALUES (1, 'Paul', 32, 'California', 20000.00 );");
  sql_vec1.push_back(
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
      "VALUES (2, 'Allen', 25, 'Texas', 15000.00 );");

  sql_vec2.push_back(
      "CREATE TABLE IF NOT EXISTS COMPANY("
      "ID INT PRIMARY KEY     NOT NULL,"
      "NAME           TEXT    NOT NULL,"
      "AGE            INT     NOT NULL,"
      "ADDRESS        CHAR(50),"
      "SALARY         REAL );");
  sql_vec2.push_back(
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
      "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );");
  sql_vec2.push_back(
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
      "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );");
  sql_vec2.push_back("SELECT * from COMPANY;");

  // multi-threading test
  std::thread t1(thread, sql_vec1);
  std::thread t2(thread, sql_vec2);
  t1.join();
  t2.join();
  return 0;
}