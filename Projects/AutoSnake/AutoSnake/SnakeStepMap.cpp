#include "SnakeStepMap.h"

SnakeStepMap::SnakeStepMap(int countRows, int countColumns, int INFVALUE)
{
	mMap.resize(countRows);
	for (int i = 0; i < countRows; i++)
	{
		mMap[i].resize(countColumns);
		for (int j = 0; j < countColumns; j++)
		{
			mMap[i][j] = INFVALUE;
		}
	}
}

SnakeStepMap::~SnakeStepMap()
{
}
