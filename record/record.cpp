#include <string>
#include <vector>
#include <fmt/ranges.h>
#include <algorithm>

#include "record.hpp"
#include "../main/main.hpp"

Record::Record(std::string const& id, std::string const& category, std::string const& name, std::string const& login, std::string const& password) {
    id_ = id;
    category_ = category;
    name_ = name;
    login_ = login;
    password_ = password;
}

Record::~Record() {}

auto Record::getId() -> int {
    return std::stoi(id_);
}

auto Record::setId(std::string const& id) -> void {
    id_ = id;
}

auto Record::getName() -> std::string {
    return name_;
}

auto Record::getCategory() -> std::string {
    return category_;
}

auto Record::setPassword(std::string const& newPassword) -> void {
    password_ = newPassword;
}

auto Record::buildRecordFromData() -> std::string {
    auto nam = name_;
    auto log = login_;
    auto id = id_;
    auto cat = category_;
    auto pas = password_;

    auto addSpaces = [](int neededLen, std::string& element) -> void {
        while (element.size() != neededLen) {
            element = " " + element;
        }
    };

    addSpaces(4, id);
    addSpaces(22, log);
    addSpaces(22, nam);
    addSpaces(22, cat);
    addSpaces(26, pas);

    return id + "|" + cat + "|" + nam + "|" + log + "|" + pas + "\n";
}

auto Record::extractDataFromRecord(std::string const& line) -> Record* {
    auto vec = std::vector<std::string> {};
    auto pieceOfData = std::string();

    auto trim = [](std::string const& record) -> std::string {
        auto trimmed = std::string();
        for (int i = record.size() - 1; i >= 0; i--) {
            if (record[i] != ' ') {
                trimmed = record[i] + trimmed;
            }
        }
        return trimmed;
    };

    for (auto const& element: line) {
        if (element == '|'){
            vec.push_back(trim(pieceOfData));
            pieceOfData = "";
        } else {
            pieceOfData += element;
        }
    }
    if (not pieceOfData.empty()) {
        vec.push_back(pieceOfData);
    }
    return new Record(vec[0], vec[1], vec[2], vec[3], vec[4]);;
}

auto Record::printAllRecords() -> void {
    fmt::print("==============BEGIN==============\n");
    fmt::print("{}\n", getFirstLine());
    std::ranges::for_each(getRecords(), [](Record* const& record) {fmt::print("{}", record->buildRecordFromData());});
    fmt::print("===============END===============\n");
}
