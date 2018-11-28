//single direction link list
//the data of head is null
//the pointer of tail is null
#include <iostream>
#include <string>
using namespace std;

//class datatype, record the student's info
class StuInfo
{
public:
	StuInfo(string id, string name, string gender, int age);
	StuInfo();
	~StuInfo();
	void stuCopy(StuInfo s);
	void stuDisplay();
private:
	string stuId;
	string stuName;
	string stuGender;
	int stuAge;
};

//node of link list,include counter, the next pointer,and student data.
template<typename T>
class Node
{
public:
	Node<T>(int seq, T temp);
	Node<T>(int seq);//for head porinter only
	~Node<T>();
	int getSeq();
	T t;
	Node *next;
private:
	int seqno;
};

//µ•œÚ¡¥±Ì Unidirectional linked list
class List
{
public:
	List();
	~List();
	void insertNode(Node<StuInfo> *n);//link list tail insert
	void deleteNode(int seq);//delete anyone node
	int searchNode(int seq);//get anyone node
	void getNodeVal(int po);
	void setNodeVal(int seq, Node<StuInfo> n);//set anyone node
	void displayList() const;//display the whole link list
private:
	Node<StuInfo> *head, *tail;
	int position;
};

template<typename T>
inline int Node<T>::getSeq()
{
	return seqno;
}
