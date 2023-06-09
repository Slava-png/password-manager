#include <string>
#include <fstream>
#include "../encryptDecrypt/encryptDecrypt.hpp"

auto readDataFromFile(std::string const& fileName) -> std::string {
    auto file = std::ifstream(fileName, std::ios::binary | std::ios::in);
    auto encData = std::string();
    auto line = std::string();

    while (std::getline(file, line)) {
        encData += line;
    }
    return extractTimeStamp(encData);
}

auto writeDataToFile(std::string const& fileName, std::string const& encData) -> void {
    auto file = std::fstream(fileName, std::ios::out);
    file << insertNewTimeStamp(encData);
}
