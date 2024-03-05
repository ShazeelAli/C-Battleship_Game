/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			printf("%d ", values[i][j]);
		}
		printf("\n");
	}
	return;
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = 0;

		}
	}

	map[0][0] = 2;
	map[1][0] = 2;

	map[2][1] = 3;
	map[2][2] = 3;
	map[2][3] = 3;

	map[MAP_SIZE - 5][MAP_SIZE - 1] = 5;
	map[MAP_SIZE - 4][MAP_SIZE - 1] = 5;
	map[MAP_SIZE - 3][MAP_SIZE - 1] = 5;
	map[MAP_SIZE - 2][MAP_SIZE - 1] = 5;
	map[MAP_SIZE - 1][MAP_SIZE - 1] = 5;

	map[MAP_SIZE - 1][0] = 4;
	map[MAP_SIZE - 1][1] = 4;
	map[MAP_SIZE - 1][2] = 4;
	map[MAP_SIZE - 1][3] = 4;

	return;

}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{	
	// 0 is horizontal 1 is vertical
	int rand_dir = rand() % 2;

	int rand_index_x = rand() % MAP_SIZE;
	int rand_index_y = rand() % MAP_SIZE;
	
	if(rand_dir == 0)
	{
		while ((rand_index_x + size) > (MAP_SIZE))
		{
			rand_index_x = rand() % MAP_SIZE;
			rand_index_y = rand() % MAP_SIZE;
		}
	}
	else
	{
		while ((rand_index_y + size) > (MAP_SIZE))
		{
			rand_index_x = rand() % MAP_SIZE;
			rand_index_y = rand() % MAP_SIZE;
		}
	}
	
	for(int i = 0; i < size;i++)
	{
		if(rand_dir == 0)
		{
			map[rand_index_y][rand_index_x + i] = size;
		}
		else
		{
			map[rand_index_y + i][rand_index_x] = size;
		}
	}
	return;
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	int count = 0;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if(map[i][j] == value)
			{
				count++;
			}
		}
	}
	return count; // to prevent compiler warning (you must complete this function)
}

int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE])
{	
	// 1 = horizontal 2 = vertical
	int j;
	int i;
	*row = 0;
	*col = 0;
	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE - 1; j++)
		{
			if (map[i][j] == size) 
			{ 
				
				*row = i;
				*col = j; 
				break; 

			}
		}
		
		if (map[i][j] == size)
		{

			*row = i;
			*col = j;
			break;

		}
		
	}

	
	if(map[*row][*col + 1] == size)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}


