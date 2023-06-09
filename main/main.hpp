#pragma once
#include <string>
#include <vector>
#include "../record/record.hpp"

/**
 * @brief Get the list of categories.
 *
 * This function returns a reference to a vector containing the list of categories.
 *
 * @return A reference to the vector of categories.
 */
auto getCategories() -> std::vector<std::string>&;

/**
 * @brief Add a new category.
 *
 * This function adds a new category to the list of categories.
 *
 * @param category The category to be added.
 */
auto addCategory(std::string const& category) -> void;

/**
 * @brief Empty the categories.
 *
 * This function clears the list of categories, removing all existing categories.
 */
auto emptyCategories() -> void;

/**
 * @brief Add a record.
 *
 * This function adds a Record object to the collection of records.
 *
 * @param ps Pointer to the Record object to be added.
 */
auto addRecord(Record* ps) -> void;

/**
 * @brief Get the list of records.
 *
 * This function returns a vector containing the collection of records.
 *
 * @return A vector of Record pointers.
 */
auto getRecords() -> std::vector<Record*>;

/**
 * @brief Empty the records.
 *
 * This function clears the collection of records, removing all existing records.
 */
auto emptyRecords() -> void;

/**
 * @brief Delete a record.
 *
 * This function deletes a Record object from the collection of records.
 *
 * @param ps Pointer to the Record object to be deleted.
 */
auto deleteRecord(Record* const& ps) -> void;

/**
 * @brief Get the first line.
 *
 * This function returns the first line of data.
 *
 * @return The first line of data as a string.
 */
auto getFirstLine() -> std::string;

/**
 * @brief Set the first line.
 *
 * This function sets the first line of data.
 *
 * @param line The string to set as the first line of data.
 */
auto setFirstLine(std::string const& line) -> void;