// Specter.Internal — implementation of logging (host pipe + file fallback).

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "helpers.h"  // il2cppi_log_write (fallback file sink)
#include "log.h"

#include <string>
#include <cstdarg>
#include <cstdio>
#include <cstddef>

namespace specter {
namespace log {

namespace {

// Under Wine/Proton the Z: drive maps to the Linux root, so this path is
// /tmp/specter.pipe on the host. Override with the SPECTER_PIPE env var.
const wchar_t* kDefaultPipe = L"Z:\\tmp\\specter.pipe";

HANDLE g_pipe = INVALID_HANDLE_VALUE;
CRITICAL_SECTION g_lock;
bool g_lock_ready = false;

std::wstring pipe_path()
{
    wchar_t buf[512];
    DWORD n = GetEnvironmentVariableW(L"SPECTER_PIPE", buf, 512);
    if (n > 0 && n < 512) {
        return std::wstring(buf, n);
    }
    return std::wstring(kDefaultPipe);
}

// Write raw bytes to the host pipe. If the pipe is gone, fall back to the file
// sink for good (g_pipe becomes INVALID_HANDLE_VALUE).
void write_all(const char* data, std::size_t len)
{
    if (g_pipe == INVALID_HANDLE_VALUE) {
        il2cppi_log_write(std::string(data, len));
        return;
    }

    std::size_t offset = 0;
    while (offset < len) {
        DWORD written = 0;
        if (!WriteFile(g_pipe, data + offset, static_cast<DWORD>(len - offset),
                       &written, NULL) || written == 0) {
            CloseHandle(g_pipe);
            g_pipe = INVALID_HANDLE_VALUE;
            il2cppi_log_write(std::string(data + offset, len - offset));
            return;
        }
        offset += written;
    }
}

void emit(const char* level, const char* message)
{
    std::string text = std::string("[specter]") + level + " " + message;

    if (g_lock_ready) EnterCriticalSection(&g_lock);
    if (g_pipe != INVALID_HANDLE_VALUE) {
        text.push_back('\n');  // host is Linux: LF only
        write_all(text.data(), text.size());
    } else {
        write_all(text.data(), text.size());  // il2cppi_log_write adds CRLF
    }
    if (g_lock_ready) LeaveCriticalSection(&g_lock);
}

// Format a printf-style message into a fixed buffer (truncating if needed).
void format_into(char* out, std::size_t cap, const char* fmt, va_list ap)
{
    out[0] = '\0';
    if (cap < 2) return;
    int n = vsnprintf(out, cap, fmt, ap);
    if (n < 0) out[0] = '\0';
}

}  // namespace

void init()
{
    // Idempotent: the entry point initialises logging *before* spawning the
    // worker, so that a spawn failure is visible on the pipe. specter::start()
    // calls it again on the worker as a no-op.
    if (g_lock_ready) {
        return;
    }

    InitializeCriticalSection(&g_lock);
    g_lock_ready = true;

    std::wstring path = pipe_path();
    g_pipe = CreateFileW(path.c_str(),
                         GENERIC_READ | GENERIC_WRITE,
                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                         NULL, OPEN_EXISTING, 0, NULL);

    if (g_pipe == INVALID_HANDLE_VALUE) {
        il2cppi_log_write("[specter] host pipe unavailable, using file log");
    }
}

void info(const char* fmt, ...)
{
    char buf[2048];
    va_list ap;
    va_start(ap, fmt);
    format_into(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    emit("", buf);
}

void error(const char* fmt, ...)
{
    char buf[2048];
    va_list ap;
    va_start(ap, fmt);
    format_into(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    emit("[error]", buf);
}

}  // namespace log
}  // namespace specter
