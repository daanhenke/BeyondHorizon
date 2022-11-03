#pragma once

namespace horizon
{
    class IFileSystem
    {
    public:
        virtual void OpenFile() = 0;
    };
}
