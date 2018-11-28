#include "vecDemo.h"

using namespace std;

//initialization
vecDemo<double>::vecDemo() :vec_var(LEN)
{
	d_var[0] = 1.1;
	d_var[1] = 2.1;
	d_var[2] = 3.1;
	d_var[3] = 4.1;

	vec_var[0] = 1.1;
	vec_var[1] = 2.1;
	vec_var[2] = 3.1;
	vec_var[3] = 4.1;

	arr_var = { 1.1, 2.2, 3.4, 5.6 };
}

template <typename T>
vecDemo<T>::vecDemo():vec_var(LEN)
{
}

template <typename T>
vecDemo<T>::~vecDemo()
{
}

template <typename T>
void vecDemo<T>::printVar()
{
	using namespace std;
	cout << "double variable" << endl;
	cout << d_var[0] << endl << d_var[1] << endl << d_var[2] << endl << d_var[3] << endl << endl;
	cout << "vector variable" << endl;
	cout << vec_var[0] << endl << vec_var[1] << endl << vec_var[2] << endl << vec_var[3] << endl << endl;
	cout << "array variable" << endl;
	cout << arr_var[0] << endl << arr_var[1] << endl << arr_var[2] << endl << arr_var[3] << endl << endl;
}

//int main()
//{
//	vecDemo<double> vecD;
//
//	vecD.printVar();
//	cin.get();
//	return 0;
//}