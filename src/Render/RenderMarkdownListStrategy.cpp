#include "Render/RenderMarkdownListStrategy.h"
#include <sstream>

void RenderMarkdownListStrategy::add(std::ostringstream& oss, const std::string& item) {
    oss << " - " << item << "\n";
}
