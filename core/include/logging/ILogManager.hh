#pragma once

#include <vector>
#include <sstream>

namespace horizon
{
    enum class LogLevel
    {
        Critical,
        Error,
        Warning,
        Info,
        Debug,
        Trace
    };

    class LogManager;

    class LogEntry
    {
    private:
        LogManager* m_mgr;

    public:
        std::stringstream m_stream;
        const char* m_label;
        LogLevel m_level;

        LogEntry(LogManager* mgr, LogLevel level, const char* label) : m_mgr(mgr), m_level(level), m_label(label) {}
        ~LogEntry();
    };

    template <typename T>
    LogEntry& operator<<(LogEntry& entry, T&& value)
    {
        entry.m_stream << std::forward<T>(value);
        return entry;
    }

    template <typename T>
    LogEntry& operator<<(LogEntry&& entry, T&& value)
    {
        return entry << std::forward<T>(value);
    }

    class Logger
    {
    private:
        const char* m_label;
        LogManager* m_mgr;

        template<LogLevel level>
        inline LogEntry Raw()
        {
            return LogEntry(m_mgr, level, m_label);
        }

    public:
        Logger(LogManager* mgr, const char* label) : m_mgr(mgr), m_label(label) {}

        inline LogEntry Critical() { return Raw<LogLevel::Critical>(); }
        inline LogEntry Error() { return Raw<LogLevel::Error>(); }
        inline LogEntry Warning() { return Raw<LogLevel::Warning>(); }
        inline LogEntry Info() { return Raw<LogLevel::Info>(); }
        inline LogEntry Debug() { return Raw<LogLevel::Debug>(); }
        inline LogEntry Trace() { return Raw<LogLevel::Trace>(); }
    };

    typedef void (*LogHook)(LogEntry* entry);
    class LogManager
    {
    public:
        LogManager();

        Logger CreateLogger(const char* label);
        void InstallHook(LogHook hook);
        void HandleLogEntry(LogEntry* entry);

    private:
        std::vector<LogHook> m_hooks;
    };
}
