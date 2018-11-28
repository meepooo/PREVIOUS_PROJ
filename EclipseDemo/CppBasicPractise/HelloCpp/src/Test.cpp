#include "Test.h"
#include <vector>

using namespace std;

StuInfo::StuInfo(string id, string name, string gender, int age)
{
	stuId = id;
	stuName = name;
	stuGender = gender;
	stuAge = age;
}
StuInfo::StuInfo()
{
	stuAge = 0;
}

StuInfo::~StuInfo()
{

}

void StuInfo::stuCopy(StuInfo s)
{
	stuId = s.stuId;
	stuName = s.stuName;
	stuGender = s.stuGender;
	stuAge = s.stuAge;
}

void StuInfo::stuDisplay()
{
	cout << stuId << " , " << stuName << " , " << stuGender << " , " << stuAge << endl;
}

template<typename T>
Node<T>::Node(int seq, T temp)
{
	this->t.stuCopy(temp);
	this->next = NULL;
	this->seqno = seq;
}

template<typename T>
Node<T>::Node(int seq)
{
	seqno = seq;
	next = NULL;
}

template<typename T>
Node<T>::~Node()
{
	next = NULL;
}

List::List()
{
	position = 0;
	head=NULL;
	tail=NULL;
}

List::~List()
{
	delete head;
	delete tail;
}

void List::insertNode(Node<StuInfo> *n)
{
	if (head == NULL)//insert seq first
	{
		head = n;
		tail = n;
		cout << "1" << endl;
		head->t.stuDisplay();
		cout << "end" << endl;
	}
	else
	{
		tail->next = n;
		tail = n;
		cout << "2" << endl;
	}
}

void List::deleteNode(int seq)
{
	Node<StuInfo> *p;
	p = head;
	if (head->next == NULL)
	{
		cout << "LinkList is empty!" << endl;
		return;
	}
	//遍历链表
	while (p->next != NULL && p->next->getSeq() != seq)
	{
		cout << "LinkList is empty!" << p->next->getSeq() << "," << seq << endl;
		p->next->t.stuDisplay();
		p = p->next;
	}

	if (p->next == NULL || p->next->getSeq() != seq)
	{
		cout << "not found the node!" << endl;
		return;
	}

	if (p->next == tail)//delete tail node
	{
		tail = p;
		tail->next = NULL;
	}
	else//delete other node
	{
		p->next = p->next->next;
	}
	cout << "delete the No." << seq << ": ";
	p->t.stuDisplay();
}

int List::searchNode(int seq)
{
	Node<StuInfo> *p = head;
	while (p != NULL && p->getSeq() != seq)
	{
		p = p->next;
	}

	if (p == NULL || p->getSeq() != seq)
	{
		cout << "not found the node!" << endl;
		return -1;
	}
	else
	{
		cout << "found the No." << seq << ": ";
		p->t.stuDisplay();
		return seq;
	}

	return -1;
}

void List::getNodeVal(int seq)
{
	Node<StuInfo> *p = head;
	while (p != NULL && p->getSeq() != seq)
	{
		p = p->next;
	}

	if (p == NULL || p->getSeq() != seq)
	{
		cout << "not found the node!" << endl;
		return;
	}
	else
	{
		cout << "found " << seq << endl;
		return;
	}
	return;
}

void List::setNodeVal(int seq, Node<StuInfo> n)
{
	Node<StuInfo> *inode = &n;
	Node<StuInfo> *p = head;
	while (p != NULL && p->getSeq() != seq)
	{
		p = p->next;
	}

	if (p == NULL || p->getSeq() != seq)
	{
		cout << "not found the node!" << endl;
		return;
	}
	else
	{
		cout << "change No." << seq << ": ";
		p = inode;
		p->t.stuDisplay();
		return;
	}
}

void List::displayList() const
{
	Node<StuInfo> *p=head;
	while (p != NULL)
	{
		p->t.stuDisplay();
		p = p->next;
	}
}

int swap(StuInfo &stu1, StuInfo &stu2)
{
	StuInfo stu;
	stu.stuCopy(stu1) ;
	stu1.stuCopy(stu2);
	stu2.stuCopy(stu);
	return 0;
}
//test main
//4 student objects execute display, delete, search, setval, display operation
//int main()
//{
//	cout << "hello LinkList!" << endl;
//	StuInfo stu1("1001", "张三", "男", 18);
//	StuInfo stu2("1002", "李四", "男", 19);
//
//	//swap function use reference
//	swap(stu1, stu2);
//	stu1.stuDisplay();
//	stu2.stuDisplay();
//
//	//vector usage
//	vector<double> arr={1,2,3,4,5};
//
//	//auto usage
//	for(auto i=arr.begin();i<arr.end();i++)
//	{
//		cout << *i << endl;
//	}
//
//	for(auto v:arr)
//	{
//		cout << v << endl;
//	}
//
//	cout << "end" <<endl;
//
////	List l;
////
////	Node<StuInfo> stu1(i++, StuInfo("1001", "张三", "男", 18));
////	Node<StuInfo> stu2(i++, StuInfo("1002", "李四", "男", 19));
////	Node<StuInfo> stu3(i++, StuInfo("1003", "王五", "女", 20));
////	Node<StuInfo> stu4(i++, StuInfo("1004", "赵六", "女", 21));
////	l.insertNode(&stu1);
////	l.insertNode(&stu2);
////	l.insertNode(&stu3);
////	l.insertNode(&stu4);
////	l.displayList();
////	l.deleteNode(2);
////	l.searchNode(1);
////	l.setNodeVal(1, Node<StuInfo>(1, StuInfo("1001", "张小红", "女", 22)));
////	cout << "display again" << endl;
////	l.displayList();
////	cin.get();
//	return 0;
//}
