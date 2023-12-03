#include <iostream>
#include <algorithm>
#include <consoleprinter.hpp>
#include "commandscontroller.hpp"

namespace bulk_defs {

namespace {
    static const std::string FINISH_COMMAND {"EOF"};
    static const std::string START_BLOCK_COMMAND {"{"};
    static const std::string END_BLOCK_COMMAND {"}"};
}

CommandsController::CommandsController(std::size_t blockCommandsLimit):
    m_blockCommandsLimit {blockCommandsLimit}
{
    m_printers.push_back(std::make_unique<hw_io::ConsolePrinter>());
}

void CommandsController::addCommand(std::string &&strCommand)
{
    if (m_finished)
        return;

    if ((strCommand != START_BLOCK_COMMAND) && (strCommand != END_BLOCK_COMMAND)) {
        if (strCommand == FINISH_COMMAND) {
            m_finished = true;
            if (m_blockDept == 0)
                printBuket();
            return;
        }

        if (m_currentBulk)
            m_currentBulk->push(std::move(strCommand));
        else
            m_currentBulk = std::make_unique<Bulk>(std::move(strCommand));

        if (m_blockDept > 0)
            return;

        if (m_currentBulk->commands().size() == m_blockCommandsLimit)
            printBuket();

        return;
    }

    if (strCommand == START_BLOCK_COMMAND) {
        if (std::exchange(m_blockDept, m_blockDept + 1) == 0)
            printBuket();
    } else {
        m_finished = (std::exchange(m_blockDept, m_blockDept - 1) == 0);
        if (m_finished)
            return;

        if (m_blockDept == 0)
            printBuket();
    }
}

bool CommandsController::isFinished() const noexcept
{
    return m_finished;
}

namespace {
    std::string bulkToString(std::unique_ptr<Bulk> bulk)
    {
        auto &&commands = bulk->commands();
        if (commands.size() > 0) {
            std::string res {"bulk: " + commands.front()};

            if (commands.size() > 1) {
                std::for_each(std::next(commands.cbegin()), commands.cend(),
                [&res](const auto &str)
                {
                    res.append(", " + str);
                });

                return res;
            }
        }

        return {};
    }
}

void CommandsController::printBuket()
{
    if (m_currentBulk) {
        const std::string str {bulkToString(std::exchange(m_currentBulk, {}))};
        for (auto &&printer : m_printers)
            printer->print(str);
    }
}

}
