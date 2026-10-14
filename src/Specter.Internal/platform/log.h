// Specter.Internal — logging.
//
// The log module has one tiny interface (info/error) and two adapters behind
// it:
//   - host pipe : a FIFO on the Linux side, reached through Wine's Z: drive
//                 (default Z:\tmp\specter.pipe == /tmp/specter.pipe). No file
//                 is written inside the game prefix.
//   - file      : Il2CppInspector's il2cppi_log_write helper (fallback).
//
// init() picks the pipe when it is available, otherwise the file.

#pragma once

namespace specter {
namespace log {

// Select the sink. Call once, before the first info()/error().
void init();

// printf-style. A newline is appended by the sink itself.
void info(const char* fmt, ...);
void error(const char* fmt, ...);

}  // namespace log
}  // namespace specter
