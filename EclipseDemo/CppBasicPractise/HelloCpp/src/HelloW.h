#include <iostream>
template <class T>
void strtest5(T &a, T &b){
	std::cout << a << "|" << b << std::endl ;
	T temp = a;
	a = b ;
	b= temp ;
}

template <class T>
T minxxx(T x,T y){
	return(x<y)?x:y;
}

template <typename T>
inline T const& Max (T const& a, T const& b)
{
    return a < b ? b:a;
}
