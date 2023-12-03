#pragma once

#include <string>

namespace hw_io {

/// @brief Интерфейс вывода данных
struct IPrinter
{
    virtual ~IPrinter() = default;
    virtual void print(const std::string &) = 0;
};

}
