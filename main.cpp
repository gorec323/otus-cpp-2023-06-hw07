#include <iostream>
#include <commandscontroller.hpp>
#include "version.h"

using namespace std;

int main(int argc, const char *argv[])
{
    using namespace std;

    cout << "Bulk version: " << PROJECT_VERSION << endl;

    const auto bulkSize = argc;
    if (bulkSize != 2) {
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " [number of commands]" << std::endl;
        return 1;
    }

    std::size_t bulkCommandsLimit = std::atoi(argv[1]);

    std::string strCommand;
    bulk_defs::CommandsController cmdProc{bulkCommandsLimit};
    while (!cmdProc.isFinished() && std::cin >> strCommand) {
        cmdProc.addCommand(std::exchange(strCommand, ""));
    }
    
    return 0;
}
