// ===========================================================================
// ConceptualExampleModern.cpp // Strategy Pattern
// ===========================================================================

#include <algorithm>
#include <functional>
#include <memory>
#include <iostream>  // Заменено <print> на <iostream>
#include <string>
#include <vector>

namespace StrategyConceptualExampleModern {

    using Strategy = std::function<std::string(const std::vector<std::string>&)>;

    static std::string doAlgorithmA(const std::vector<std::string>& data)
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

    static std::string doAlgorithmB(const std::vector<std::string>& data)
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

        std::reverse(
            result.begin(),
            result.end()
        );

        return result;
    }

    class Context
    {
    private:
        Strategy m_strategy;

    public:
        Context(Strategy&& strategy) : m_strategy{ std::move(strategy) } {}
        Context(Strategy& strategy) : m_strategy{ strategy } {}

        ~Context() {}

        void setStrategy(Strategy&& strategy)
        {
            m_strategy = std::move(strategy);
        }

        void setStrategy(Strategy& strategy)
        {
            m_strategy = strategy;
        }

        void doSomeBusinessLogic() const
        {
            std::vector<std::string> someStrings{ "A", "E", "C", "B", "D" };

            // Заменено std::println на std::cout
            std::cout << "Context: Sorting data ..." << std::endl;

            std::string result{ m_strategy(someStrings) };

            // Заменено std::println на std::cout
            std::cout << "Result: " << result << std::endl;
        }
    };

    static void clientCode()
    {
        // Заменено std::println на std::cout
        std::cout << "Client: Strategy is set to 'Normal Sorting':" << std::endl;

        Context context{ doAlgorithmA };
        context.doSomeBusinessLogic();
        std::cout << std::endl;

        // Заменено std::println на std::cout
        std::cout << "Client: Strategy is set to 'Reverse Sorting':" << std::endl;
        context.setStrategy(doAlgorithmB);
        context.doSomeBusinessLogic();
    }
}

void test_conceptual_example_modern()
{
    using namespace StrategyConceptualExampleModern;

    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
