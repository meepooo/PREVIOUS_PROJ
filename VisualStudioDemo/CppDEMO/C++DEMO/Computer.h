#pragma once
#include <iostream>

using namespace std;

enum CPU_rank{ P1 = 1,P2,P3,P4,P5,P6 };
class CPU
{
public:
	CPU(CPU_rank r, int f, float v) :rank(r),frequency(f),voltage(v)	{ 		cout << "CPU structure" << endl; 	};
	~CPU() 	{		cout << "CPU destruct" << endl;	}
	void run() { cout << "CPU run" << endl; };
	void stop() { cout << "CPU stop" << endl; };
	CPU(const CPU& c) { cout << "CPU default structure" << endl; };// copy structure func
private:
	CPU_rank rank;
	int frequency;
	float voltage;
};

enum RAM_type{DDR2=2,DDR3,DDR4};
class RAM 
{
public:
	RAM(int c, RAM_type t, int f) :size(c), type(t), frequency(f) { cout << "RAM structure" << endl; };
	~RAM() { cout << "RAM destruct" << endl; };
	void run() { cout << "RAM run" << endl; };
	void stop() { cout << "RAM stop" << endl; };
	RAM(const RAM& r) { cout << "RAM default structure" << endl; };// copy structure func
private:
	int size;
	RAM_type type;
	int frequency;
};

enum CDROM_Interface{SATA,USB};
enum CDROM_Install_type{external,built_in};
class CDROM
{
public:
	CDROM(int c, CDROM_Interface t, CDROM_Install_type it) :capacity(c), interfact_type(t), inst_type(it) { cout << "CDROM structure" << endl; };
	~CDROM() { cout << "CODRM desstruct" << endl; };
	void run() { cout << "CDROM run" << endl; };
	void stop() { cout << "CDROM stop" << endl; };
	CDROM(const CDROM& m) { cout << "CDROM default structure" << endl; };// copy structure func
private:
	int capacity;
	CDROM_Interface interfact_type;
	CDROM_Install_type inst_type;
};

class Computer
{
public:
	Computer(const CPU& c, const RAM& r, const CDROM& m, int s, int b) :cpu(c), ram(r), cdrom(m), size(s), bandwidth(b) {		cout << "computer structure" << endl;	}
	~Computer() {		cout << "computer desstruct" << endl;};
	void run() { cout << "Computer run" << endl; };
	void stop() { cout << "Computer stop" << endl; };
private:
	CPU cpu;
	RAM ram;
	CDROM cdrom;
	int size;
	int bandwidth;
};

