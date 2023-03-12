#pragma once

#include <iostream>

#define D3_UTL_REQUIRE(condition)                          \
    if (!(condition)) {                                    \
        std::cerr << "[D3] CONDITION FAILED:\n"            \
                  << "- CONDITION: " << #condition << '\n' \
                  << "- FILE:      " << __FILE__ << '\n'   \
                  << "- FUNCTION:  " << __func__ << '\n'   \
                  << "- LINE:      " << __LINE__;          \
        abort();                                           \
    }