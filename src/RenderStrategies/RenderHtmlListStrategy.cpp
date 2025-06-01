#include "RenderHtmlListStrategy.h"
#include <sstream>

void RenderHtmlListStrategy::start(std::ostringstream& oss) {
    oss << "<ul>\n";
}

void RenderHtmlListStrategy::end(std::ostringstream& oss) {
    oss << "</ul>\n";
}

void RenderHtmlListStrategy::add(std::ostringstream& oss, const std::string& item) {
    oss << "  <li>" << item << "</li>\n";
}
