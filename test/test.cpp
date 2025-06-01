// tests/AllTests.cpp
#include "CreditCard.h"
#include "Order.h"
#include "PayByCreditCard.h"
#include "PayByPayPal.h"
#include "RenderHtmlListStrategy.h"
#include "RenderMarkdownListStrategy.h"
#include "RenderTextProcessor.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// Тесты для CreditCard
void testCreditCard() {
    CreditCard card("1234567812345678", "12/24", "123");
    card.setValid(true);
    
    // Проверка валидации
    assert(card.isValid() == true);
    
    // Проверка списания средств
    assert(card.charge(1000) == true);
    assert(card.charge(4000) == true);
    assert(card.charge(1) == false); // Должно быть недостаточно средств
    
    std::cout << "CreditCard tests passed!\n";
}

// Тесты для Order
void testOrder() {
    Order order;
    
    // Проверка начального состояния
    assert(order.getTotalCost() == 0);
    assert(order.isClosed() == false);
    
    // Добавление стоимости
    order.addToTotalCost(100);
    assert(order.getTotalCost() == 100);
    
    order.addToTotalCost(200);
    assert(order.getTotalCost() == 300);
    
    // Закрытие заказа
    order.setClosed();
    assert(order.isClosed() == true);
    
    std::cout << "Order tests passed!\n";
}

// Тесты для PayByCreditCard
void testPayByCreditCard() {
    PayByCreditCard payment;
    
    // Тест сбора данных (симуляция ввода)
    std::istringstream input("1234567812345678\n12/24\n123\n");
    std::cin.rdbuf(input.rdbuf());
    
    payment.collectPaymentDetails();
    assert(payment.pay(1000) == true);
    assert(payment.pay(5000) == false); // Недостаточно средств
    
    std::cout << "PayByCreditCard tests passed!\n";
}

// Тесты для PayByPayPal
void testPayByPayPal() {
    PayByPayPal payment;
    
    // Тест сбора данных (симуляция ввода)
    std::istringstream input("hans@web.de\nsecret\n");
    std::cin.rdbuf(input.rdbuf());
    
    payment.collectPaymentDetails();
    assert(payment.pay(100) == true);
    
    std::cout << "PayByPayPal tests passed!\n";
}

// Тесты для RenderHtmlListStrategy
void testRenderHtmlListStrategy() {
    RenderHtmlListStrategy strategy;
    std::ostringstream oss;
    
    strategy.start(oss);
    strategy.add(oss, "Item1");
    strategy.add(oss, "Item2");
    strategy.end(oss);
    
    std::string expected = "<ul>\n  <li>Item1</li>\n  <li>Item2</li>\n</ul>\n";
    assert(oss.str() == expected);
    
    std::cout << "RenderHtmlListStrategy tests passed!\n";
}

// Тесты для RenderMarkdownListStrategy
void testRenderMarkdownListStrategy() {
    RenderMarkdownListStrategy strategy;
    std::ostringstream oss;
    
    strategy.add(oss, "Item1");
    strategy.add(oss, "Item2");
    
    std::string expected = " * Item1\n * Item2\n";
    assert(oss.str() == expected);
    
    std::cout << "RenderMarkdownListStrategy tests passed!\n";
}

// Тесты для RenderTextProcessor
void testRenderTextProcessor() {
    RenderTextProcessor processor;
    
    // Тест HTML рендеринга
    processor.setOutputFormat(std::make_unique<RenderHtmlListStrategy>());
    processor.appendList({"Apple", "Banana"});
    std::string htmlResult = processor.toString();
    std::string htmlExpected = "<ul>\n  <li>Apple</li>\n  <li>Banana</li>\n</ul>\n";
    assert(htmlResult == htmlExpected);
    
    // Тест Markdown рендеринга
    processor.clear();
    processor.setOutputFormat(std::make_unique<RenderMarkdownListStrategy>());
    processor.appendList({"Orange", "Grape"});
    std::string mdResult = processor.toString();
    std::string mdExpected = " * Orange\n * Grape\n";
    assert(mdResult == mdExpected);
    
    std::cout << "RenderTextProcessor tests passed!\n";
}

int main() {
    testCreditCard();
    testOrder();
    testPayByCreditCard();
    testPayByPayPal();
    testRenderHtmlListStrategy();
    testRenderMarkdownListStrategy();
    testRenderTextProcessor();
    
    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
