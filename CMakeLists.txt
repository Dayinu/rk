cmake_minimum_required(VERSION 3.14)
project(StrategyPattern)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Статическая библиотека
add_library(StrategyPatternLib STATIC
    src/library/CreditCard.cpp
    src/library/Order.cpp
    src/library/PayByCreditCard.cpp
    src/library/PayByPayPal.cpp
    src/library/RenderHtmlListStrategy.cpp
    src/library/RenderMarkdownListStrategy.cpp
    src/library/RenderTextProcessor.cpp
)

target_include_directories(StrategyPatternLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Основная программа
add_executable(StrategyPatternProgram
    src/main/Program.cpp
    src/examples/ConceptualExample.cpp
    src/examples/ConceptualExampleModern.cpp
    src/examples/RealWorldExample.cpp
    src/examples/RealWorldExampleModern.cpp
    src/examples/ECommerceApp.cpp
    src/examples/StaticStrategyExample.cpp
)

target_include_directories(StrategyPatternProgram PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(StrategyPatternProgram StrategyPatternLib)

# Тесты
enable_testing()
add_executable(StrategyPatternTests
    tests/test_CreditCard.cpp
    tests/test_Order.cpp
    tests/test_PayByCreditCard.cpp
    tests/test_PayByPayPal.cpp
    tests/test_RenderHtmlListStrategy.cpp
    tests/test_RenderMarkdownListStrategy.cpp
    tests/test_RenderTextProcessor.cpp
)

target_link_libraries(StrategyPatternTests StrategyPatternLib)

add_test(NAME StrategyPatternTests COMMAND StrategyPatternTests)
