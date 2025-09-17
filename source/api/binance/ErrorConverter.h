#pragma once

#include <QString>

#include "Errors.h"

namespace Api::Binance
{
    class ErrorConverter
    {
    public:
        // ErrorCode
        inline static QString errorCodeToString(ErrorCode code);
        inline static ErrorCode stringToErrorCode(const QString &code);
    };
} // namespace Binance::Api
