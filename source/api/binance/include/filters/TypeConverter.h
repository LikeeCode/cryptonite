#pragma once

#include <optional>

#include <QString>

#include "filters/Filters.h"

namespace Binance::Filter
{
    QString toString(Type type);
    std::optional<Type> toFilterType(const QString &type);
} // namespace Binance::Filter
