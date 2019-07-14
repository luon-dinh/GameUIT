#pragma once

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

void DebugOut(const wchar_t *fmt, ...);
void PrintDebug(const char*);
void PrintDebugNumber(int);