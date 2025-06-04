#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>
#include "Payment/CreditCard.h"
#include "Payment/PayByCreditCard.h"
#include "Payment/PayByPayPal.h"
#include "Payment/Order.h"
#include "Render/RenderHtmlListStrategy.h"
#include "Render/RenderMarkdownListStrategy.h"
#include "Render/RenderTextProcessor.h"

// Тест для класса CreditCard
TEST(CreditCardTest, ChargeAndValidation) {
    CreditCard card("1234567890123456", "12/25", "123");
    card.setValid(true);
    EXPECT_TRUE(card.isValid());
    EXPECT_TRUE(card.charge(1000));
    EXPECT_EQ(card.charge(5000), false); // Превышение лимита
}

// Тест для класса PayByCreditCard
TEST(PayByCreditCardTest, PaymentProcess) {
    PayByCreditCard payment;
    testing::internal::CaptureStdout();
    payment.collectPaymentDetails(); // Ввод данных имитируется в тесте
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Enter the card number:") != std::string::npos);
    EXPECT_TRUE(payment.pay(1000)); // Успешная оплата
}

// Тест для класса PayByPayPal
TEST(PayByPayPalTest, PaymentProcess) {
    PayByPayPal payment;
    testing::internal::CaptureStdout();
    payment.collectPaymentDetails(); // Ввод данных имитируется в тесте
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Enter the user's email address:") != std::string::npos);
    EXPECT_TRUE(payment.pay(1000)); // Успешная оплата
}

// Тест для класса Order
TEST(OrderTest, ProcessOrder) {
    Order order;
    auto strategy = std::make_shared<PayByCreditCard>();
    testing::internal::CaptureStdout();
    order.processOrder(strategy);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Enter the card number:") != std::string::npos);
    order.addToTotalCost(1000);
    EXPECT_EQ(order.getTotalCost(), 1000);
}

// Тест для класса RenderHtmlListStrategy
TEST(RenderHtmlListStrategyTest, Formatting) {
    RenderHtmlListStrategy strategy;
    std::ostringstream oss;
    strategy.start(oss);
    strategy.add(oss, "item1");
    strategy.end(oss);
    EXPECT_TRUE(oss.str().find("<ul>") != std::string::npos);
    EXPECT_TRUE(oss.str().find("<li>item1</li>") != std::string::npos);
}

// Тест для класса RenderMarkdownListStrategy
TEST(RenderMarkdownListStrategyTest, Formatting) {
    RenderMarkdownListStrategy strategy;
    std::ostringstream oss;
    strategy.add(oss, "item1");
    EXPECT_TRUE(oss.str().find(" - item1") != std::string::npos);
}

// Тест для класса RenderTextProcessor
TEST(RenderTextProcessorTest, OutputFormatting) {
    RenderTextProcessor processor;
    processor.setOutputFormat(std::make_unique<RenderHtmlListStrategy>());
    processor.appendList({"item1", "item2"});
    std::string result = processor.toString();
    EXPECT_TRUE(result.find("<ul>") != std::string::npos);
    EXPECT_TRUE(result.find("<li>item1</li>") != std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