int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int row = -1, col=-1,dir;
	//dir = TopLeftPosition(size, &row, &col, map);

	//1 = horizontal 2 = vertical
	int j;
	int i;
	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE - 1; j++)
		{
			if (map[i][j] == size)
			{
	
				row = i;
				col = j;
				break;
	
			}
		}
	
		if (map[i][j] == size)
		{
	
			row = i;
			col = j;
			break;
	
		}
	
	}

	if(row == -1 || col == -1)
	{
		return 0;
	}
	
	if (map[row][col + 1] == size)
	{
		dir = 1;
	}
	else
	{
		dir = 2;
	}
	
	if (dir == 1)
	{
		for(int i = col; i < (size+col);i++)
		{
			
			if (row + 1 < MAP_SIZE) {
				if (map[row + 1][i] != 0 && map[row + 1][i] != size) { return 0; }
			}

			if (i + 1 < MAP_SIZE) {
				if (map[row][i + 1] != 0 && map[row][i+1] != size) { return 0; }
			}

			if (row - 1 >= 0) {
				if (map[row - 1][i] != 0 && map[row - 1][i] != size) { return 0; }
			}

			if(i-1 >= 0){
				if (map[row][i - 1] != 0 && map[row][i - 1] != size) { return 0; }
			}
				
			
		}
	}
	else
	{
		for (int i = row; i < (size + row); i++)
		{ 
			
			if (i + 1 < MAP_SIZE) {
				if (map[i + 1][col] != 0 && map[i + 1][col] != size) { return 0; }
			}

			if (col + 1 < MAP_SIZE) {
				if (map[i][col + 1] != 0 && map[i][col + 1] != size) { return 0; }
			}

			if (i - 1 >= 0) {
				if (map[i - 1][col] != 0 && map[i - 1][col] != size) { return 0; }
			}

			if (col - 1 >= 0) {
				if (map[i][col - 1] != 0 && map[i][col - 1] != size) { return 0; }
			}

		}
	}

	return 1;
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = 0;
		}
	}
	AddRandomShip(2,map);
	AddRandomShip(3, map);
	AddRandomShip(4, map);
	AddRandomShip(5, map);
	while(!IsShipValid(2,map) || !IsShipValid(3,map) || !IsShipValid(4,map) || !IsShipValid(5,map))
	{

		for(int i = 0; i < MAP_SIZE; i++)
		{
			for(int j = 0; j < MAP_SIZE; j++)
			{
				map[i][j] = 0;
			}
		}
		AddRandomShip(2, map);
		AddRandomShip(3, map);
		AddRandomShip(4, map);
		AddRandomShip(5, map);
	}

	
	return;
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	int most_recent_shot = 0;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if((shots[i][j] % 1000) > most_recent_shot)
			{
				most_recent_shot = shots[i][j] % 1000;
			}

		}
	}
	if(shots[row][col] != 0)
	{
		return;
	}
	
	if(map[row][col] != 0)
	{
		shots[row][col] = 1000 + most_recent_shot + 1;
	}
	else
	{
		shots[row][col] = most_recent_shot + 1;
	}
	


	int top_left_col;
	int top_left_row;
	int dir;
	int count;
	for(int size = 2; size <= 5; size++)
	{
		count = 0;
		dir = TopLeftPosition(size,&top_left_row,&top_left_col,map);
		if(dir == 1)
		{
			for (int i = 0; i < size; i++)
			{
				if(shots[top_left_row][top_left_col + i] >= 1000)
				{
					count++;
				}
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (shots[top_left_row + i][top_left_col] >= 1000)
				{
					count++;
				}
			}
		
		}

		if(count == size)
		{
			if (dir == 1)
			{
				for (int i = 0; i < size; i++)
				{
					if (shots[top_left_row][top_left_col + i] >= 1000)
					{
						shots[top_left_row][top_left_col + i] = (shots[top_left_row][top_left_col + i] % 1000) + (size * 1000);
					}
				}
			}
			else
			{
				for (int i = 0; i < size; i++)
				{
					if (shots[top_left_row + i][top_left_col] >= 1000)
					{
						shots[top_left_row + i][top_left_col] = (shots[top_left_row + i][top_left_col] % 1000) + (size * 1000);
					}
				}

			}
		
		}
		


		
	}
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	int number_of_ships = 0;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if(map[i][j] > number_of_ships)
			{
				number_of_ships = map[i][j];
			}
		}
		
	}

	int over_threshold = 0;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (shots[i][j] >= 2000)
			{
				over_threshold++;
			}
		}

	}

	int all_ship_pos_count = 0;
	for(int i = 2; i<= number_of_ships;i++)
	{
		all_ship_pos_count += i;
	}

	if(over_threshold == all_ship_pos_count)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

/*************************************************************************
** You should define your own test functions below
*************************************************************************/

// Example: a test function for Task One
void TestPrintArray(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	printf("Map 1: \n");
	PrintArray(map1);

	int map2[MAP_SIZE][MAP_SIZE] = {0};
	for (int i = 0; i < MAP_SIZE; i++) {
		map2[MAP_SIZE-i-1][i] = i;
	}
	printf("\nMap 2:\n");
	PrintArray(map2);
}

