cmake_minimum_required(VERSION 3.15)
project(StrategyPattern)

# Требуем поддержку C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройка структуры каталогов
set(INCLUDE_DIR include)
set(PAYMENT_DIR ${INCLUDE_DIR}/Payment)
set(RENDER_DIR ${INCLUDE_DIR}/Render)
set(STRATEGY_DIR ${INCLUDE_DIR}/Strategy)

set(SRC_DIR src)
set(PAYMENT_SRC_DIR ${SRC_DIR}/Payment)
set(RENDER_SRC_DIR ${SRC_DIR}/Render)
set(STRATEGY_SRC_DIR ${SRC_DIR}/Strategy)

# Основная библиотека
add_library(StrategyPatternLib STATIC
    ${PAYMENT_SRC_DIR}/CreditCard.cpp
    ${PAYMENT_SRC_DIR}/Order.cpp
    ${PAYMENT_SRC_DIR}/PayByCreditCard.cpp
    ${PAYMENT_SRC_DIR}/PayByPayPal.cpp
    ${RENDER_SRC_DIR}/RenderHtmlListStrategy.cpp
    ${RENDER_SRC_DIR}/RenderMarkdownListStrategy.cpp
    ${RENDER_SRC_DIR}/RenderTextProcessor.cpp
    ${STRATEGY_SRC_DIR}/ConceptualExample.cpp
    ${STRATEGY_SRC_DIR}/ConceptualExampleModern.cpp
    ${STRATEGY_SRC_DIR}/RealWorldExample.cpp
    ${STRATEGY_SRC_DIR}/RealWorldExampleModern.cpp
    ${STRATEGY_SRC_DIR}/StaticStrategyExample.cpp
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
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(StrategyPatternTests tests.cpp)
target_link_libraries(StrategyPatternTests 
    PRIVATE 
    StrategyPatternLib 
    GTest::gtest_main
)

# Добавление тестов в CTest
gtest_discover_tests(StrategyPatternTests)

# Для Windows
if(MSVC)
    target_compile_definitions(StrategyPatternLib PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(StrategyPatternApp PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(StrategyPatternTests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
