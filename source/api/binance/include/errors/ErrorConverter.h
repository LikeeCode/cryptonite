#pragma once

#include <optional>

#include <QString>

#include "Errors.h"

namespace Binance::Error
{
    QString toString(Code code);
    std::optional<Code> toErrorCode(const QString &code);
} // namespace Binance::Error