// Example: a test function for Task Two
void TestInitialiseMap(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	InitialiseMap(map1);
	printf("\nMap: \n");
	PrintArray(map1);
}

// Example: a test function for Task Three
void TestAddRandomShip(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	int map2[MAP_SIZE][MAP_SIZE] = {0};

	AddRandomShip(5, map1);

	printf("\nMap: \n");
	PrintArray(map1);

	AddRandomShip(2, map2);
	AddRandomShip(3, map2);
	AddRandomShip(4, map2);
	AddRandomShip(5, map2);

	printf("\nMap: \n");
	PrintArray(map2);
}

// Example: a test function for Task Three
void TestAddRandomShipLoop(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = { 0 };
	int map2[MAP_SIZE][MAP_SIZE] = { 0 };

	AddRandomShip(5, map1);

	printf("\nMap: \n");
	PrintArray(map1);

	for (int i = 0; i < 50; i++) {
		AddRandomShip(2, map2);
		AddRandomShip(3, map2);
		AddRandomShip(4, map2);
		AddRandomShip(5, map2);
	}

	printf("\nMap: \n");
	PrintArray(map2);
}


void TestCountValues(void) {
	int map[MAP_SIZE][MAP_SIZE] = { 0 }; 
	int count, shipSize;

	InitialiseMap(map); 
	PrintArray(map);

	for (shipSize = 2; shipSize <= 5; shipSize++) {
		count = CountValues(shipSize, map); printf("The value %d appears %d times\n", shipSize, count);
	}
}

void TestTopLeftPosition(void)
{
	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	int row, col, direction, shipSize;
	InitialiseMap(map);
	PrintArray(map);
	for (shipSize = 2; shipSize <= 5; shipSize++) {
		direction = TopLeftPosition(shipSize, &row, &col, map);
		printf("Ship %d is at (%d, %d) facing %d\n", shipSize,
			row, col, direction);
	}
}


void TestIsShipValid(void) {
	//int map[MAP_SIZE][MAP_SIZE] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//		{ 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0},
	//		{ 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//		{ 0, 0,0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 },
	//		{ 0, 0,0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 },
	//		{ 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	//		{ 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	//		{ 3, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	//		{ 3, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	//		{ 3, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//		{ 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//		{ 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//		{ 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	int valid, shipSize;
	InitialiseMap(map); 
	PrintArray(map);
	for (shipSize = 2; shipSize <= 5; shipSize++) {
		valid = IsShipValid(shipSize, map); 
		printf("Is ship %d valid? %d\n", shipSize, valid);
	}

	//Move Ship 3 to an invalid position 
	map[2][3] = 0;
	map[2][2] = 0;
	map[2][1] = 0;

	//Move Ship 4 to an invalid position 
	map[5][0] = 0;
	map[5][1] = 0;
	map[5][2] = 0;
	map[5][3] = 0;

	map[4][2] = 4;
	map[4][3] = 4;
	map[4][4] = 4;
	map[4][5] = 4;
	PrintArray(map);

	for (shipSize = 2; shipSize <= 5; shipSize++) {
		valid = IsShipValid(shipSize, map); printf("Is ship %d valid? %d\n", shipSize, valid);
	}

}

void TestIsShipValidLoop(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = { 0 };


	AddRandomShip(2, map1);
	AddRandomShip(3, map1);
	AddRandomShip(4, map1);
	AddRandomShip(5, map1);


	printf("\nMap: \n");
	PrintArray(map1);

	int valid;
	for (int shipSize = 2; shipSize <= 5; shipSize++) {
		valid = IsShipValid(shipSize, map1); 
		printf("Is ship %d valid? %d\n", shipSize, valid);
	}

}

