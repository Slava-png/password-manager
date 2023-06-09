#pragma once
#include <string>

/**
 * @brief Decrypt data.
 *
 * This function decrypts the encrypted data using the provided password.
 *
 * @param password The password used for decryption.
 * @param encData The data to be decrypted.
 * @return The decrypted data as a string.
 */
auto decrypt(std::string const& password, std::string encData) -> std::string;

/**
 * @brief Encrypt data.
 *
 * This function encrypts the data using the provided password.
 *
 * @param password The password used for encryption.
 * @param data The data to be encrypted.
 * @return The encrypted data as a string.
 */
auto encrypt(std::string const& password, std::string data) -> std::string;

/**
 * @brief Parse records.
 *
 * This function parses the data and extracts individual records.
 *
 * @param data The data to be parsed.
 */
auto parseRecords(std::string const& data) -> void;

/**
 * @brief Extract timestamp from data.
 *
 * This function extracts the timestamp from the encrypted data.
 *
 * @param encData The encrypted data.
 * @return The extracted timestamp as a string.
 */
auto extractTimeStamp(std::string encData) -> std::string;

/**
 * @brief Insert a new timestamp in data.
 *
 * This function inserts a new timestamp into the encrypted data.
 *
 * @param encData The encrypted data.
 * @return The modified data with the new timestamp as a string.
 */
auto insertNewTimeStamp(std::string encData) -> std::string;
