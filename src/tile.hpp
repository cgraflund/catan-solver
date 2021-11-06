#pragma once
enum Resource {wood, brick, sheep, wheat, stone, desert};

struct Tile {
    Resource resource;
    int token;
    int value;

    Tile(Resource r, int t):resource(r), token(t) {};
};  