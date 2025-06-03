#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <memory>

// Payment Components
#include "Payment/CreditCard.h"
#include "Payment/Order.h"
#include "Payment/PayByCreditCard.h"
#include "Payment/PayByPayPal.h"

// Render Components
// #include "Render/RenderHtmlListStrategy.h"  // Removed problematic include
#include "Render/RenderMarkdownListStrategy.h"
// #include "Render/RenderTextProcessor.h"      // Removed problematic include


// Тест для CreditCard
TEST(PaymentTests, CreditCard) {
    CreditCard card("1234-5678-9012-3456", "12/25", "123");
    card.setValid(true);
    
    EXPECT_TRUE(card.isValid());
    EXPECT_TRUE(card.charge(1000));
    EXPECT_FALSE(card.charge(5000));  // Превышение лимита
}

// Тест для Order
TEST(PaymentTests, Order) {
    Order order;
    order.addToTotalCost(500);
    order.addToTotalCost(300);
    
    EXPECT_EQ(order.getTotalCost(), 800);
    EXPECT_FALSE(order.isClosed());
    
    order.setClosed();
    EXPECT_TRUE(order.isClosed());
}

// Тест для PayByCreditCard
TEST(PaymentTests, PayByCreditCard) {
    PayByCreditCard payment;
    
    // Имитируем ввод данных
    std::istringstream input("1234567890123456\n12/25\n123\n");
    std::cin.rdbuf(input.rdbuf());
    payment.collectPaymentDetails();
    
    EXPECT_TRUE(payment.pay(2000));
    EXPECT_FALSE(payment.pay(10000));  // Превышение лимита
}

// Тест для PayByPayPal
TEST(PaymentTests, PayByPayPal) {
    PayByPayPal payment;
    
    // Имитируем ввод данных
    std::istringstream input("hans@web.de\nsecret\n");
    std::cin.rdbuf(input.rdbuf());
    payment.collectPaymentDetails();
    
    EXPECT_TRUE(payment.pay(1500));
}

// Тест для RenderMarkdownListStrategy
TEST(RenderTests, MarkdownListStrategy) {
    RenderMarkdownListStrategy strategy;
    std::ostringstream oss;
    
    strategy.add(oss, "Apple");
    strategy.add(oss, "Banana");
    
    std::string expected = " * Apple\n * Banana\n";
    EXPECT_EQ(oss.str(), expected);
}

// Тест для ConcreteStrategyA
TEST(StrategyTests, ConceptualStrategyA) {
    using namespace StrategyConceptualExample;
    ConcreteStrategyA strategy;
    std::vector<std::string> data = {"E", "A", "C", "B", "D"};
    
    std::string result = strategy.doAlgorithm(data);
    EXPECT_EQ(result, "ABCDE");
}

// Тест для ConcreteStrategyB
TEST(StrategyTests, ConceptualStrategyB) {
    using namespace StrategyConceptualExample;
    ConcreteStrategyB strategy;
    std::vector<std::string> data = {"A", "E", "C", "B", "D"};
    
    std::string result = strategy.doAlgorithm(data);
    EXPECT_EQ(result, "EDCBA");
}

// Тест для Win32CircleStrategy
TEST(StrategyTests, Win32CircleStrategy) {
    using namespace StrategyRealWorldExample;
    Win32CircleStrategy strategy;
    Circle circle(5.0, nullptr);
    
    testing::internal::CaptureStdout();
    strategy.draw(circle);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Drawing a Circle") != std::string::npos);
}

// Тест для Static Strategy
TEST(StrategyTests, StaticStrategy) {
    using namespace StaticStrategyPatternExample;
    TextProcessorEx<MarkdownListStrategyEx> processor;
    
    processor.append_list({"One", "Two", "Three"});
    std::string result = processor.str();
    
    std::string expected = " - One\n - Two\n - Three\n";
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
