#pragma once
#include <string>

/**
 * @brief Displays available commands.
 *
 * This function shows the list of available commands to the user.
 */
auto showCommands() -> void;

/**
 * @brief Adds a new password.
 *
 * This function allows the user to add a new password entry.
 */
auto addPassword() -> void;

/**
 * @brief Adds a new category.
 *
 * This function allows the user to add a new category for password addition.
 *
 * @param forPasswordAddition Determines if the category is being added for password addition.
 */
auto addNewCategory(bool forPasswordAddition) -> void;

/**
 * @brief Deletes a category.
 *
 * This function allows the user to delete an existing category.
 */
auto deleteCategory() -> void;

/**
 * @brief Edits a password.
 *
 * This function allows the user to edit an existing password entry.
 */
auto editPassword() -> void;

/**
 * @brief Deletes a password.
 *
 * This function allows the user to delete an existing password entry.
 */
auto deletePassword() -> void;

/**
 * @brief Sorts the records.
 *
 * This function sorts the password records based on a specified criteria.
 */
auto sortRecords() -> void;

/**
 * @brief Searches for a password.
 *
 * This function allows the user to search for a specific password.
 */
auto searchPassword() -> void;

/**
 * @brief Exits the program.
 *
 * This function terminates the program.
 */
auto exit() -> void;
