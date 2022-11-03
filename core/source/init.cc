#include "init.hh"
#include "arch/logging.hh"
#include "globals.hh"

namespace horizon
{
    Status InitHorizonRuntime()
    {
        auto result = arch::InstallLoggingHooks();
        if (status::invalid(result)) return result;

        auto logger = gLogManager.CreateLogger("test");
        logger.Critical() << "Fakka G";
        return status::make();
    }
}
