#pragma once

#ifndef SNAKESTEPMAP_H
#define SNAKESTEPMAP_h

#include <vector>

class SnakeStepMap
{
public:
	SnakeStepMap(int countRows, int countColumns, int INFVALUE);
	~SnakeStepMap();
	SnakeStepMap(const SnakeStepMap &rhs) = default;
	SnakeStepMap &operator = (const SnakeStepMap &rhs) = default;
	int &At(int row, int column) { return mMap[row][column]; }
	std::vector<int> &operator [] (int row) { return mMap[row]; }

private:
	std::vector<std::vector<int> > mMap;
};

#endif // SNAKESTEPMAP_H