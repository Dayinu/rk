cmake_minimum_required(VERSION 3.15)
project(StrategyPattern)

# Требуем поддержку C++23 (для std::println)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включить поддержку модулей (если используется)
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

# Создаем статическую библиотеку
add_library(StrategyPatternLib STATIC
    # Payment компоненты
    ${PAYMENT_SRC_DIR}/CreditCard.cpp
    ${PAYMENT_SRC_DIR}/Order.cpp
    ${PAYMENT_SRC_DIR}/PayByCreditCard.cpp
    ${PAYMENT_SRC_DIR}/PayByPayPal.cpp
    
    # Render компоненты
    ${RENDER_SRC_DIR}/RenderHtmlListStrategy.cpp
    ${RENDER_SRC_DIR}/RenderMarkdownListStrategy.cpp
    ${RENDER_SRC_DIR}/RenderTextProcessor.cpp
    
    # Strategy примеры
    ${STRATEGY_SRC_DIR}/ConceptualExample.cpp
    ${STRATEGY_SRC_DIR}/ConceptualExampleModern.cpp
    ${STRATEGY_SRC_DIR}/RealWorldExample.cpp
    ${STRATEGY_SRC_DIR}/RealWorldExampleModern.cpp
    ${STRATEGY_SRC_DIR}/StaticStrategyExample.cpp
)

# Указываем пути для заголовочных файлов
target_include_directories(StrategyPatternLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PAYMENT_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${RENDER_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${STRATEGY_DIR}
)

# Создаем исполняемый файл
add_executable(StrategyPatternApp
    ${SRC_DIR}/ECommerceApp.cpp
    ${SRC_DIR}/Program.cpp
)

# Связываем исполняемый файл с библиотекой
target_link_libraries(StrategyPatternApp PRIVATE StrategyPatternLib)

# Устанавливаем пути для заголовков исполняемого файла
target_include_directories(StrategyPatternApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}
)

# Для Windows: отключаем предупреждения CRT
if(MSVC)
    target_compile_definitions(StrategyPatternLib PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(StrategyPatternApp PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
