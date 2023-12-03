#pragma once

#include "iprinter.hpp"

namespace hw_io {

class ConsolePrinter : public IPrinter
{
public:
    void print(const std::string &data) override final;
};

}