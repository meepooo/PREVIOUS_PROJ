#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Clock {
public:
	void showTime()
	{
		cout << hour << " " << minute << " " << second << endl;
	}
	Clock(int h, int m, int s) :hour(h), minute(m), second(s) {};
	Clock():Clock(0,0,0){};
	//Clock(const Clock& c) = delete; //delete copy constructorf
private:
	int hour;
	int minute;
	int second;
};
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void setTime(int h=0, int m=0, int s=0)
{
	cout << h << " " << m << " " << s << endl;
}
//int main()
//{
//	int x = 10, y = 100;
//	cout << x << "," << y << endl;
//
//	swap(&x, &y);
//	cout << x << "," << y << endl;
//
//	cout << pow(x, y) << endl;
//
//	vector<int> arr = { 12,30,0 };
//
//	cout << "setTime:";
//	setTime();
//	cout << "setTime:";
//	setTime(arr[0]);
//	cout << "setTime:";
//	setTime(arr[0],arr[1],arr[2]);
//
//	cout.width(12);
//	Clock myClock;
//	myClock.showTime();
//
//	Clock myClock1(myClock);
//	myClock1.showTime();
//	
//	vector<double> array={ 1.1,2.2,3.0 };
//	vector<double> array1{ 1.1,2.2 };
//	//double array[3]{ 1.2,3.3,5.5 };
//	for (auto &e : array1)
//		cout << e << endl;
//	return 0;
//}