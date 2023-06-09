#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "fmt/ranges.h"

#include "../encryptDecrypt/encryptDecrypt.hpp"
#include "../readWrite/readWriteToFile.hpp"
#include "fileInteration.hpp"
#include "../passwordCommands/passwordCommands.hpp"

auto password = std::string();
auto data = std::string();
auto timeStamp = std::string();
auto filePath = std::string();

auto getFilePath() -> std::string {
    return filePath;
}

auto getFilePassword() -> std::string {
    return password;
}

auto getData() -> std::string {
    return data;
}

auto setTimeStamp(std::string const& stamp) -> void {
    timeStamp = stamp;
}

auto createNewFile(std::vector<std::string> const& existingFiles, std::string const& dirPath) -> std::string {
    auto line = "_ID_|_______CATEGORY_______|_________NAME_________|_________LOGIN________|_________PASSWORD_________\nCategory ";
    auto newFile = std::string();
    fmt::print("Write name of file:");
    std::cin >> newFile;

    // check if this file already exists
    auto result = std::ranges::find(existingFiles, newFile);
    if (result == existingFiles.end()) {
        // create new file
        auto file = std::ofstream(dirPath + "/" + newFile + ".txt");

        auto filePassword = std::string();
        fmt::print("Provide password for this file:");
        std::cin >> filePassword;

        // write initial default data to it
        writeDataToFile(dirPath + "/" + newFile + ".txt", encrypt(filePassword, line));
        return newFile;
    } else {
        fmt::print("====Such file already exists\n");
        chooseFile();
    }
}

auto chooseFile() -> void {
    auto dirPath = std::string("files");
    using namespace std::filesystem;
    if (not exists(dirPath) && not is_directory(dirPath)) {
        create_directory(dirPath);
    }

    // convert file path to name of file
    auto convertEntryToStr = [](auto const& entry) -> std::string {
        auto strEntry = std::string{std::filesystem::path{entry}.string()};
        strEntry.replace(0, strEntry.find("\\") + 1, "");
        strEntry.replace(strEntry.find("."), 4, "");
        return strEntry;
    };

    // iterate through all files
    auto filesVec = std::vector<std::string> {};
    auto dirIter = std::filesystem::directory_iterator(dirPath);
    for (auto const& entry : dirIter){
        filesVec.push_back(convertEntryToStr(entry));
    }

    if (filesVec.empty()) {
        fmt::print("You don't any files created, create new one at first\n");
        filesVec.push_back(createNewFile(filesVec, dirPath));
    }
    fmt::print("Existing files:\n");
    std::ranges::for_each(filesVec, [](std::string const& file) {fmt::print("  {}\n", file);});

    auto action = std::string();
    fmt::print("Create new file or choose existing one: [n/e]:");
    std::cin >> action;

    if (action == "n") {
        // add new file to existing ones
        filesVec.push_back(createNewFile(filesVec, dirPath));
        fmt::print("Existing files:\n");
        std::ranges::for_each(filesVec, [](std::string const& file) {fmt::print("  {}\n", file);});
        action = "e";
    }
    if (action == "e") {
        fmt::print("Choose file:");
        auto chosenFile = std::string();
        std::cin >> chosenFile;

        // check if user provided valid name
        if (std::ranges::find(filesVec, chosenFile) == filesVec.end()) {
            fmt::print("====Such file doesn't exist");
            chooseFile();
        }
        filePath = dirPath + "/" + chosenFile + ".txt";
        login();
    } else {
        fmt::print("Incorrect input\n");
        chooseFile();
    }
}

auto login() -> void {
    fmt::print("Write your password:");
    std::cin >> password;
    data = decrypt(password, readDataFromFile(getFilePath()));
    fmt::print("Last time when file was opened (time stamp): {}\n", timeStamp);
    fmt::print("==============BEGIN==============\n{}===============END===============\n", data);
    showCommands();
}