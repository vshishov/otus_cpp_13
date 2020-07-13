#pragma once

#include "session.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

namespace otus {

class TableRow
{
public:
  TableRow(int a_nInd = -1, const std::string& a_strValue = "")
    : m_nId(a_nInd)
    , m_strValue(a_strValue)
  { }

private:
  int m_nId;
  std::string m_strValue;
};

using Index = std::set<TableRow>;

class Table {
public:
  Table()
  { }

private:
  Index m_Rows;
};

using Tables = std::unordered_map<std::string, Table>;

} // otus::
