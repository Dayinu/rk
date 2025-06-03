// ===========================================================================
// ConceptualExample.cpp // Strategy Pattern
// ===========================================================================

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <iostream>  // Заменено <print> на <iostream>

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

           
