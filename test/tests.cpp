// tests.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <memory>

// Концептуальные примеры
#include "ConceptualExample.cpp"
#include "ConceptualExampleModern.cpp"

// Пример электронной коммерции
#include "CreditCard.h"
#include "PayByCreditCard.h"
#include "PayByPayPal.h"
#include "Order.h"

// Примеры рендеринга
#include "RenderListStrategy.h"
#include "RenderHtmlListStrategy.h"
#include "RenderMarkdownListStrategy.h"
#include "RenderTextProcessor.h"

using namespace StrategyConceptualExample;
using namespace StrategyConceptualExampleModern;

// Тесты для концептуального примера (традиционная реализация)
TEST(ConceptualExampleTest, ConcreteStrategyA) {
    ConcreteStrategyA strategy;
    std::vector<std::string> data = {"D", "B", "A", "C"};
    std::string result = strategy.doAlgorithm(data);
    ASSERT_EQ("ABCD", result);
}

TEST(ConceptualExampleTest, ConcreteStrategyB) {
    ConcreteStrategyB strategy;
    std::vector<std::string> data = {"D", "B", "A", "C"};
    std::string result = strategy.doAlgorithm(data);
    ASSERT_EQ("DCBA", result);
}

TEST(ConceptualExampleTest, ContextSwitching) {
    Context context(std::make_unique<ConcreteStrategyA>());
    context.doSomeBusinessLogic();  // Normal Sorting
    
    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();  // Reverse Sorting
}

// Тесты для современной реализации
TEST(ConceptualExampleModernTest, AlgorithmA) {
    std::vector<std::string> data = {"D", "B", "A", "C"};
    std::string result = doAlgorithmA(data);
    ASSERT_EQ("ABCD", result);
}

TEST(ConceptualExampleModernTest, AlgorithmB) {
    std::vector<std::string> data = {"D", "B", "A", "C"};
    std::string result = doAlgorithmB(data);
    ASSERT_EQ("DCBA", result);
}

// Тесты для платежных стратегий
TEST(PaymentTest, CreditCardCharge) {
    CreditCard card("12345678", "12/25", "123");
    card.setValid(true);
    
    ASSERT_TRUE(card.charge(1000));
    ASSERT_FALSE(card.charge(5000)); // Превышение лимита
}

TEST(PaymentTest, PayByCreditCardFlow) {
    PayByCreditCard payment;
    // Тест сбора данных (имитация ввода)
    testing::internal::CaptureStdout();
    payment.collectPaymentDetails();
    std::string output = testing::internal::GetCapturedStdout();
    
    ASSERT_TRUE(output.find("Enter the card number") != std::string::npos);
}

TEST(PaymentTest, OrderProcessing) {
    Order order;
    order.addToTotalCost(1500);
    ASSERT_EQ(1500, order.getTotalCost());
    
    auto strategy = std::make_shared<PayByPayPal>();
    order.processOrder(strategy);
    order.setClosed();
    ASSERT_TRUE(order.isClosed());
}

// Тесты для стратегий рендеринга
class MockHtmlStrategy : public RenderListStrategy {
public:
    void start(std::ostringstream& oss) override { oss << "<mock>"; }
    void add(std::ostringstream& oss, const std::string& item) override { oss << item; }
    void end(std::ostringstream& oss) override { oss << "</mock>"; }
};

TEST(RenderingTest, HtmlStrategy) {
    RenderHtmlListStrategy strategy;
    std::ostringstream oss;
    
    strategy.start(oss);
    strategy.add(oss, "Test");
    strategy.end(oss);
    
    ASSERT_TRUE(oss.str().find("<ul>") != std::string::npos);
    ASSERT_TRUE(oss.str().find("<li>Test</li>") != std::string::npos);
}

TEST(RenderingTest, MarkdownStrategy) {
    RenderMarkdownListStrategy strategy;
    std::ostringstream oss;
    
    strategy.add(oss, "Test");
    ASSERT_EQ(oss.str(), " - Test\n");
}

TEST(RenderingTest, TextProcessor) {
    RenderTextProcessor processor;
    processor.setOutputFormat(std::make_unique<MockHtmlStrategy>());
    
    std::vector<std::string> items = {"A", "B", "C"};
    processor.appendList(items);
    
    std::string result = processor.toString();
    ASSERT_EQ(result, "<mock>ABC</mock>");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
