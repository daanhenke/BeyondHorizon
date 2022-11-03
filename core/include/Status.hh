#pragma once

#include <cinttypes>


namespace horizon
{
    union Status
    {
        uint32_t AsUInt32;
        __attribute__((packed)) struct
        {
            uint32_t Module: 9;
            uint32_t Description: 13;
            uint32_t Unused: 10;
        };
    };

    namespace status
    {
        namespace mod
        {
            constexpr uint32_t BeyondHorizon = 501;
        }

        namespace code
        {
            constexpr uint32_t Success = 0;
        }

        constexpr Status make(uint32_t module = mod::BeyondHorizon, uint32_t description = code::Success)
        {
            return { .Module = module, .Description = description  };
        }

        inline bool valid(Status status)
        {
            return status.Description == code::Success;
        }

        inline bool invalid(Status status)
        {
            return status.Description != code::Success;
        }
    }
}
