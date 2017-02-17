#include "AutoSnake.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
#include <queue>
#include <vector>
#include "SnakeStepMap.h"

AutoSnake::AutoSnake(int countRows, int countColumns) :
    mMap(countRows, countColumns), mFailed(false)
{
    srand(time(nullptr));
    Replay();
}

AutoSnake::~AutoSnake()
{
}

void AutoSnake::ChangeCountRowsAndColumns(int countRows, int countColumns)
{
    mMap.ChangeCountRowsAndColumns(countRows, countColumns);
}

void AutoSnake::timeout()
{
    MoveForward();
}

void AutoSnake::Replay()
{
    mFailed = false;
    mMap.Clear();
    mGoodFoodDirectionList.clear();
    Location loc = GetRandomLocation();
    mMap.AddSnakeHeadDot(loc);
    GenerateFood();
}

AutoSnake::Direction AutoSnake::GetRandomDirection() const
{
    int num = rand() % 4;
    switch (num)
    {
    case 0:
        return Direction::Left;
        break;
    case 1:
        return Direction::Right;
        break;
    case 2:
        return Direction::Up;
        break;
    case 3:
        return Direction::Down;
        break;
    default:
        break;
    }
}

AutoSnake::Direction AutoSnake::GetQuickFoodDirection() const
{
    assert(false);
    const int INF = INT_MAX / 2;
    int * *step;
    step = new int *[GetMap().GetCountRows()];
    for (int r = 0; r < GetMap().GetCountRows(); r++)
    {
        step[r] = new int[GetMap().GetCountColumns()];
        for (int c = 0; c < GetMap().GetCountColumns(); c++)
        {
            step[r][c] = INF;
        }
    }

    struct Node
    {
        int dist;
        Location location;
    };

    static int dr[] = { -1, 1, 0, 0, };
    static int dc[] = { 0, 0, -1, 1, };

    std::queue<Node> q;
    q.push(Node{ 0, mMap.GetFoodLocation() });
    step[mMap.GetFoodLocation().row][mMap.GetFoodLocation().column] = 0;
    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nr = node.location.row + dr[i];
            int nc = node.location.column + dc[i];

            Location nloc = Location{ nr, nc };
            if (!mMap.IsValidLocation(nloc))
            {
                continue;
            }

            if (mMap[nr][nc] != SnakeMap::Dot::Road || step[nr][nc] != INF)
            {
                continue;
            }

            step[nr][nc] = node.dist + 1;
            q.push(Node{ node.dist + 1, nloc });
        }
    }

    Direction ans = Direction::None;
    int ans_step = INF;
    Location head = GetHeadLocation();
    if (head.column > 0
        && ans_step > step[head.row][head.column - 1])
    {
        SnakeMap newmap = mMap;
        newmap.SetDirection(Direction::Left);
        newmap.MoveForward();
        if (IsHeadAndTailReachable(newmap))
        {
            ans_step = step[head.row][head.column - 1];
            ans = Direction::Left;
        }
    }

    if (head.column < mMap.GetCountColumns() - 1
        && ans_step > step[head.row][head.column + 1])
    {
        SnakeMap newmap = mMap;
        newmap.SetDirection(Direction::Right);
        newmap.MoveForward();
        if (IsHeadAndTailReachable(newmap))
        {
            ans_step = step[head.row][head.column + 1];
            ans = Direction::Right;
        }
    }

    if (head.row > 0
        && ans_step > step[head.row - 1][head.column])
    {
        SnakeMap newmap = mMap;
        newmap.SetDirection(Direction::Up);
        newmap.MoveForward();
        if (IsHeadAndTailReachable(newmap))
        {
            ans_step = step[head.row - 1][head.column];
            ans = Direction::Up;
        }
    }

    if (head.row < mMap.GetCountRows() - 1
        && ans_step > step[head.row + 1][head.column])
    {
        SnakeMap newmap = mMap;
        newmap.SetDirection(Direction::Down);
        newmap.MoveForward();
        if (IsHeadAndTailReachable(newmap))
        {
            ans_step = step[head.row + 1][head.column];
            ans = Direction::Down;
        }
    }

    return ans;
}

