#pragma  once

#include <string>
#include <memory>

class Database;

namespace FileParser
{
bool parseFile(const std::string &fileName, std::shared_ptr<Database> db);
};