// ===========================================================================
// RenderListStrategy.h
// ===========================================================================

#pragma once

#include <sstream> // Добавлено
#include <string>  // Добавлено

class RenderListStrategy
{
public:
    virtual ~RenderListStrategy() = default;

    virtual void start(std::ostringstream&) {};
    virtual void add(std::ostringstream&, const std::string& item) {};
    virtual void end(std::ostringstream&) {};
};

// ===========================================================================
// End-of-File
// ===========================================================================