AutoSnake::Direction AutoSnake::GetGoodFoodDirection()
{
    const int INF = INT_MAX / 2;
    int * *step;
    step = new int *[GetMap().GetCountRows()];
    for (int r = 0; r < GetMap().GetCountRows(); r++)
    {
        step[r] = new int[GetMap().GetCountColumns()];
        for (int c = 0; c < GetMap().GetCountColumns(); c++)
        {
            step[r][c] = INF;
        }
    }

    struct Node // this struct may help when BFS
    {
        int dist;
        Location location;
    };

    static int dr[] = { -1, 1, 0, 0, };
    static int dc[] = { 0, 0, -1, 1, };

    std::queue<Node> q;
    q.push(Node{ 0, mMap.GetFoodLocation() });
    step[mMap.GetFoodLocation().row][mMap.GetFoodLocation().column] = 0;
    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nr = node.location.row + dr[i];
            int nc = node.location.column + dc[i];

            Location nloc = Location{ nr, nc };
            if (!mMap.IsValidLocation(nloc))
            {
                continue;
            }

            if (mMap[nr][nc] != SnakeMap::Dot::Road || step[nr][nc] != INF)
            {
                continue;
            }

            step[nr][nc] = node.dist + 1;
            q.push(Node{ node.dist + 1, nloc });
        }
    }

    Direction ans = Direction::None;
    int ans_step = INF;
    Location head = GetHeadLocation();
    if (head.column > 0
        && ans_step > step[head.row][head.column - 1])//mDirection != Direction::Right)
    {
        ans_step = step[head.row][head.column - 1];
        ans = Direction::Left;
    }

    if (head.column < mMap.GetCountColumns() - 1
        && ans_step > step[head.row][head.column + 1])//&& mDirection != Direction::Left)
    {
        ans_step = step[head.row][head.column + 1];
        ans = Direction::Right;
    }

    if (head.row > 0
        && ans_step > step[head.row - 1][head.column])//&& mDirection != Direction::Down)
    {
        ans_step = step[head.row - 1][head.column];
        ans = Direction::Up;
    }

    if (head.row < mMap.GetCountRows() - 1
        && ans_step > step[head.row + 1][head.column])//&& mDirection != Direction::Up)
    {
        ans_step = step[head.row + 1][head.column];
        ans = Direction::Down;
    }

    if (ans == Direction::None)
    {
        return ans;
    }

    std::deque<Direction> newlist;
    SnakeMap newmap = mMap;
    newmap.SetDirection(ans);
    newmap.MoveForward();
    while (true)
    {
        Location loc = newmap.GetSnakeQueue().front();
        int curstep = step[loc.row][loc.column];
        if (curstep == 0)
        {
            break;
        }

        Location newloc;
        for (int i = 0; i < 4; i++)
        {
            int nr = loc.row + dr[i];
            int nc = loc.column + dc[i];
            if (!newmap.IsValidLocation(Location{ nr, nc, }))
            {
                continue;
            }

            if (step[nr][nc] == curstep - 1)
            {
                newloc = Location{ nr, nc };
                break;
            }
        }

        Direction dir = SnakeMap::GetAToBDirection(loc, newloc);
        newmap.SetDirection(dir);
        newmap.MoveForward();
        newlist.push_back(dir);
    }

    for (int r = 0; r < mMap.GetCountRows(); r++)
    {
        delete[] step[r];
    }
    delete[] step;

    if (!IsHeadAndTailReachable(newmap))
    {
        if (!mGoodFoodDirectionList.empty())
        {
            Direction cur_ans = mGoodFoodDirectionList.front();
            mGoodFoodDirectionList.pop_front();
            return cur_ans;
        }
        else
        {
            ;
            return Direction::None;
        }
    }
    else
    {
        mGoodFoodDirectionList = newlist;
        return ans;
    }

    return ans;
}

