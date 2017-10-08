#pragma once
#ifndef GAMAP_H
#define GAMAP_H

#include <vector>
#include <deque>

namespace GA
{   
    class Map
    {
    public:
        enum class Dot 
        {
            ROAD, START, END, WALL,
        };

        struct Location
        {
            int row;
            int column;
        };
        
        enum Direction
        {
            LEFT, DOWN, RIGHT, UP,
        };

    public:
        Map(int width, int height);
        ~Map();
        Map(const Map &rhs) = default;
        Map &operator = (const Map &map) = default; 
        Dot &At(const Location &location) { return mMap[location.row][location.column]; }
        std::deque<Location> &Queue() { return mPath; }
        Location &GetStartLocation() { return mStartLocation; }
        Location &GetEndLocation() { return mEndLocation; }
        

    private:
        Location mStartLocation;
        Location mEndLocation;
        std::vector<std::vector<Dot> > mMap;
        std::deque<Location> mPath; // saved path, first is start location
    };
}


#endif // GAMAP_H