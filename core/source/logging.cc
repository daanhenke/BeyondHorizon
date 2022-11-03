#include "logging/ILogManager.hh"
#include "globals.hh"

namespace horizon
{
    LogManager gLogManager;

    LogManager::LogManager() {}

    Logger LogManager::CreateLogger(const char* label)
    {
        return Logger(this, label);
    }

    void LogManager::InstallHook(LogHook hook)
    {
        m_hooks.push_back(hook);
    }

    void LogManager::HandleLogEntry(LogEntry* entry)
    {
        for (auto& item : m_hooks)
        {
            item(entry);
        }
    }

    LogEntry::~LogEntry()
    {
        m_mgr->HandleLogEntry(this);
    }
}
