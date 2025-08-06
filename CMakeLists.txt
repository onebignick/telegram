cmake_minimum_required(VERSION 3.10)
project(Telegram CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    json_lib
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)

add_library(telegram_bot_api STATIC
    src/telegram_bot_api/types/user.cpp
    src/telegram_bot_api/types/chat.cpp
)

target_include_directories(telegram_bot_api PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(telegram_bot_api_tests
    tests/main_test.cpp
    tests/types/user_test.cpp
    tests/types/chat_test.cpp
)

target_link_libraries(telegram_bot_api_tests PRIVATE
    GTest::gtest_main
    telegram_bot_api
)

target_include_directories(telegram_bot_api_tests PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME run_telegram_bot_api_tests COMMAND telegram_bot_api_tests)