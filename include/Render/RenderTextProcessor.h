// ===========================================================================
// RenderTextProcessor.h
// ===========================================================================

#include <memory>       // Для std::unique_ptr
#include <sstream>      // Для std::ostringstream
#include <string>       // Для std::string
#include <vector>       // Для std::vector

// Предварительное объявление, чтобы избежать циклических зависимостей
class RenderListStrategy;

class RenderTextProcessor
{
public:
    void setOutputFormat(std::unique_ptr<RenderListStrategy>&&);
    void appendList(const std::vector<std::string>&);
    std::string toString() const;
    void clear();

private:
    std::ostringstream m_oss;
    std::unique_ptr<RenderListStrategy> m_format;
};

// ===========================================================================
// End-of-File
// ===========================================================================
