#pragma once

#include <optional>

#include <QString>

#include "Errors.h"

namespace Binance
{
    class ErrorConverter
    {
    public:
        inline static QString toString(ErrorCode code);
        inline static std::optional<ErrorCode> toErrorCode(const QString &code);
    };
} // namespace Binance
