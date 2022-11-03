#include "arch/logging.hh"
#include "globals.hh"

#include <android/log.h>

namespace horizon::arch
{
    void AndroidLog(LogEntry* entry)
    {
        __android_log_print(ANDROID_LOG_DEBUG, entry->m_label, "%s", entry->m_stream.str().c_str());
    }

    Status InstallLoggingHooks()
    {
        gLogManager.InstallHook(AndroidLog);
        return status::make();
    }
}
