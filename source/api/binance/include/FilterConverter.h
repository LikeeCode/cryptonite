#pragma once

#include <optional>

#include <QString>

#include "Filters.h"

namespace Binance
{
    class FilterConverter
    {
    public:
        inline static QString toString(FilterType type);
        inline static std::optional<FilterType> toFilterType(const QString &type);
    };
} // namespace Binance
