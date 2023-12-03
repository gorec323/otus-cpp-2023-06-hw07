#pragma once

#include <memory>
#include <deque>
#include <iprinter.hpp>
#include "bulk.hpp"

namespace bulk_defs {

class CommandsController
{
public:
    CommandsController(std::size_t blockCommandsLimit);
    ~CommandsController() = default;

    void addCommand(std::string &&strCommand);

    bool isFinished() const noexcept;

private:
    void printBuket();
    const std::size_t m_blockCommandsLimit;
    bool m_finished {false};
    int m_blockDept{0};
    std::unique_ptr<Bulk> m_currentBulk;
    std::vector<std::unique_ptr<hw_io::IPrinter>> m_printers;
};

}
