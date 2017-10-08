#ifndef AUTOSNAKE_H
#define AUTOSNAKE_H

#include <deque>
#include <deque>
#include "SnakeMap.h"

class AutoSnake final
{
public:
    typedef SnakeMap::Location Location;
    typedef SnakeMap::Direction Direction;

public:
    AutoSnake(int countRows = 10, int countColumns = 10);
    ~AutoSnake();
    const SnakeMap &GetMap() const { return mMap; }
    void ChangeCountRowsAndColumns(int countRows, int countColumns);
    void Timeout() { timeout(); } 
    void timeout();
    const Location &GetFoodLocation() const { return mMap.GetFoodLocation(); }
    const Location &GetHeadLocation() const { return mMap.GetSnakeQueue().front(); }
    const Location &GetTailLocation() const { return mMap.GetSnakeQueue().back(); }
    inline bool IsFailed() const { return mFailed; }
    void Replay();
    Direction GetRandomDirection() const;
    const SnakeMap &GetHelpMap() const { return mHelpMap; }

private:
    Direction GetGoodDirection();
    Direction GetQuickFoodDirection() const;
    Direction GetGoodFoodDirection();
    Direction GetFarestFoodDirection() const;
    Direction GetValidRandomDirection() const;
    Location GetRandomLocation() const;
    void GenerateFood();
    bool IsFoodReachable() const;
    bool MoveForward();
    inline void SetFail() { mFailed = true; }
    static bool IsHeadAndTailReachable(SnakeMap &map);
    static int GetDistanceBetweenHeadAndFood(const SnakeMap &map);

    SnakeMap mMap;
    bool mFailed;
    std::deque<Direction> mGoodFoodDirectionList;

    SnakeMap mHelpMap;

private:
    class Impl;
    Impl *impl;
};

#endif
