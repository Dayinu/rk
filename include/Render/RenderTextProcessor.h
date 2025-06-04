// ===========================================================================
// RenderTextProcessor.h
// ===========================================================================
#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>

class RenderListStrategy; // Предварительное объявление

class RenderTextProcessor
{
public:
    RenderTextProcessor(); 
    // Объявляем специальные функции
    ~RenderTextProcessor(); // Деструктор
    RenderTextProcessor(RenderTextProcessor&&) noexcept; // Перемещающий конструктор
    RenderTextProcessor& operator=(RenderTextProcessor&&) noexcept; // Перемещающее присваивание

    void setOutputFormat(std::unique_ptr<RenderListStrategy>&&);
    void appendList(const std::vector<std::string>&);
    std::string toString() const;
    void clear();

private:
    std::ostringstream m_oss;
    std::unique_ptr<RenderListStrategy> m_format;
};
