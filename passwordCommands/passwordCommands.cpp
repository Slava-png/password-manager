#include "fmt/ranges.h"
#include <fmt/core.h>
#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "../main/main.hpp"
#include "../encryptDecrypt/encryptDecrypt.hpp"
#include "passwordCommands.hpp"
#include "../readWrite/readWriteToFile.hpp"
#include "../fileInteration/fileInteration.hpp"

/**
 * @brief Allow the user to create a password.
 * This function prompts the user to enter a password and returns it as a string.
 * @return The user-entered password as a string.
 */
auto letUserCreatePassword() -> std::string;

/**
 * @brief Generate a password.
 * This function generates a random password and returns it as a string.
 * @return The generated password as a string.
 */
auto generatePassword() -> std::string;

/**
 * @brief Create a password.
 * This function creates a password and returns it as a string.
 * @return The created password as a string.
 */
auto createPassword() -> std::string;

/**
 * @brief Get the last ID.
 * This function retrieves the last ID used for password records.
 * @return The last ID as an integer.
 */
auto getLastId() -> int;

/**
 * @brief Delete passwords explicitly.
 * This function deletes the passwords associated with the given list of IDs.
 * @param ids A vector of password IDs to be deleted.
 */
auto deletePasswordsExplicitly(std::vector<int> ids) -> void;

/**
 * @brief Reset IDs after deletion.
 * This function resets the IDs of password records after deleting passwords.
 */
auto resetIdsAfterDeletion() -> void;

/**
 * @brief Perform decryption for the first command.
 * This function performs decryption for the first command.
 */
auto firstCommandDecryption() -> void;

auto anyCommandPerformed = false;

auto showCommands() -> void {
    fmt::print("List of commands:\n");
    fmt::print("  Login -> lg\n");
    fmt::print("  Change file -> cf\n");
    fmt::print("  Add password -> ap\n");
    fmt::print("  Edit password -> ep\n");
    fmt::print("  Delete password(s) -> dp\n");
    fmt::print("  Search password -> sp\n");
    fmt::print("  Add category -> ac\n");
    fmt::print("  Delete category -> dc\n");
    fmt::print("  Print sorted records -> sr\n");
    fmt::print("  Show records -> show\n");
    fmt::print("  Exit -> ex\n");
    auto command = std::string();

    fmt::print("Write command which you want to perform:");
    std::cin >> command;
    auto fileName = getFilePath();

    if (command == "lg") {
        login();
    } else if (command == "cf") {
        chooseFile();
    } else if (command == "ap") {
        addPassword();
    } else if (command == "ac") {
        addNewCategory(false);
    } else if (command == "dc") {
        deleteCategory();
    } else if (command == "sr") {
        sortRecords();
    } else if (command == "ep") {
        editPassword();
    } else if (command == "sp") {
        searchPassword();
    } else if (command == "show") {
        firstCommandDecryption();
        Record::printAllRecords();
        showCommands();
    } else if (command == "dp") {
        deletePassword();
    } else if (command == "ex") {
        exit();
    } else {
        fmt::print("====Incorrect input. Try again\n");
        showCommands();
    }
}

auto firstCommandDecryption() -> void {
    if (not anyCommandPerformed) {
        parseRecords(getData());
    }
    anyCommandPerformed = true;
}

// add password
auto addPassword() -> void {
    firstCommandDecryption();

    auto id = std::to_string(getLastId() + 1);
    auto name = std::string();
    auto login = std::string();
    auto category = std::string();

    if (getCategories().empty()) {
        fmt::print("You don't have any categories. Create new category at first place\n");
        addNewCategory(true);
    }

    fmt::print("List of existing categories:\n");
    std::ranges::for_each(getCategories(), [](std::string const& category) -> void {
        fmt::print("  {}\n", category);
    });

    fmt::print("Write category(obligatory):");
    std::cin >> category;
    if (std::ranges::find(getCategories(), category) == getCategories().end()) {
        fmt::print("====Incorrect input, category: {}, doesn't exist. Try again\n", category);
        showCommands();
    }

    fmt::print("Write name(obligatory):");
    std::cin >> name;
    fmt::print("Write login (if you want to skip write _skip):");
    std::cin >> login;

    if (login == "_skip") {
        login = "";
    }
    auto password = createPassword();

    addRecord(new Record(id, category, name, login, password));
    showCommands();
}

