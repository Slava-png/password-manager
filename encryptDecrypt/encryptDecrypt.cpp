#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

#include "../main/main.hpp"
#include "encryptDecrypt.hpp"
#include "../fileInteration/fileInteration.hpp"

auto encrypt(std::string const& password, std::string data) -> std::string {
    auto len = int(password.size());
    auto result = std::string();
    auto count = 0;
    auto shift = 0;

    // add all categories
    if ( not getCategories().empty()) {
        auto categories = std::string();
        for (auto const& category : getCategories()) {
            categories += category + ",";
        }
        data += "\nCategory " + categories;
    }

    // encrypt data
    for (auto const& symbol : data) {
        if (count == len) {
            count = 0;
        }
        if (count % 2 == 0) {
            shift = (static_cast<int>(password[count]) / 2 + len) % 128;
        } else {
            shift = (static_cast<int>(password[count]) * 2 - len) % 128;
        }
        auto asciiValue = static_cast<int>(symbol);
        int shiftedValue = (asciiValue + shift) % 128;
        auto encryptedChar = static_cast<char>(shiftedValue);

        result += encryptedChar;
        count++;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

auto decrypt(std::string const& password, std::string encData) -> std::string {
    auto len = int(password.size());
    auto result = std::string();
    auto count = 0;
    auto shift = 0;

    emptyCategories();
    std::reverse(encData.begin(), encData.end());

    // decrypt data
    for (auto const& symbol: encData) {
        if (count == len) {
            count = 0;
        }
        if (count % 2 == 0) {
            shift = (static_cast<int>(password[count]) / 2 + len) % 128;
        } else {
            shift = (static_cast<int>(password[count]) * 2 - len) % 128;
        }

        auto asciiValue = static_cast<int>(symbol);
        if (asciiValue == 13) {
            asciiValue = 10;
        }
        int shiftedValue = (asciiValue - shift + 128) % 128;
        if (shiftedValue < 0) {
            shiftedValue += 128;  // Handle negative values properly
        }
        auto decryptedChar = static_cast<char>(shiftedValue);

        result += decryptedChar;
        count++;
    }

    // divide files into category and records
    auto stream = std::stringstream(result);
    auto line = std::string();
    auto categories = std::string();
    auto data = std::string();


    // separate result into category and records
    while (std::getline(stream, line)) {
        if (line.substr(0, 9) == "Category ") {
            categories = line.substr(9, line.size() - 9);
        } else if (!line.empty()){
            data += line + "\n";
        }
    }

    // parse category line
    auto category = std::string();
    for (char categorie : categories) {
        if (categorie == ',') {
            addCategory(category);
            category = "";
        } else {
            category += categorie;
        }
    }
    if (!category.empty()) {
        addCategory(category);
    }

    return data;
}

auto parseRecords(std::string const& data) -> void {
    auto lines = std::istringstream(data);
    auto line = std::string();
    std::string::size_type startPos = 0;
    std::string::size_type endPos = 0;
    auto skipFirstLine = true;

    // parse a string of all records to Record objects
    while (endPos != std::string::npos) {
        endPos = data.find_first_of("\r\n", startPos);

        if (endPos != std::string::npos) {
            if (not skipFirstLine){
                addRecord(Record::extractDataFromRecord(data.substr(startPos, endPos - startPos)));
            } else {
                setFirstLine(data.substr(startPos, endPos - startPos));
            }
            skipFirstLine = false;
            startPos = endPos + 1;
        }
    }

    // Add the last line if it doesn't end with a line break
    if (startPos < data.length()) {
        addRecord(Record::extractDataFromRecord(data.substr(startPos)));
    }
}

auto insertNewTimeStamp(std::string encData) -> std::string {
    auto secPos = 8;
    auto minPos = 14;
    auto hourPos = 24;
    auto dayPos = 32;
    auto monPos = 40;
    auto yearPos = 55;

    auto now = std::chrono::system_clock::now();
    auto current_time = std::chrono::system_clock::to_time_t(now);
    auto* local_time = std::localtime(&current_time);

    // Extract parts of time
    auto second = std::to_string(local_time->tm_sec);
    auto minute = std::to_string(local_time->tm_min);
    auto hour = std::to_string(local_time->tm_hour);
    auto day = std::to_string(local_time->tm_mday);
    auto month = std::to_string(local_time->tm_mon + 1);  // Month value is zero-based, so add 1
    auto year = std::to_string(local_time->tm_year + 1900);  // Year value is years since 1900

    // add spaces were needed to make len of every part 2
    if (second.size() != 2) {
        second = " " + second;
    } if (minute.size() != 2) {
        minute = " " + minute;
    } if (hour.size() != 2) {
        hour = " " + hour;
    } if (day.size() != 2) {
        day = " " + day;
    } if (month.size() != 2) {
        month = " " + month;
    }

    encData.insert(secPos, second);
    encData.insert(minPos, minute);
    encData.insert(hourPos, hour);
    encData.insert(dayPos, day);
    encData.insert(monPos, month);
    encData.insert(yearPos, year);

    return encData;
}

auto extractTimeStamp(std::string encData) -> std::string {
    auto secPos = 8;
    auto minPos = 14;
    auto hourPos = 24;
    auto dayPos = 32;
    auto monPos = 40;
    auto yearPos = 55;

    // extract time stamp
    auto timeStamp = encData.substr(hourPos, 2) + ":" + encData.substr(minPos, 2) + ":" +
                     encData.substr(secPos, 2) + "-" +encData.substr(dayPos, 2) + "." +
                     encData.substr(monPos, 2) + "." + encData.substr(yearPos, 4);

    timeStamp.erase(std::remove(timeStamp.begin(), timeStamp.end(), ' '), timeStamp.end());
    setTimeStamp(timeStamp);

    // delete time from encData
    encData.erase(yearPos, 4);
    encData.erase(monPos, 2);
    encData.erase(dayPos, 2);
    encData.erase(hourPos, 2);
    encData.erase(minPos, 2);
    encData.erase(secPos, 2);

    return encData;
}
