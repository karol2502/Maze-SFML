#include "Walls.h"

int Walls::getWallIndex(std::vector<int> v, int wall)
{
	auto it = find(v.begin(), v.end(), wall);

	// If element was found
	if (it != v.end())
	{
		// calculating the index
		// of K
		int index = it - v.begin();
		return index;
	}
	else {
		// If the element is not
		// present in the vector
		return -1;
	}
}

std::pair<int, int> Walls::getXYfromIndex(int index, int width, int height)
{
	int x = index % width;
	int y = (int)(index / width);
	return std::pair<int, int>(x,y);
}

Walls::Walls(int width, int height)
{
	this->height = height;
	this->width = width;
	numberOfWalls = (width - 1) * height + width * (height - 1);
	for (int i = 0; i < numberOfWalls; i++)
	{
		wallsToCheck.push_back(i);
	}
	//initialize vector of vertical walls
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width - 1; y++)
		{
			int wall = x * (2 * width - 1) + y;
			verticalWalls.push_back(wall);
		}
	}
	//initialize vector of horizontal walls
	for (int x = 0; x < height-1; x++)
	{
		for (int y = 0; y < width; y++)
		{
			int wall = x * (2 * width - 1) + (width - 1) + y;
			horizontalWalls.push_back(wall);
		}
	}
}

int Walls::GetRandomWall()
{	
	int index = std::rand() % wallsToCheck.size();
	int wall = wallsToCheck[index];
	wallsToCheck.erase(wallsToCheck.begin() + index);
	return wall;
}

std::pair<int, int> Walls::getCellsFromWall(int wall)
{
	//check if wall is vertical
	if (std::find(verticalWalls.begin(), verticalWalls.end(), wall) != verticalWalls.end()) 
	{
		int index = getWallIndex(verticalWalls, wall);
		std::pair<int, int> pos = getXYfromIndex(index, width-1, height);
		int firstCell = pos.second * width + pos.first;
		return std::pair<int, int>(firstCell, firstCell + 1);
	}
	//otherwise it is horizontal
	else
	{
		int index = getWallIndex(horizontalWalls, wall);
		std::pair<int, int> pos = getXYfromIndex(index, width, height-1);
		int firstCell = pos.second * width + pos.first;
		return std::pair<int, int>(firstCell, firstCell + width);
	}
}

int Walls::getWallsToCheckSize()
{
	return wallsToCheck.size();
}
