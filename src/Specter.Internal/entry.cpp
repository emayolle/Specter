// Specter.Internal — injected DLL entry point (definition).
//
// This is the thin adapter the generated framework calls into. It owns the two
// symbols the scaffold expects (Run and LOG_FILE) and immediately delegates to
// the specter module. No logic lives here on purpose.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "main.h"
#include "specter.h"

// Log file used by the generated helper `il2cppi_log_write` (see helpers.cpp).
extern const LPCWSTR LOG_FILE = L"specter-log.txt";

void Run()
{
    specter::start();
}
