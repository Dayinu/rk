cmake_minimum_required(VERSION 3.15)
project(StrategyPattern)

# Требуем поддержку C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройка структуры каталогов
set(INCLUDE_DIR include)
set(SRC_DIR src)
set(TEST_DIR test)

# Основная библиотека
add_library(StrategyPatternLib STATIC
    ${SRC_DIR}/Payment/CreditCard.cpp
    ${SRC_DIR}/Payment/Order.cpp
    ${SRC_DIR}/Payment/PayByCreditCard.cpp
    ${SRC_DIR}/Payment/PayByPayPal.cpp
    ${SRC_DIR}/Render/RenderHtmlListStrategy.cpp
    ${SRC_DIR}/Render/RenderMarkdownListStrategy.cpp
    ${SRC_DIR}/Render/RenderTextProcessor.cpp
    ${SRC_DIR}/Strategy/ConceptualExample.cpp
    ${SRC_DIR}/Strategy/ConceptualExampleModern.cpp
    ${SRC_DIR}/Strategy/RealWorldExample.cpp
    ${SRC_DIR}/Strategy/RealWorldExampleModern.cpp
    ${SRC_DIR}/Strategy/StaticStrategyExample.cpp
)

# Пути для заголовков
target_include_directories(StrategyPatternLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}
)

# Основное приложение
add_executable(StrategyPatternApp
    ${SRC_DIR}/ECommerceApp.cpp
    ${SRC_DIR}/Program.cpp
)
target_link_libraries(StrategyPatternApp PRIVATE StrategyPatternLib)

# Тесты
enable_testing()

# Используем FetchContent для управления зависимостями GTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# ВАЖНО: Должно быть ДО FetchContent_MakeAvailable
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ВАЖНО: Подключаем модуль GoogleTest ПОСЛЕ загрузки
include(GoogleTest)

# Создаем тестовый исполняемый файл
add_executable(StrategyPatternTests ${TEST_DIR}/tests.cpp)
target_link_libraries(StrategyPatternTests PRIVATE
    StrategyPatternLib
    GTest::gtest_main
)

gtest_discover_tests(StrategyPatternTests)

# Для Windows
if(MSVC)
    target_compile_definitions(StrategyPatternLib PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(StrategyPatternApp PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(StrategyPatternTests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

install(TARGETS StrategyPatternApp
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Resources/
        DESTINATION share/strategy-pattern/Resources)
