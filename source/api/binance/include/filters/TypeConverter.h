#pragma once

#include <optional>

#include <QString>

#include "filters/Filters.h"

namespace Binance::Filters
{
    QString toString(FilterType type);
    std::optional<FilterType> toFilterType(const QString &type);
} // namespace Binance
