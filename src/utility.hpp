#pragma once
#include <map>

#include "resource.hpp"

struct Utility {
    Utility(int wood, int brick, int sheep, int wheat, int stone) {
        utility[Resource::wood] = wood;
        utility[Resource::brick] = brick;
        utility[Resource::sheep] = sheep;
        utility[Resource::wheat] = wheat;
        utility[Resource::stone] = stone;
        utility[Resource::desert] = 0;
    };
    std::map<Resource, int> utility;

    int getUtility(Resource r) {
        return utility[r];
    }

};