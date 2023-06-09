#pragma once
#include <string>


/**

@class Record
@brief Represents a data record with various attributes.
*/
class Record {
    std::string id_;
    std::string category_;
    std::string name_;
    std::string login_;
    std::string password_;
public:
    /**
    * @brief Constructs a new Record object with the given attributes.
    * @param id The unique identifier of the record.
    * @param category The category of the record.
    * @param name The name associated with the record.
    * @param login The login information for the record.
    * @param password The password for the record.
    */
    Record(std::string const& id, std::string const& category, std::string const& name, std::string const& login, std::string const& password);
    /**
     * @brief Default constructor for the Record class.
     */
    Record() = default;

    /**
     * @brief Destructor for the Record class.
     */
    ~Record();

    // getters and setters

    /**
     * @brief Retrieves the unique identifier of the record.
     * @return The unique identifier of the record.
     */
    auto getId() -> int;

    /**
     * @brief Sets the unique identifier of the record.
     * @param id The unique identifier of the record.
     */
    auto setId(std::string const& id) -> void;

    /**
     * @brief Sets the password for the record.
     * @param newPassword The new password for the record.
     */
    auto setPassword(std::string const& newPassword) -> void;

    /**
     * @brief Retrieves the name associated with the record.
     * @return The name associated with the record.
     */
    auto getName() -> std::string;

    /**
     * @brief Retrieves the category of the record.
     * @return The category of the record.
     */
    auto getCategory() -> std::string;

    // other functions

    /**
     * @brief Extracts data from a record represented as a string.
     * @param line The string representing the record.
     * @return A pointer to the extracted Record object.
     */
    static auto extractDataFromRecord(std::string const& line) -> Record*;

    /**
     * @brief Builds a string representation of the record's data.
     * @return The string representation of the record's data.
     */
    auto buildRecordFromData() -> std::string;

    /**
     * @brief Prints all the records.
     */
    static auto printAllRecords() -> void;
};
