// Specter.Internal — logging.
//
// A thin adapter over Il2CppInspector's generated `il2cppi_log_write` helper,
// so the rest of the code never depends on the SDK helper directly.

#pragma once

namespace specter {
namespace log {

void info(const char* message);
void error(const char* message);

}  // namespace log
}  // namespace specter
