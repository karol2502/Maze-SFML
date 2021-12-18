#pragma once
#include "Walls.h"
#include "DisjSet.h"

class MazeGenerator
{
	int width;
	int height;
	DisjSet cells;
	Walls walls;

	std::map<int, int> generatedWalls;

public:
	MazeGenerator(int width, int height);
	void Generate();
	std::map<int, int> getGeneratedMaze();
};

