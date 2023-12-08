#pragma once
#include <iostream>
#include <cstdio>
#include <cstdarg>

class ColorUtils
{
public:
    static void OutputColoredMessage(const char* color, const char* format, va_list args)
    {
        printf("\033[%sm", color);
        vprintf(format, args);
        printf("\n\033[0m");
    }
};

