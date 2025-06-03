// ===========================================================================
// RenderMarkdownListStrategy.h
// ===========================================================================

#pragma once

#include "RenderListStrategy.h"  // Include base class declaration
#include <sstream>               // For std::ostringstream
#include <string>                // For std::string

class RenderMarkdownListStrategy : public RenderListStrategy
{
public:
    void add(std::ostringstream& oss, const std::string& item) override;
};

// ===========================================================================
// End-of-File
// ===========================================================================
