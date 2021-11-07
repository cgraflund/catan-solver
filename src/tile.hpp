#pragma once
#include <map>

#include "resource.hpp"

const std::map<int, float> token_probability = {
    {0, 0.f},
    {2, 1/36.f},
    {3, 2/36.f},
    {4, 3/36.f},
    {5, 4/36.f},
    {6, 5/36.f},
    {8, 5/36.f},
    {9, 4/36.f},
    {10, 3/36.f},
    {11, 2/36.f},
    {12, 1/36.f},
};

struct Tile {
    Resource resource;
    int token;
    int row, col;

    Tile(Resource r, int t):resource(r), token(t) {};
};  