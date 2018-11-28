#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class e_sex {MAN=1,FEMALE};

class People
{
public:
	People();
	~People();
	People(string n, int a, e_sex e);
	void print() const;
	void run() const;
private:
	string name;
	int age;
	e_sex sex;
};

class Warrior : public People
{
public:
	void attack();
	Warrior();
	~Warrior();
	Warrior(People p, double l, double a);
	void print() const;
private:
	People *people;
	double life;
	double attack_value;
};