AutoSnake::Direction AutoSnake::GetFarestFoodDirection() const
{
    Direction ans = Direction::None;
    Location head = mMap.GetHeadLocation();
    int distance = -INT_MAX / 2;
    SnakeMap newmap = mMap;
    newmap.SetDirection(Direction::Left);
    int tmp_count = 0;
    std::vector<Direction> ans_arr;
    if (newmap.MoveForward())
    {
        if (GetDistanceBetweenHeadAndFood(newmap) > distance
            && IsHeadAndTailReachable(newmap))
        {
            distance = GetDistanceBetweenHeadAndFood(newmap);
            ans = Direction::Left;
            ans_arr.push_back(Direction::Left);
        }
        tmp_count++;
    }

    newmap = mMap;
    newmap.SetDirection(Direction::Right);
    if (newmap.MoveForward())
    {
        if (GetDistanceBetweenHeadAndFood(newmap) > distance
            && IsHeadAndTailReachable(newmap))
        {
            distance = GetDistanceBetweenHeadAndFood(newmap);
            ans = Direction::Right;
            ans_arr.push_back(Direction::Right);
        }
        tmp_count++;
    }

    newmap = mMap;
    newmap.SetDirection(Direction::Up);
    if (newmap.MoveForward())
    {
        if (GetDistanceBetweenHeadAndFood(newmap) > distance
            && IsHeadAndTailReachable(newmap))
        {
            distance = GetDistanceBetweenHeadAndFood(newmap);
            ans = Direction::Up;
            ans_arr.push_back(Direction::Up);
        }
        tmp_count++;
    }

    newmap = mMap;
    newmap.SetDirection(Direction::Down);
    if (newmap.MoveForward())
    {
        if (GetDistanceBetweenHeadAndFood(newmap) > distance
            && IsHeadAndTailReachable(newmap))
        {
            distance = GetDistanceBetweenHeadAndFood(newmap);
            ans = Direction::Down;
            ans_arr.push_back(Direction::Down);
        }
        tmp_count++;
    }

    if (ans == Direction::None)
    {
        assert(false);
    }
    return ans_arr[rand() % ans_arr.size()];
    /*
    const int INF = -INT_MAX / 2;
    int * *step;
    step = new int *[GetMap().GetCountRows()];
    for (int r = 0; r < GetMap().GetCountRows(); r++)
    {
    step[r] = new int[GetMap().GetCountColumns()];
    for (int c = 0; c < GetMap().GetCountColumns(); c++)
    {
    step[r][c] = INF;
    }
    }

    struct Node
    {
    int dist;
    Location location;
    };

    int dr[] = { -1, 1, 0, 0, };
    int dc[] = { 0, 0, -1, 1, };

    std::queue<Node> q;
    q.push(Node{ 0, GetTailLocation() });
    step[mMap.GetFoodLocation().row][mMap.GetFoodLocation().column] = INF;
    while (!q.empty())
    {
    Node node = q.front();
    q.pop();

    for (int i = 0; i < 4; i++)
    {
    int nr = node.location.row + dr[i];
    int nc = node.location.column + dc[i];

    Location nloc = Location{ nr, nc };
    if (!mMap.IsValidLocation(nloc))
    {
    continue;
    }

    if (mMap[nr][nc] != SnakeMap::Dot::Road || step[nr][nc] != INF)
    {
    continue;
    }

    step[nr][nc] = node.dist + 1;
    q.push(Node{ node.dist + 1, nloc });
    }
    }

    Direction ans = Direction::None;
    int ans_step = INF;
    Location head = GetHeadLocation();
    if (head.column > 0
    && ans_step < step[head.row][head.column - 1])
    {
    SnakeMap newmap = mMap;
    newmap.SetDirection(Direction::Left);
    newmap.MoveForward();
    if (IsHeadAndTailReachable(newmap))
    {
    ans_step = step[head.row][head.column - 1];
    ans = Direction::Left;
    }
    }

    if (head.column < mMap.GetCountColumns() - 1
    && ans_step < step[head.row][head.column + 1])
    {
    SnakeMap newmap = mMap;
    newmap.SetDirection(Direction::Right);
    newmap.MoveForward();
    if (IsHeadAndTailReachable(newmap))
    {
    ans_step = step[head.row][head.column + 1];
    ans = Direction::Right;
    }
    }

    if (head.row > 0
    && ans_step < step[head.row - 1][head.column])
    {
    SnakeMap newmap = mMap;
    newmap.SetDirection(Direction::Up);
    newmap.MoveForward();
    if (IsHeadAndTailReachable(newmap))
    {
    ans_step = step[head.row - 1][head.column];
    ans = Direction::Up;
    }
    }

    if (head.row < mMap.GetCountRows() - 1
    && ans_step < step[head.row + 1][head.column])
    {
    SnakeMap newmap = mMap;
    newmap.SetDirection(Direction::Down);
    newmap.MoveForward();
    if (IsHeadAndTailReachable(newmap))
    {
    ans_step = step[head.row + 1][head.column];
    ans = Direction::Down;
    }
    }

    for (int r = 0; r < mMap.GetCountRows(); r++)
    {
    delete[] step[r];
    }
    delete[] step;

    return ans;
    */
}

AutoSnake::Direction AutoSnake::GetValidRandomDirection() const
{
    Direction ans_arr[4];
    int cnt_ans = 0;
    Location cur = GetHeadLocation();
    Location tmp = cur;
    tmp.column--;
    if (mMap.IsCanInLocation(tmp))
    {
        ans_arr[cnt_ans++] = Direction::Left;
    }

    tmp = cur;
    tmp.column++;
    if (mMap.IsCanInLocation(tmp))
    {
        ans_arr[cnt_ans++] = Direction::Right;
    }

    tmp = cur;
    tmp.row--;
    if (mMap.IsCanInLocation(tmp))
    {
        ans_arr[cnt_ans++] = Direction::Up;
    }

    tmp = cur;
    tmp.row++;
    if (mMap.IsCanInLocation(tmp))
    {
        ans_arr[cnt_ans++] = Direction::Down;
    }

    if (cnt_ans > 0)
    {
        return ans_arr[rand() % cnt_ans];
    }
    else
    {
        return Direction::None;
    }
}

