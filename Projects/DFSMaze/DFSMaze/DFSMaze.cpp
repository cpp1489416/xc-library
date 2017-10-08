#include "DFSMaze.h"

#include <iostream>
#include <stack>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include<queue>

namespace Xc
{
    DFSMaze::DFSMaze(int width, int height)
    {
        if (width % 2 == 0)
        {
            width++;
        }

        if (height % 2 == 0)
        {
            height++;
        }

        mWidth = width;
        mHeight = height;

        srand(time(nullptr));
        init();
        buildMap(1, 1);

    }

    DFSMaze::~DFSMaze()
    {
    }

    void DFSMaze::print()
    {
        for (int row = 0; row < mHeight; row++)
        {
            for (int col = 0; col < mWidth; col++)
            {
                std::cout << mMap[row][col];
            }

            std::cout << std::endl;
        }
    }

    void DFSMaze::solve()
    {
        Location end(width() - 2, height() - 2);

        static int dr[] = { 0, 0, -2, 2 };
        static int dc[] = { -2, 2, 0, 0 };

        struct Node
        {
            Node(Location location, Node *previous) : location(location), previous(previous) {}
            
            Location location;
            Node * previous;
        };

        bool vis[MAXN][MAXN];
        memset(vis, false, sizeof(vis));

        std::queue<Node *> q;
        q.push(new Node(Location(1, 1), nullptr));
        while (!q.empty())
        {
            Node * node = q.front();
            q.pop();

            if (node->location.mRow == end.mRow && node->location.mColumn == end.mColumn)
            {
                Node * cur = node;
                int lastRow = node->location.mRow;
                int lastCol = node->location.mColumn;
                while (node != nullptr)
                {
                    int row = node->location.mRow;
                    int col = node->location.mColumn;
                    mMap[(row + lastRow) / 2][(col + lastCol) / 2] = mMap[row][col] = STEP;
                    node = node->previous;
                    lastRow = row;
                    lastCol = col;
                }

                print();
                return;
            }

            int row = node->location.mRow;
            int col = node->location.mColumn;
            vis[row][col] = true;

            for (int i = 0; i < 4; i++)
            {
                int newRow = row + dr[i];
                int newCol = col + dc[i];

                if (newRow < 0 || newRow >= height() || newCol < 0 || newCol >= width())
                {
                    continue;
                }

                if (vis[newRow][newCol] || mMap[(newRow + row) / 2][(newCol + col)/ 2] == WALL)
                {
                    continue;
                }

                Node * newNode = new Node(Location(newRow, newCol), node);
                q.push(newNode);

                vis[newRow][newCol] = true;
            }
        }
    }

    void DFSMaze::init()
    {
        for (int row = 0; row < mHeight; row++)
        {
            for (int col = 0; col < mWidth; col++)
            {
                if (row % 2 == 1 && col % 2 == 1)
                {
                    mMap[row][col] = ROAD;
                }
                else
                {
                    mMap[row][col] = WALL;
                }
            }
        }

        memset(mVis, false, sizeof(mVis));
    }

    void DFSMaze::buildMap(int startRow, int startColumn)
    {
        memset(mVis, false, sizeof(mVis));

        Location start(startRow, startColumn);
        
        std::stack<Location> stack;
        stack.push(start);

        static int dr[] = { 0, 0, -1, 1 };
        static int dc[] = { -1, 1, 0, 0 };

        while (!stack.empty())
        {
            Location cur = stack.top();
            
            int row = cur.mRow;
            int col = cur.mColumn;

            int dir = getPossible(Location(row, col));
            
            if (dir == -1)
            {
                stack.pop();
                continue;
            }

            int newRow = row + 2 * dr[dir];
            int newCol = col + 2 * dc[dir];
            int newPRow = row + dr[dir];
            int newPCol = col + dc[dir];
        
            mVis[newRow][newCol] = mVis[newPRow][newPCol] = true;
            mMap[newRow][newCol] = mMap[newPRow][newPCol] = ROAD;
            stack.push(Location(newRow, newCol));

      //      print();
        //    std::cout << std::endl;
        }
    }

    int DFSMaze::getPossible(Location location)
    {
        static int dr[] = { 0, 0, -1, 1 };
        static int dc[] = { -1, 1, 0, 0 };

        int ans[100];
        int cntAns = 0;

        for (int i = 0; i < 4; i++)
        {
            int row = location.mRow + 2 * dr[i];
            int col = location.mColumn + 2 * dc[i];

            if (row < 0 || row >= height() || col < 0 || col >= width())
            {
                continue;
            }

            if (mVis[row][col] == true)
            {
                continue;
            }

            ans[cntAns++] = i;
        }

        if (cntAns == 0)
        {
            return -1;
        }
        else
        {
            return ans[rand() % cntAns];
        }
    
        return 0;
    }
}