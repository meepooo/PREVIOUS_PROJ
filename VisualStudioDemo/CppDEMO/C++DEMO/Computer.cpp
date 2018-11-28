#include "Computer.h"
#include <iostream>
using namespace std;
int main()
{
	CPU myCpu(P4,2,2.4);
	RAM myRam(8,DDR4,2);
	CDROM myCdRom(10,SATA,external);
	Computer myComputer(myCpu,myRam,myCdRom,1,2);
	cout << "program end" << endl;
	return 0;
}
