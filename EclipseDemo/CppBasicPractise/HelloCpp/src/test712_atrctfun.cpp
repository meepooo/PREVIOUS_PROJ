#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct polar
{
	double distance;
	double agnle;
};

struct rect
{
	double x;
	double y;
};

int test712()
{
	rect rplace;
	polar pplace;

	cout << "Enter the x and y values:" ;

	while(cin >> rplace.x >> rplace.y)
	{
		cout << "Next two numbers (q to quit):" ;
	}

	return 0;
}
