// ===========================================================================
// PayByCreditCard.h
// ===========================================================================

/**
 * Concrete strategy. Implements credit card payment method.
 */
#pragma once

#include "PaymentStrategy.h"  // Базовый класс
#include <memory>             // Для std::unique_ptr

// Forward declaration вместо #include "CreditCard.h"
class CreditCard;

class PayByCreditCard : public PaymentStrategy {
private:
    std::unique_ptr<CreditCard> m_card;

public:
    PayByCreditCard();
    ~PayByCreditCard() {}

    virtual bool pay(int paymentAmount) override;
    virtual void collectPaymentDetails() override;

private:
    bool cardIsPresent();
};

// ===========================================================================
// End-of-File
// ===========================================================================
