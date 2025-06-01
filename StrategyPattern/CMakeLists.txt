cmake_minimum_required(VERSION 3.20)
project(StrategyPattern)

# Требуем поддержки C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Разные настройки для MSVC и других компиляторов
if(MSVC)
    # Включить экспериментальную поддержка std::print в MSVC
    add_compile_definitions(_HAS_CXX23=1)
    add_compile_options(/Zc:preprocessor /std:c++latest)
else()
    # Для GCC/Clang
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Список всех исходных файлов
set(SOURCES
    ConceptualExample.cpp
    ConceptualExampleModern.cpp
    CreditCard.cpp
    ECommerceApp.cpp
    Order.cpp
    PayByCreditCard.cpp
    PayByPayPal.cpp
    Program.cpp
    RealWorldExample.cpp
    RealWorldExampleModern.cpp
    StaticStrategyExample.cpp
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Для Windows: игнорируем предупреждения о безопасности CRT
if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
        _CRT_SECURE_NO_WARNINGS
        _SCL_SECURE_NO_WARNINGS)
endif()

# Для GCC/Clang: линкуем std::format если требуется
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++exp)
endif()
