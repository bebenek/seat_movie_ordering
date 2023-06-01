#include "file_parser.h"

#include <fstream>
#include <iostream>
#include "rapidjson/document.h"
#include "database.h"

using namespace rapidjson;

namespace FileParser
{
bool parseFile(const std::string &fileName, std::shared_ptr<Database> db)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        Document d;
        ParseResult ok = d.Parse(line.c_str());
        if (!ok)
        {
            return false;
        }

        std::string movie;
        auto it = d.FindMember("movie");
        if (it == d.MemberEnd())
            return false;
        auto &v = it->value;
        if (!v.IsString())
            return false;
        movie = v.GetString();

        std::string theater;
        it = d.FindMember("theater");
        if (it == d.MemberEnd())
            return false;
        v = it->value;
        if (!v.IsString())
            return false;
        theater = v.GetString();

        Database::Seats seats;
        it = d.FindMember("seat");
        if (it == d.MemberEnd())
            return false;
        v = it->value;
        if (!v.IsArray())
            return false;
        // iterate over the array of strings (like A1 A2 ect) and translate values into position in seats and mark that position as 1
        for (auto &seat : v.GetArray())
        {
            if (!seat.IsString())
                return false;
            std::string seat_str = seat.GetString();
            if (seat_str.size() != 2)
            {
                return false;
            }
            int row = seat_str[0] - 'A';
            int col = seat_str[1] - '1';
            if (row < 0 || row > 4 || col < 0 || col > 3)
            {
                return false;
            }
            seats[row][col] = 1;
        }
        db->addShow(movie, theater, seats);
    }

    return true;
}

} // namespace FileParser