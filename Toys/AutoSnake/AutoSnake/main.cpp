
#include <iostream>
#include "AutoSnake.h"`
#include "SnakeMap.h"

namespace
{
	void PrintMap(const AutoSnake &snake)
	{
		SnakeMap map = snake.GetMap();
		for (int r = 0; r < map.GetCountRows(); r++)
		{
			for (int c = 0; c < map.GetCountColumns(); c++)
			{
				switch (map[r][c])
				{
				case SnakeMap::Dot::Road:
					std::cout << ".";
					break;
				case SnakeMap::Dot::Snake:
					std::cout << "@";
					break;
				default:
					break;
				}
			}
			std::cout << std::endl;
		}
	}
}

int main(int argc, char * *argv)
{
	AutoSnake snake(30, 30);
	while (true)
	{
		system("Pause");
		PrintMap(snake);
		snake.timeout();
	}
	return 0;
}

