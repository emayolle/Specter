// Specter.Internal — implementation of logging.

#include "pch-il2cpp.h"

#include "helpers.h"  // il2cppi_log_write (generated framework)
#include "log.h"

#include <string>

namespace specter {
namespace log {

void info(const char* message)
{
    il2cppi_log_write(std::string("[specter] ") + message);
}

void error(const char* message)
{
    il2cppi_log_write(std::string("[specter][error] ") + message);
}

}  // namespace log
}  // namespace specter