auto createPassword() -> std::string {
    auto type = std::string();

    // check if user wants to create its own password or auto-generated
    fmt::print("Types of password:\n");
    fmt::print("Provide your own password -> own\n");
    fmt::print("Auto generated password -> auto\n");
    fmt::print("Which type:");
    std::cin >> type;

    // check user password
    if (type == "own") {
        return letUserCreatePassword();
    } else if (type == "auto") {
        return generatePassword();
    } else {
        fmt::print("====Incorrect input, choose type again\n");
    }
    createPassword();
}

auto letUserCreatePassword() -> std::string {
    auto password = std::string();

    fmt::print("Write your password:");
    std::cin >> password;

    // check password length
    auto validLength = true;
    if (password.size() >= 10) {
        fmt::print("--Length >= 10: Ok\n");
    } else {
        fmt::print("--Length >= 10: Not Ok\n");
        validLength = false;
    }

    // check if upperCase letter is present
    auto upperCaseSymbol = false;
    for (auto symbol: password) {
        if (std::isupper(symbol)) {
            upperCaseSymbol = true;
            break;
        }
    }

    // check if punctuation symbol is present
    auto punctSymbol = false;
    for (auto symbol: password) {
        if (std::ispunct(symbol)) {
            punctSymbol = true;
            break;
        }
    }

    if (upperCaseSymbol) fmt::print("--Upper case symbol: Ok\n");
    else fmt::print("--Upper case symbol: Not Ok\n");

    if (punctSymbol) fmt::print("--Punctuation symbol: Ok");
    else fmt::print("--Punctuation symbol: Not Ok\n");

    // provide user with password status
    if (punctSymbol && upperCaseSymbol && validLength) {
        fmt::print("Password status: Good\n");
    } else if (punctSymbol && upperCaseSymbol || punctSymbol && validLength || upperCaseSymbol && validLength) {
        fmt::print("Password status: Low\n");
    } else {
        fmt::print("Password status: Very Low\n");
    }

    // check if user wants to change password
    auto changePassword = char();
    fmt::print("Do you want to change password (y/n):");
    std::cin >> changePassword;

    if (changePassword == 'n') {
        return password;
    }
    letUserCreatePassword();
}

auto generatePassword() -> std::string {
    auto password = std::string();
    auto len = 26;
    auto upperCase = std::string();
    auto lowerCase = std::string();
    auto punctSymbol = std::string();

    // get user preferences regarding password

    while (true) {

        fmt::print("Provide length of password (max 26):");
        std::cin >> len;
        fmt::print("Use lowercase letters [y/n]:");
        std::cin >> lowerCase;
        fmt::print("Use uppercase letters [y/n]:");
        std::cin >> upperCase;
        fmt::print("Use punctuation symbols [y/n]:");
        std::cin >> punctSymbol;


        //std::cout << std::setw(44) << "\nUse punctuation symbols [y/n]: ";
        if (len >= 0 && len <= 26 && (lowerCase == "y" || lowerCase == "n") &&
              (upperCase == "y" || upperCase == "n") && (punctSymbol == "y" || punctSymbol == "n")) {
            break;
        } else {
            fmt::print("====Incorrectly specified parameters for password. Try again\n");
        }
    }

    // create symbols for password
    auto symbols = std::string("1234567890");
    if (lowerCase == "y") {
        symbols += "qwertyuiopasdfghjklzxcvbnm";
    } if (upperCase == "y") {
        symbols += "QWERTYUIOPASDFGHJKLZXCVBNM";
    } if (punctSymbol == "y") {
        symbols += "!@#$%^&*()_+-=[];'.,<>?:{}";
    }

    // set random
    auto rd = std::random_device();
    auto rng = std::mt19937(rd());
    auto dist = std::uniform_int_distribution<int>(0, symbols.size() - 1);
    // create password
    for (int i = 0; i < len; i++) {
        int randomNum = dist(rng);
        password += symbols.at(randomNum);
    }

    return password;
}

