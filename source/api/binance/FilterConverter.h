#pragma once

#include <QString>

#include "Filters.h"

namespace Api::Binance
{
    class FilterConverter
    {
    public:
        // FilterType
        inline static QString filterTypeToString(FilterType type);
        inline static FilterType stringToFilterType(const QString& typeStr);
    };
} // namespace Api::Binance
