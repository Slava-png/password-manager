cmake_minimum_required(VERSION 3.24)
project(password_manager)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         a33701196adfad74917046096bf5a2aa0ab0bb50
)
FetchContent_MakeAvailable(fmt)

add_executable(password_manager main/main.cpp record/record.cpp passwordCommands/passwordCommands.cpp encryptDecrypt/encryptDecrypt.cpp readWrite/readWriteToFile.cpp readWrite/readWriteToFile.cpp readWrite/readWriteToFile.hpp fileInteration/fileInteraction.cpp fileInteration/fileInteraction.cpp fileInteration/fileInteration.hpp)
target_link_libraries(password_manager fmt)