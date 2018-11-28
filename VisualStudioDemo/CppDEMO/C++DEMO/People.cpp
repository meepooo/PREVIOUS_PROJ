#include "People.h"



People::People()
{
	name = "无名氏";
	age = 0;
	sex = e_sex::MAN;
}


People::~People()
{
}

People::People(string n, int a, e_sex e)
{
	name = n;
	age = a;
	sex = e;
}

void People::print() const
{
	string sexname;
	(int)sex == 1 ? sexname = "man":sexname="female" ;

	//if (sex == e_sex::MAN)
	//	sexname = "man";
	//else
	//	sexname = "female";

	cout << "you have constract a people named" << name << ", a " << sexname << ", age is " << age << endl;
}

void People::run() const
{
	cout << name << " is running" << endl;
}

int main()
{
	People p("亚瑟", 18, e_sex::FEMALE);
	p.print();
	p.run();

	Warrior w(p, 1000.00, 100.00);
	w.print();
	w.People::run();
	w.run();

	string str = "你好,hello";
	const char *pch = str.c_str();
	cout << str.length() << endl;
	cout << str << endl;
	cout << *pch << endl;
	
	return 0;
}

void Warrior::attack()
{
	cout << "attack the enemy" << endl;
}

Warrior::Warrior()
{
	people = new People();
	life = 0.00;
	attack_value = 0.00;
}

Warrior::~Warrior()
{
	delete people;
}

Warrior::Warrior(People p, double l, double a)
{
	people = new People(p);
	life = l;
	attack_value = a;
}

void Warrior::print() const
{
	people->print();
	cout << "life is " << life << " and acctck is " << attack_value << endl;
}
