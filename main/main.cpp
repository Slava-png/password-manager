#include <string>
#include <vector>
#include <algorithm>

#include "main.hpp"
#include "../fileInteration/fileInteration.hpp"

auto records = std::vector<Record*> {};
auto categories = std::vector<std::string> {};
auto firstLine = std::string();

auto main() -> int {
    chooseFile();
}


auto setFirstLine(std::string const& line) -> void {
    firstLine = line;
}

auto getFirstLine() -> std::string {
    return firstLine;
}

auto addRecord(Record* ps) -> void {
    records.push_back(ps);
}

auto getRecords() -> std::vector<Record*> {
    return records;
}

auto deleteRecord(Record* const& record) -> void {
    records.erase(std::ranges::find(records, record));
    delete record;
}

auto emptyRecords() -> void {
    records.clear();
}

auto getCategories() -> std::vector<std::string>& {
    return categories;
}

auto addCategory(std::string const& category) -> void {
    categories.push_back(category);
}

auto emptyCategories() -> void {
    categories = std::vector<std::string> {};
}
