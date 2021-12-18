#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(int width, int height) : cells(width*height), walls(width, height)
{
	this->width = width;
	this->height = height;
}

void MazeGenerator::Generate()
{
	while (walls.getWallsToCheckSize())
	{
		int wall = walls.GetRandomWall();
		std::pair<int, int> adjacentCells = walls.getCellsFromWall(wall);
		if (cells.find(adjacentCells.first) != cells.find(adjacentCells.second))
		{
			cells.Union(adjacentCells.first, adjacentCells.second);
			generatedWalls[wall] = 0;
		}
		else
		{
			generatedWalls[wall] = 1;
		}
	}
}

std::map<int, int> MazeGenerator::getGeneratedMaze()
{
	return generatedWalls;
}
