#include <gtest/gtest.h>
#include "Payment/CreditCard.h"
#include "Payment/PayByCreditCard.h"
#include "Payment/PayByPayPal.h"
#include "Payment/Order.h"
#include "Render/RenderListStrategy.h"
#include "Render/RenderHtmlListStrategy.h"
#include "Render/RenderMarkdownListStrategy.h"
#include "Render/RenderTextProcessor.h"

// Тесты для CreditCard
TEST(CreditCardTest, ChargeAndValidation) {
    CreditCard card("1234567890123456", "12/24", "123");
    card.setValid(true);
    
    EXPECT_TRUE(card.isValid());
    EXPECT_TRUE(card.charge(1000));
    EXPECT_FALSE(card.charge(5000)); // Превышение лимита
}

// Тесты для Order
TEST(OrderTest, OrderManagement) {
    Order order;
    
    order.addToTotalCost(500);
    EXPECT_EQ(order.getTotalCost(), 500);
    
    order.addToTotalCost(300);
    EXPECT_EQ(order.getTotalCost(), 800);
    
    EXPECT_FALSE(order.isClosed());
    order.setClosed();
    EXPECT_TRUE(order.isClosed());
}

// Тесты для PayByCreditCard
TEST(PayByCreditCardTest, PaymentProcess) {
    PayByCreditCard payment;
    
    // Тестовый ввод данных карты
    std::istringstream input("1234567890123456\n12/24\n123\n");
    std::cin.rdbuf(input.rdbuf());
    
    payment.collectPaymentDetails();
    EXPECT_TRUE(payment.pay(2000));
    EXPECT_FALSE(payment.pay(4000)); // Недостаточно средств
}

// Тесты для PayByPayPal
TEST(PayByPayPalTest, AuthenticationAndPayment) {
    PayByPayPal payment;
    
    // Тестовый ввод данных
    std::istringstream input("hans@web.de\nsecret\n");
    std::cin.rdbuf(input.rdbuf());
    
    payment.collectPaymentDetails();
    EXPECT_TRUE(payment.pay(1500));
}

// Тесты для RenderMarkdownListStrategy
TEST(MarkdownRendererTest, Formatting) {
    RenderMarkdownListStrategy strategy;
    std::ostringstream oss;
    
    strategy.add(oss, "First item");
    strategy.add(oss, "Second item");
    
    // Изменено: ожидаем звездочки вместо дефисов
    EXPECT_EQ(oss.str(), " * First item\n * Second item\n");
}

// Тесты для RenderHtmlListStrategy
TEST(HtmlRendererTest, Formatting) {
    RenderHtmlListStrategy strategy;
    std::ostringstream oss;
    
    strategy.start(oss);
    strategy.add(oss, "Item 1");
    strategy.add(oss, "Item 2");
    strategy.end(oss);
    
    // Изменено: используем 2 пробела вместо табуляции
    std::string expected = "<ul>\n  <li>Item 1</li>\n  <li>Item 2</li>\n</ul>\n";
    EXPECT_EQ(oss.str(), expected);
}

// Тесты для RenderTextProcessor
TEST(TextProcessorTest, DynamicRendering) {
    RenderTextProcessor processor;
    
    // HTML-рендеринг
    processor.setOutputFormat(std::make_unique<RenderHtmlListStrategy>());
    processor.appendList({"Apple", "Banana"});
    std::string htmlResult = processor.toString();
    
    EXPECT_TRUE(htmlResult.find("<ul>") != std::string::npos);
    EXPECT_TRUE(htmlResult.find("<li>Apple</li>") != std::string::npos);
    
    processor.clear();
    
    // Markdown-рендеринг
    processor.setOutputFormat(std::make_unique<RenderMarkdownListStrategy>());
    processor.appendList({"Orange", "Grape"});
    std::string mdResult = processor.toString();
    
    // Изменено: ожидаем звездочки
    EXPECT_TRUE(mdResult.find(" * Orange") != std::string::npos);
    EXPECT_TRUE(mdResult.find(" * Grape") != std::string::npos);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
