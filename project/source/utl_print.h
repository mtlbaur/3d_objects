#pragma once

#include <iostream>

namespace D3::Utl {
    template <typename T>
    void write(std::ostream& out, const T& t) { out << t; }

    template <typename... A>
    void write(std::ostream& out, const A&... a) { (write(out, a), ...); }

    template <typename... A>
    void writeln(std::ostream& out, const A&... a) { write(out, a..., '\n'); }

    template <typename... A>
    void print(const A&... a) { write(std::cout, a...); }

    template <typename... A>
    void println(const A&... a) { write(std::cout, a..., '\n'); }
} // namespace D3::Utl