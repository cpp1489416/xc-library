#include "SnakeMap.h"
#include <cassert>

SnakeMap::SnakeMap(int countRows, int countColumns)
	: mCountRows(0), mCountColumns(0)
{
	ChangeCountRowsAndColumns(countRows, countColumns);
	Clear();
}

SnakeMap::~SnakeMap()
{
	ReleaseMap();
}

const SnakeMap::Location & SnakeMap::GetHeadLocation() const
{
	if (mSnakeQueue.empty())
	{
		assert(false);
	}

	return mSnakeQueue.front();}

void SnakeMap::SetFoodLocation(const Location & location)
{
	//if (At(mFoodLocation) == Dot::Food)
	//{
	//	At(mFoodLocation) = Dot::Road;
	//}

	mFoodLocation = location;
    if (!mFoodLocation.IsValid()) 
    {
        return;
    }

	At(location) = Dot::Food;
}

void SnakeMap::Clear()
{
	for (int r = 0; r < GetCountRows(); r++)
	{
		for (int c = 0; c < GetCountColumns(); c++)
		{
			GetDot(r, c) = Dot::Road;
		}
	}
	mSnakeQueue.clear();
}

void SnakeMap::AddSnakeHeadDot(const Location & location)
{
	mSnakeQueue.push_front(location);
	At(location) = Dot::Snake;
}

void SnakeMap::AddSnakeTailDot(const Location & location)
{
	mSnakeQueue.push_back(location);
	At(location) = Dot::Snake;
}

#include <cassert>
bool SnakeMap::MoveForward()
{
	if (mSnakeQueue.empty())
	{
		return false;
	}

	Location newloc = GetMovedLocation(mSnakeQueue.front(), mDirection);
	if (!IsCanInLocation(newloc))
	{
		return false;
	}

	if (newloc != mFoodLocation)
	{
		At(GetSnakeQueue().back()) = Dot::Road;
		mSnakeQueue.pop_back();
	}
	else 
	{
	//	return false;
//		assert(false);
	}

	AddSnakeHeadDot(newloc);
	return true;
}

bool SnakeMap::IsValidLocation(const Location & location) const
{
	int row = location.row;
	int col = location.column;
	return row >= 0 && row < GetCountRows() && col >= 0 && col < GetCountColumns();
}

bool SnakeMap::IsCanInLocation(const Location & location) const
{
	if (!IsValidLocation(location))
	{
		return false;
	}

	if (At(location) == Dot::Road || At(location) == Dot::Food || location == mSnakeQueue.back())
	{
		return true;
	}
	else
	{
		return false;
	}
}

SnakeMap::Location SnakeMap::GetMovedLocation(const Location & location, Direction direction) const
{
	switch (direction)
	{
	case SnakeMap::None:
		return location;
		break;
	case SnakeMap::Left:
		return Location{ location.row, location.column - 1, };
		break;
	case SnakeMap::Right:
		return Location{ location.row, location.column + 1, };
		break;
	case SnakeMap::Up:
		return Location{ location.row - 1, location.column, };
		break;
	case SnakeMap::Down:
		return Location{ location.row + 1, location.column, };
		break;
	default:
		return location;
		break;
	}
}

SnakeMap::Direction SnakeMap::GetAToBDirection(const Location & a, const Location & b)
{
	if (a.column - 1 == b.column)
	{
		return Direction::Left;
	}
	else if (a.column + 1 == b.column)
	{
		return Direction::Right;
	}
	else if (a.row - 1 == b.row)
	{
		return Direction::Up;
	}
	else if (a.row + 1 == b.row)
	{
		return Direction::Down;
	}

	return Direction::None;
}

void SnakeMap::ChangeCountRowsAndColumns(int countRows, int countColumns)
{
	ReleaseMap();
	mCountRows = countRows;
	mCountColumns = countColumns;
	mMap.resize(countRows);
	for (int r = 0; r < countRows; r++)
	{
		mMap[r].resize(countColumns);
	}
	Clear();
}

void SnakeMap::CloneMap(const SnakeMap & map)
{
	if (GetCountRows() != map.GetCountColumns() &&
		GetCountColumns() != map.GetCountColumns())
	for (int r = 0; r < GetCountRows(); r++)
	{
		for (int c = 0; c < GetCountColumns(); c++)
		{
			mMap[r][c] = map[r][c];
		}
	}
}

void SnakeMap::ReleaseMap()
{
	return; // do nothing
}

