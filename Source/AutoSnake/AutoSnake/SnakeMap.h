#pragma once
#ifndef SNAKEMAP_H
#define SNAKEMAP_H

#include <vector>
#include <deque>

class SnakeMap
{
public:
	enum class Dot
	{
		None,
		Road,
		Snake,
		Food,
		Wall,
	};

	struct Location
	{
		int row;
		int column;

		bool operator == (const Location &rhs) const { return row == rhs.row && column == rhs.column; }
		bool operator != (const Location &rhs) const { return !(*this == rhs); }
        static Location GetInvalidLocation() { return Location{ -1, -1 }; }
        bool IsValid() const { return (*this) != GetInvalidLocation(); }
    };

	enum Direction
	{
		None, Left, Right, Up, Down,
	};

public:
	SnakeMap(int countRows = 100, int countColumns = 100);
	~SnakeMap();
	SnakeMap(const SnakeMap &rhs) = default;
	SnakeMap &operator =(const SnakeMap &rhs) = default;
	inline int GetCountRows() const { return mCountRows; }
	inline int GetCountColumns() const { return mCountColumns; }
	void ChangeCountRowsAndColumns(int countRows, int countColumns);
	inline const Dot &GetDot(int row, int column) const { return mMap[row][column]; }
	inline Dot &GetDot(int row, int column) { return mMap[row][column]; }
	inline const std::vector<Dot> &operator[] (int row) const { return mMap[row]; }
	inline std::vector<Dot> &operator[] (int row) { return mMap[row]; }
	inline const Dot &At(const Location &location) const { return mMap[location.row][location.column]; }
	inline Dot &At(const Location &location) { return mMap[location.row][location.column]; }
	Direction GetDirection() const { return mDirection; }
	void SetDirection(Direction direction) { mDirection = direction; }
	const std::deque<Location> &GetSnakeQueue() const { return mSnakeQueue; }
	std::deque<Location> &GetSnakeQueue() { return mSnakeQueue; }
	const Location &GetFoodLocation() const { return mFoodLocation; }
	Location &GetFoodLocation() { return mFoodLocation; }
	const Location &GetHeadLocation() const;
	void SetFoodLocation(const Location &location);
	int GetSnakeLength() const { return mSnakeQueue.size(); }
	void Clear();
	void AddSnakeHeadDot(const Location &location);
	void AddSnakeTailDot(const Location &location);
	bool IsValidLocation(const Location &location) const;
	bool IsCanInLocation(const Location &location) const;
	Location GetMovedLocation(const Location &location, Direction direction) const;
	static Direction GetAToBDirection(const Location &a, const Location &b);
	bool MoveForward();

private:
	void CloneMap(const SnakeMap &map);
	void ReleaseMap();

	int mCountRows;
	int mCountColumns;
	std::vector<std::vector<Dot> > mMap;
	Direction mDirection;
	Location mFoodLocation;
	std::deque<Location> mSnakeQueue;
};

#endif