void TestIsShipValidTrue(void) {
	int map[MAP_SIZE][MAP_SIZE];
	int valid, shipSize;
	int output = 0;

	// Initialise a random (and valid) map 1000 times
	for (int i = 0; i < 1000; i++) {
		InitialiseRandomMap(map);
		// All ships are in valid positions
		// Check that IsShipValid() returns true
		for (shipSize = 2; shipSize <= 5; shipSize++) {
			valid = IsShipValid(shipSize, map);
			if (!valid) {
				if (!output) {
					printf("Reporting an invalid ship!\n");
					PrintArray(map);
					output = 1;
				}
			}
		}
	}
	printf("All ships are valid");
}

void TestInitialiseRandomMap(void) {
	int map[MAP_SIZE][MAP_SIZE];
	InitialiseRandomMap(map); 
	PrintArray(map);
	printf("%d\n", IsShipValid(2, map));
	printf("%d\n", IsShipValid(3, map));
	printf("%d\n", IsShipValid(4, map));
	printf("%d\n", IsShipValid(5, map));
}

void TestFireShot(void) {
	int map[MAP_SIZE][MAP_SIZE] = { 0 }; 
	int shots[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseMap(map);

	printf("Map:\n"); 
	PrintArray(map); 

	printf("Shots:\n"); 
	PrintArray(shots);

	FireShot(shots, map, 2, 0); 
	printf("Shots:\n");
	PrintArray(shots);

	FireShot(shots, map, 2, 1);
	printf("Shots:\n");
	PrintArray(shots);

	FireShot(shots, map, 2, 2);
	printf("Shots:\n");
	PrintArray(shots);

	FireShot(shots, map, 2, 3);
	printf("Shots:\n");
	PrintArray(shots);

	FireShot(shots, map, 0, 0);
	FireShot(shots, map, 1, 0);
	FireShot(shots, map, 2, 0);
	FireShot(shots, map, 3, 0);
	FireShot(shots, map, 4, 0);
	FireShot(shots, map, 5, 0);
	printf("Shots:\n"); 
	PrintArray(shots);
}

void TestCheckGameOverLoop(void) {
	int map[MAP_SIZE][MAP_SIZE] = { 0 }; 
	int shots[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseMap(map); printf("Map:\n"); 
	PrintArray(map); 
	printf("Shots:\n"); 
	PrintArray(shots);
	printf("\n");
	while (!CheckGameOver(shots, map)) {
		FireShot(shots, map, rand() % MAP_SIZE, rand() % MAP_SIZE);
	} 
	PrintArray(shots);
}

void TestCheckGameOver(void)
{
	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	int shots[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseMap(map);

	printf("Map:\n");
	PrintArray(map);

	printf("Shots:\n");
	PrintArray(shots);

	FireShot(shots, map, 0, 0);
	FireShot(shots, map, 1, 0);
	printf("Shots:\n");
	PrintArray(shots);

	FireShot(shots, map, 2, 1);
	FireShot(shots, map, 2, 2);
	FireShot(shots, map, 2, 3);
	printf("Shots:\n");
	PrintArray(shots);

	FireShot(shots, map, 5, 0);
	FireShot(shots, map, 5, 1);
	FireShot(shots, map, 5, 2);
	FireShot(shots, map, 5, 3);
	printf("Shots:\n");
	PrintArray(shots);

	FireShot(shots, map, 1, 5);
	FireShot(shots, map, 2, 5);
	FireShot(shots, map, 3, 5);
	FireShot(shots, map, 4, 5);
	FireShot(shots, map, 5, 5);
	printf("Shots:\n");
	PrintArray(shots);

	printf("\n Game Over? %d", CheckGameOver(shots, map));


}

int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	//TestPrintArray();
	//TestInitialiseMap();
	//TestAddRandomShip();
	//TestAddRandomShipLoop();
	//TestCountValues();
	//TestTopLeftPosition();
	//TestIsShipValid();
	TestIsShipValidLoop();
	//TestInitialiseRandomMap();
	//TestFireShot();
	//TestCheckGameOver();

	return 0;
}