AutoSnake::Direction AutoSnake::GetGoodDirection()
{
    Direction ans = GetGoodFoodDirection();
    if (ans == Direction::None)
    {
        ans = GetFarestFoodDirection();
    }

    if (ans == Direction::None)
    {
        ans = GetQuickFoodDirection();
    }

    if (ans == Direction::None)
    {
        assert(false);
        ans = GetValidRandomDirection();
    }
    return ans;
}

AutoSnake::Location AutoSnake::GetRandomLocation() const
{
    bool full = true;
    for (int r = 0; r < mMap.GetCountRows(); r++)
    {
        for (int c = 0; c < mMap.GetCountColumns(); c++)
        {
            if (mMap[r][c] == SnakeMap::Dot::Road)
            {
                full = false;
                break;
            }
        }
    }

    if (full)
    {
        return Location{ -1, -1 };
    }

    while (true)
    {
        int row = rand() % mMap.GetCountRows();
        int col = rand() % mMap.GetCountColumns();
        if (mMap[row][col] != SnakeMap::Dot::Road)
        {
            continue;
        }
        else
        {
            return Location{ row, col };
        }
    }
}

void AutoSnake::GenerateFood()
{
    mMap.SetFoodLocation(GetRandomLocation());
    if (GetFoodLocation() == Location{ -1, -1 })
    {
        mFailed = true;
    }
}

bool AutoSnake::IsFoodReachable() const
{
    return false;
}

bool AutoSnake::MoveForward()
{
    if (IsFailed())
    {
        return false;
    }

    mMap.SetDirection(GetGoodDirection());
    const Location &head = GetHeadLocation();

    Location newLoc = head;
    switch (mMap.GetDirection())
    {
    case AutoSnake::Direction::Left:
        newLoc.column--;
        break;
    case AutoSnake::Direction::Right:
        newLoc.column++;
        break;
    case AutoSnake::Direction::Up:
        newLoc.row--;
        break;
    case AutoSnake::Direction::Down:
        newLoc.row++;
        break;
    default:
        SetFail();
        return false;
        break;
    }

    if (!mMap.IsCanInLocation(newLoc))
    {
        SetFail();
        return false;
    }

    bool needgenerate = false;
    if (mMap.At(newLoc) == SnakeMap::Dot::Food)
    {
        needgenerate = true;
    }

    mMap.MoveForward();

    if (needgenerate)
    {
        GenerateFood();
    }

    //IsHeadAndTailReachable(mMap);
    return true;
}

bool AutoSnake::IsHeadAndTailReachable(SnakeMap & map) // static function
{
    struct Node
    {
        int dist;
        Location location;
    };

    static int dr[] = { -1, 1, 0, 0, };
    static int dc[] = { 0, 0, -1, 1, };
    if (map.GetSnakeQueue().empty())
    {
        return false;
    }

    Location head = map.GetSnakeQueue().front();
    Location tail = map.GetSnakeQueue().back();
    if (map.GetSnakeLength() < 3)
    {
        return true;
    }

    SnakeStepMap step(map.GetCountRows(), map.GetCountColumns(), 0); // 0 cannot reach, 1 can reach
    std::queue<Node> q;
    q.push(Node{ 0, head });
    step[head.row][head.column] = 0;
    //	if (head != tail) assert(false);
    while (!q.empty())
    {
        Node nd = q.front();
        Location loc = nd.location;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nr = loc.row + dr[i];
            int nc = loc.column + dc[i];
            Location newloc = Location{ nr, nc };

            if (newloc == tail)
            {
                if (nd.dist == 0) // this is a big probleam, too compleated
                {
                    // snke cannot bite its tail
                }

                return true;
            }

            if (!map.IsCanInLocation(newloc))
            {
                continue;
            }

            if (step[nr][nc] != 0)
            {
                continue;
            }

            step[nr][nc] = nd.dist + 1;
            q.push(Node{ nd.dist + 1, newloc });
        }
    }

    // assert(false);
    return false;
}

int AutoSnake::GetDistanceBetweenHeadAndFood(const SnakeMap & map)
{
    Location head = map.GetSnakeQueue().front();
    Location food = map.GetFoodLocation();
    return (abs(head.row - food.row) + abs(head.column - food.column));
}
