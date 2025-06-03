// ===========================================================================
// ConceptualExample.cpp // Strategy Pattern
// ===========================================================================

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <iostream>  // Используем <iostream> вместо <print>

namespace StrategyConceptualExample {

    class StrategyBase
    {
    public:
        virtual ~StrategyBase() {}

        virtual std::string doAlgorithm(const std::vector<std::string>& data) const = 0;
        virtual std::string getName() const = 0;
    };

    // =======================================================================

    class ConcreteStrategyA : public StrategyBase
    {
    public:
        std::string getName() const override {
            return { "Normal Sorting" };
        }

        std::string doAlgorithm(const std::vector<std::string>& data) const override
        {
            std::string result{};

            std::for_each(
                data.begin(),
                data.end(),
                [&](const std::string& letter) {
                    result += letter;
                }
            );

            std::sort(
                result.begin(),
                result.end()
            );

            return result;
        }
    };

    class ConcreteStrategyB : public StrategyBase
    {
    public:
        std::string getName() const override {
            return { "Reverse Sorting" };
        }

        std::string doAlgorithm(const std::vector<std::string>& data) const override
        {
            std::string result;

            std::for_each(
                data.begin(),
                data.end(),
                [&](const std::string& letter) {
                    result += letter;
                }
            );

            std::sort(
                result.begin(),
                result.end()
            );

            std::reverse(
                result.begin(),
                result.end()
            );

            return result;  // Добавлен возврат результата
        }  // Добавлена закрывающая скобка
    };

    class Context
    {
    private:
        std::unique_ptr<StrategyBase> m_strategy;

    public:
        Context(std::unique_ptr<StrategyBase> strategy)
            : m_strategy{ std::move(strategy) }
        {}

        ~Context() {}

        void setStrategy(std::unique_ptr<StrategyBase> strategy)
        {
            m_strategy = std::move(strategy);
        }

        void doSomeBusinessLogic() const
        {
            std::vector<std::string> someStrings{ "A", "E", "C", "B", "D" };

            std::cout << "Context: Sorting data ..." << std::endl;

            std::string result{ m_strategy->doAlgorithm(someStrings) };

            std::cout << "Result: " << result << std::endl;
        }
    };

    static void clientCode()
    {
        std::cout << "Client: Strategy is set to 'Normal Sorting':" << std::endl;

        Context context{ std::make_unique<ConcreteStrategyA>() };
        context.doSomeBusinessLogic();
        std::cout << std::endl;

        std::cout << "Client: Strategy is set to 'Reverse Sorting':" << std::endl;
        context.setStrategy(std::make_unique<ConcreteStrategyB>());
        context.doSomeBusinessLogic();
    }
}  

void test_conceptual_example()
{
    using namespace StrategyConceptualExample;

    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
