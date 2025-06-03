// ===========================================================================
// RealWorldExample.cpp // Strategy Pattern
// ===========================================================================

#include <memory>
#include <iostream>  // Заменяем <print> на <iostream>
#include <string>
#include <vector>

namespace StrategyRealWorldExample {

    // =======================================================================

    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void draw() const = 0;
    };

    // =======================================================================

    class Circle;
    class Rectangle;

    class DrawCircleStrategy
    {
    public:
        virtual ~DrawCircleStrategy() = default;
        virtual void draw(const Circle&) const = 0;
    };

    class DrawRectangleStrategy
    {
    public:
        virtual ~DrawRectangleStrategy() = default;
        virtual void draw(const Rectangle&) const = 0;
    };

    // ===========================================================================

    class Circle : public Shape
    {
    public:
        explicit Circle(double radius, std::unique_ptr<DrawCircleStrategy> drawer)
            : m_radius{ radius }, m_drawer{ std::move(drawer) }
        {
        }

        void setDrawCircleStrategy(std::unique_ptr<DrawCircleStrategy> drawer)
        {
            m_drawer = std::move(drawer);
        }

        void draw() const override
        {
            m_drawer->draw(*this);
        }

        double radius() const { return m_radius; }

    private:
        std::unique_ptr<DrawCircleStrategy> m_drawer;
        double m_radius;
    };

    class Rectangle : public Shape
    {
    public:
        explicit Rectangle(double width, double height, std::unique_ptr<DrawRectangleStrategy> drawer)
            : m_width{ width }, m_height{ height }, m_drawer{ std::move(drawer) }
        {
        }

        void setDrawRectangleStrategy(std::unique_ptr<DrawRectangleStrategy> strategy)
        {
            m_drawer = std::move(strategy);
        }

        void draw() const override
        {
            m_drawer->draw(*this);
        }

        double width() const { return m_width; }
        double height() const { return m_height; }

    private:
        std::unique_ptr<DrawRectangleStrategy> m_drawer;
        double m_width;
        double m_height;
    };

    // ===========================================================================

    class Win32CircleStrategy : public DrawCircleStrategy
    {
    public:
        void draw(const Circle& circle) const override {
            std::cout << "Drawing a Circle (radius=" 
                      << circle.radius() 
                      << ") using Win32 API\n";
        }
    };

    class Win32RectangleStrategy : public DrawRectangleStrategy
    {
    public:
        void draw(const Rectangle& rectangle) const override {
            std::cout << "Drawing a Rectangle (" 
                      << rectangle.width() << "x" << rectangle.height() 
                      << ") using Win32 API\n";
        }
    };

    // ===========================================================================

    static void clientCode(const std::vector<std::unique_ptr<Shape>>& shapes)
    {
        for (const auto& shape : shapes)
        {
            shape->draw();
        }
    }
}

void test_realworld_example()
{
    using namespace StrategyRealWorldExample;
    using Shapes = std::vector<std::unique_ptr<Shape>>;

    Shapes shapes;

    // Создаем фигуры напрямую с стратегиями
    shapes.push_back(std::make_unique<Circle>(
        3.0, 
        std::make_unique<Win32CircleStrategy>())
    );

    shapes.push_back(std::make_unique<Rectangle>(
        4.0, 5.0,
        std::make_unique<Win32RectangleStrategy>())
    );

    shapes.push_back(std::make_unique<Circle>(
        6.0,
        std::make_unique<Win32CircleStrategy>())
    );

    clientCode(shapes);
}

// ===========================================================================
// End-of-File
// ===========================================================================
