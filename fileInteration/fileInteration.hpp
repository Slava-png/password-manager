#pragma once
#include <string>
#include <vector>

/**
 * @brief Create a new file.
 *
 * This function creates a new file with a unique name in the specified directory path.
 *
 * @param existingFiles A vector of existing file names in the directory.
 * @param dirPath The path of the directory where the new file should be created.
 * @return The name of the newly created file as a string.
 */
auto createNewFile(std::vector<std::string> const& existingFiles, std::string const& dirPath) -> std::string;

/**
 * @brief Choose a file.
 *
 * This function allows the user to choose a file for further operations.
 */
auto chooseFile() -> void;

/**
 * @brief Perform login.
 *
 * This function performs the login operation.
 */
auto login() -> void;

/**
 * @brief Get the file path.
 *
 * This function returns the path of the currently selected file.
 *
 * @return The file path as a string.
 */
auto getFilePath() -> std::string;

/**
 * @brief Get the file password.
 *
 * This function prompts the user to enter the password for the selected file.
 *
 * @return The entered password as a string.
 */
auto getFilePassword() -> std::string;

/**
 * @brief Get data.
 *
 * This function retrieves the data from the selected file.
 *
 * @return The data from the file as a string.
 */
auto getData() -> std::string;

/**
 * @brief Set the timestamp.
 *
 * This function sets the timestamp for the selected file.
 *
 * @param stamp The timestamp to be set.
 */
auto setTimeStamp(std::string const& stamp) -> void;