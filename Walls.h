#pragma once
#include <vector>
#include <map>
#include <utility>
#include <time.h>  

class Walls
{
	std::vector<int> wallsToCheck;
	int height;
	int width;
	int numberOfWalls;	
	std::vector<int>horizontalWalls;
	std::vector<int>verticalWalls;

	int getWallIndex(std::vector<int> v, int wall);
	std::pair<int,int> getXYfromIndex(int index, int width, int height);

public:
	Walls(int width, int height);
	int GetRandomWall();
	std::pair<int, int> getCellsFromWall(int wall);
	int getWallsToCheckSize();
};