auto getLastId() -> int {
    int maxId = 0;
    for (auto const& record: getRecords()) {
        if (maxId < record->getId()) {
            maxId = record->getId();
        }
    }
    return maxId;
}

// categories
auto addNewCategory(bool forPasswordAddition) -> void {
    firstCommandDecryption();

    // print all categories
    if (not forPasswordAddition && not getCategories().empty()){
        fmt::print("Existing categories:\n");
        std::ranges::for_each(getCategories(), [](std::string const& category) -> void {
            fmt::print("  {}\n", category);
        });
    }

    auto newCategory = std::string();
    fmt::print("Write new category:");
    std::cin >> newCategory;

    // check if provided category already exists
    if (std::ranges::find(getCategories(), newCategory) != getCategories().end() && not getCategories().empty()) {
        fmt::print("====Such category already exists\n");
        showCommands();
    }

    fmt::print("Category {} was added\n", newCategory);
    addCategory(newCategory);

    if (not forPasswordAddition){
        showCommands();
    }
}

auto deleteCategory() -> void {
    firstCommandDecryption();

    // check if any categories exist
    if (getCategories().empty()) {
        fmt::print("====You have 0 categories existing\n");
        showCommands();
    }
    fmt::print("Existing categories:\n");
    std::ranges::for_each(getCategories(), [](std::string const& category) -> void {
        fmt::print("  {}\n", category);
    });

    auto remCategory = std::string();
    fmt::print("Category for deletion:");
    std::cin >> remCategory;

    // check if provided category exist
    if (std::ranges::find(getCategories(), remCategory) == getCategories().end()) {
        fmt::print("====Such category doesn't exist\n");
        showCommands();
    }

    fmt::print("Category {} was deleted\n", remCategory);
    getCategories().erase(std::remove(getCategories().begin(),getCategories().end(),
                                      remCategory), getCategories().end());
    showCommands();
}

// exit
auto exit() -> void {
    auto data = std::string("_ID_|_______CATEGORY_______|_________NAME_________|_________LOGIN________|_________PASSWORD_________\n");

    // collect all records in a string for being written to a file
    for (auto const& record: getRecords()) {
        data += record->buildRecordFromData();
    }

    // check if any commands were performed, if no than user provided wrong password
    if (anyCommandPerformed) {
        writeDataToFile(getFilePath(), encrypt(getFilePassword(), data));
    } else {
        writeDataToFile(getFilePath(), readDataFromFile(getFilePath()));
    }
    // clear global variables
    getCategories().clear();
    emptyRecords();
    anyCommandPerformed = false;
    chooseFile();
}

auto editPassword() -> void {
    firstCommandDecryption();

    fmt::print("List of records:\n");
    Record::printAllRecords();

    // get id of password which user wants to delete
    auto id = int();
    fmt::print("Choose id of password which you want to edit:");
    std::cin >> id;

    if (id > getLastId() || id <= 0) {
        fmt::print("====Invalid input. Such index doesn't exist\n");
        showCommands();
    }

    // get new password
    auto newPassword = std::string();
    fmt::print("Enter new password for record with id {}:", id);
    std::cin >> newPassword;

    // find the right record and change password
    std::ranges::for_each(getRecords(), [id, newPassword](Record* record) -> void {
        if (record->getId() == id) record->setPassword(newPassword);
    });

    fmt::print("Password was changed\n");
    showCommands();
}

auto deletePassword() -> void {
    firstCommandDecryption();
    Record::printAllRecords();

    if (getRecords().empty()) {
        fmt::print("You don't have any records to delete\n");
        showCommands();
    }

    auto strIds = std::string();
    auto vec = std::vector<int> {};

    std::cin.ignore();
    fmt::print("Write id of passwords for deletion(write them separated by space): ");
    std::getline(std::cin, strIds);

    // parse string of ids to vector<int> of ids
    auto id = std::string();
    for (auto const& el: strIds) {
        if (el == ' ') {
            vec.push_back(std::stoi(id));
            id = "";
        } else {
            id += el;
        }
    }
    if (not id.empty()) {
        vec.push_back(std::stoi(id));
    }

    deletePasswordsExplicitly(vec);
    resetIdsAfterDeletion();
    showCommands();
}

