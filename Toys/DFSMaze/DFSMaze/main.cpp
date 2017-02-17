#include <iostream>
#include <string>
#include "DFSMaze.h"

int main()
{
    std::cout << "hello)" << std::endl;

    int cntRow;
    int cntCol;

    while (true)
    {
        int cntRow;
        int cntCol;
        std::cin >> cntRow >> cntCol;

        Xc::DFSMaze maze(cntRow, cntCol);
        maze.print();
        std::cout << std::endl;
        maze.solve();
    }

    system("Pause");
    return 0;
}