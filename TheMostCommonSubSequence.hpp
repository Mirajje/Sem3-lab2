#ifndef THE_MOST_COMMON_SUB_SEQUENCE_HPP
#define THE_MOST_COMMON_SUB_SEQUENCE_HPP

#include "IMap.hpp"

IMap<std::string, std::vector<int>>* TheMostCommonSubSequence(const std::string& str, int l, int r)
{
    auto map = new IMap<std::string, std::vector<int>>;

    for (int i = 0; i < str.size(); i++)
        for (int j = l; j < r + 1; j++)
        {
            if (i + j <= str.size())
            {
                std::string ss = str.substr(i, j);
                (*map)[ss].push_back(i);
            }
        }

    return map;
}

#endif
