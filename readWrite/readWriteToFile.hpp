#pragma once
#include <string>

/**
 * @brief Writes encrypted data to a file.
 *
 * This function writes the provided encrypted data to the specified file.
 *
 * @param fileName The name of the file to write the data to.
 * @param encData The encrypted data to write to the file.
 */
auto writeDataToFile(std::string const& fileName, std::string const& encData) -> void;

/**
 * @brief Reads data from a file.
 *
 * This function reads data from the specified file and returns it as a string.
 *
 * @param fileName The name of the file to read data from.
 * @return The data read from the file as a string.
 */
auto readDataFromFile(std::string const& fileName) -> std::string;


