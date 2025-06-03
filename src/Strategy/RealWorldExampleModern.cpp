// ===========================================================================
// RealWorldExampleModern.cpp // Strategy Pattern
// ===========================================================================

#include <functional>
#include <memory>
#include <iostream>  // Заменяем <print> на <iostream>
#include <string>
#include <vector>

namespace StrategyRealWorldExampleModern {

    // =======================================================================

    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void draw() const = 0;
    };

    // ===========================================================================

    class Circle : public Shape
    {
    public:
        using DrawStrategy = std::function<void(const Circle&)>;

        explicit Circle(double radius, DrawStrategy drawer)
            : m_radius{ radius }, m_drawer{ std::move(drawer) }
        {
        }

        void setDrawStrategy(DrawStrategy drawer) {
            m_drawer = std::move(drawer);
        }

        void draw() const override {
            m_drawer(*this);
        }

        double radius() const { return m_radius; }

    private:
        DrawStrategy m_drawer;
        double m_radius;
    };

    class Rectangle : public Shape
    {
    public:
        using DrawStrategy = std::function<void(const Rectangle&)>;

        explicit Rectangle(double width, double height, DrawStrategy drawer)
            : m_width{ width }, m_height{ height }, m_drawer{ std::move(drawer) }
        {
        }

        void setDrawStrategy(DrawStrategy strategy) {
            m_drawer = std::move(strategy);
        }

        void draw() const override {
            m_drawer(*this);
        }

        double width() const { return m_width; }
        double height() const { return m_height; }

    private:
        DrawStrategy m_drawer;
        double m_width;
        double m_height;
    };

    // ===========================================================================

    class Win32CircleStrategy
    {
    public:
        void operator()(const Circle& circle) const {
            std::cout << "Drawing a Circle (radius=" 
                      << circle.radius() 
                      << ") using Win32 API\n"; // Используем std::cout
        }
    };

    class Win32RectangleStrategy
    {
    public:
        void operator()(const Rectangle& rectangle) const {
            std::cout << "Drawing a Rectangle (" 
                      << rectangle.width() << "x" << rectangle.height() 
                      << ") using Win32 API\n"; // Исправлено название фреймворка
        }
    };

    // ===========================================================================

    static void clientCode(const std::vector<std::unique_ptr<Shape>>& shapes) {
        for (const auto& shape : shapes) {
            shape->draw();
        }
    }
}

void test_realworld_example_modern() {
    using namespace StrategyRealWorldExampleModern;
    using Shapes = std::vector<std::unique_ptr<Shape>>;

    Shapes shapes;
    
    // Создаем фигуры с нужными стратегиями
    shapes.push_back(std::make_unique<Circle>(
        3.0, Win32CircleStrategy{})
    );
    
    shapes.push_back(std::make_unique<Rectangle>(
        4.0, 5.0, Win32RectangleStrategy{})
    );
    
    shapes.push_back(std::make_unique<Circle>(
        6.0, Win32CircleStrategy{})
    );

    clientCode(shapes);
}

// ===========================================================================
// End-of-File
// ===========================================================================
