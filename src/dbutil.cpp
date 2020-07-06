#include "dbutil.h"

#include <iostream>

namespace otus {

void DBUtil::Exec()
{
  sqlite3 *db;

  int rc;

  rc = sqlite3_open("test.db", &db);

  if( rc ) {
    std::cout << "Can't open database: " << sqlite3_errmsg(db);
  } else {
    std::cout << "Opened database successfully\n";
  }
  sqlite3_close(db);
}

} // otus::