auto deletePasswordsExplicitly(std::vector<int> ids) -> void {
    for (auto const& record: getRecords()) {
        // check if such password exists in list of records
        if (std::ranges::find(ids, record->getId()) != ids.end()) {
            // let user confirm deletion
            auto confirmation = std::string();
            fmt::print("Are you sure you want to delete the record with id: {} and name: {}, [y/n]:", record->getId(), record->getName());
            std::cin >> confirmation;

            if (confirmation == "y") {
                fmt::print("Record was removed\n");
                deleteRecord(record);
            } else if (confirmation == "n") {
                fmt::print("Deletion canceled\n");
                continue;
            } else {
                fmt::print("====Invalid input. Deletion canceled\n");
            }
        }
    }
}

auto resetIdsAfterDeletion() -> void {
    firstCommandDecryption();

    auto records = getRecords();

    // sort records in asc order by keeping the initial order
    std::ranges::sort(records, [](Record* const& first, Record* const& second) {
        return first->getId() < second->getId();
    });

    // add to each record new id
    for (int i = 0; i < records.size(); i++) {
        records[i]->setId(std::to_string(i + 1));
    }
}

auto sortRecords() -> void {
    firstCommandDecryption();
    auto order = std::string();
    fmt::print("Choose order of sorting records [asc/desc]:");
    std::cin >> order;
    auto records = getRecords();

    if (order == "asc") {
        std::ranges::sort(records, [](Record* const& first, Record* const& second) {
            // sort on basis of category
            if (first->getCategory() < second->getCategory()) {
                return true;
            } else if (first->getCategory() > second->getCategory()) {
                return false;
            // if categories are equal sort on basis of name
            } else {
                return first->getName() < second->getName();
            }
        });
    } else if (order == "desc") {
        std::ranges::sort(records, [](Record* const& first, Record* const& second) {
            // sort on basis of category
            if (first->getCategory() > second->getCategory()) {
                return true;
            } else if (first->getCategory() < second->getCategory()) {
                return false;
                // if categories are equal sort on basis of name
            } else {
                return first->getName() > second->getName();
            }
        });
    } else {
        fmt::print("Invalid input. Try again\n");
        showCommands();
    }

    // print sorted records
    fmt::print("==============BEGIN==============\n");
    fmt::print("{}\n", getFirstLine());
    std::ranges::for_each(records, [](auto const& record) {fmt::print("{}", record->buildRecordFromData());});
    fmt::print("===============END===============\n");
    showCommands();
}

auto searchPassword() -> void {
    firstCommandDecryption();
    auto parameter = std::string();
    fmt::print("Choose column which will be searched: name, category [n,c]:");
    std::cin >> parameter;
    auto validPasswords = std::vector<Record*> {};

    // function for searching records
    auto searchRecords = [](std::string const& pattern, bool searchByName) -> std::vector<Record*> {
        auto validPasswords = std::vector<Record*> {};
        for (auto const& record: getRecords()) {
            if (searchByName && record->getName().find(pattern) != std::string::npos) {
                validPasswords.push_back(record);
            } else if (not searchByName && record->getCategory().find(pattern) != std::string::npos) {
                validPasswords.push_back(record);
            }
        }
        return validPasswords;
    };

    // choose pattern for searching
    auto pattern = std::string();
    if (parameter == "n") {
        fmt::print("Write a substring of name:");
        std::cin >> pattern;

        validPasswords = searchRecords(pattern, true);
    } else if (parameter == "c") {
        fmt::print("Write a substring of category:");
        std::cin >> pattern;

        validPasswords = searchRecords(pattern, false);
    } else {
        fmt::print("Invalid input. Try again\n");
        showCommands();
    }

    // print records
    fmt::print("==============BEGIN==============\n");
    fmt::print("{}\n", getFirstLine());
    std::ranges::for_each(validPasswords, [](auto const& record) {fmt::print("{}", record->buildRecordFromData());});
    fmt::print("===============END===============\n");
    showCommands();
}
