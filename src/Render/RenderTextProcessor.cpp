#include "Render/RenderTextProcessor.h"

void RenderTextProcessor::setOutputFormat(std::unique_ptr<RenderListStrategy>&& strategy) {
    m_format = std::move(strategy);
}

void RenderTextProcessor::appendList(const std::vector<std::string>& items) {
    if (m_format) {
        m_format->start(m_oss);
        for (const auto& item : items) {
            m_format->add(m_oss, item);
        }
        m_format->end(m_oss);
    }
}

std::string RenderTextProcessor::toString() const {
    return m_oss.str();
}

void RenderTextProcessor::clear() {
    m_oss.str("");
    m_oss.clear();
}
