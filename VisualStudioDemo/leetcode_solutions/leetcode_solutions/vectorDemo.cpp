#include "vectorDemo.h"

//��1��a.assign(b.begin(), b.begin() + 3); //bΪ��������b��0~2��Ԫ�ع��ɵ���������a
//��2��a.assign(4, 2); //��aֻ��4��Ԫ�أ���ÿ��Ԫ��Ϊ2
//��3��a.back(); //����a�����һ��Ԫ��
//��4��a.front(); //����a�ĵ�һ��Ԫ��
//��5��a[i]; //����a�ĵ�i��Ԫ�أ����ҽ���a[i]����2013-12-07
//��6��a.clear(); //���a�е�Ԫ��
//��7��a.empty(); //�ж�a�Ƿ�Ϊ�գ����򷵻�ture,�����򷵻�false
//��8��a.pop_back(); //ɾ��a���������һ��Ԫ��
//��9��a.erase(a.begin() + 1, a.begin() + 3); //ɾ��a�е�1�����ӵ�0�����𣩵���2��Ԫ�أ�Ҳ����˵ɾ����Ԫ�ش�a.begin()+1���𣨰�������һֱ��a.begin()+         3������������
//��10��a.push_back(5); //��a�����һ�����������һ��Ԫ�أ���ֵΪ5
//��11��a.insert(a.begin() + 1, 5); //��a�ĵ�1��Ԫ�أ��ӵ�0�����𣩵�λ�ò�����ֵ5����aΪ1,2,3,4������Ԫ�غ�Ϊ1,5,2,3,4
//��12��a.insert(a.begin() + 1, 3, 5); //��a�ĵ�1��Ԫ�أ��ӵ�0�����𣩵�λ�ò���3��������ֵ��Ϊ5
//��13��a.insert(a.begin() + 1, b + 3, b + 6); //bΪ���飬��a�ĵ�1��Ԫ�أ��ӵ�0�����𣩵�λ�ò���b�ĵ�3��Ԫ�ص���5��Ԫ�أ�������b+6������bΪ1,2,3,4,5,9,8         ������Ԫ�غ�Ϊ1,4,5,9,2,3,4,5,9,8
//��14��a.size(); //����a��Ԫ�صĸ�����
//��15��a.capacity(); //����a���ڴ����ܹ��������ɵ�Ԫ�ظ���
//��16��a.resize(10); //��a������Ԫ�ظ�������10��������ɾ�����򲹣���ֵ���
//��17��a.resize(10, 2); //��a������Ԫ�ظ�������10��������ɾ�����򲹣���ֵΪ2
//��18��a.reserve(100); //��a��������capacity��������100��Ҳ����˵���ڲ���a.capacity();��ʱ�򷵻�ֵ��100.���ֲ���ֻ������Ҫ��a��Ӵ������ݵ�ʱ���         �Ե������壬��Ϊ�⽫�����ڴ������������������a����������ʱ���Ի��Զ����ݣ���Ȼ���Ȼ�������ܣ� 
//��19��a.swap(b); //bΪ��������a�е�Ԫ�غ�b�е�Ԫ�ؽ��������Խ���
//��20��a == b; //bΪ�����������ıȽϲ�������!=,>=,<=,>,<

vectorDemo::vectorDemo()
{
}


vectorDemo::~vectorDemo()
{
}

int vectorDemo::getVectorValue()
{
	vector<int> vec;
	int i;

	// ��ʾ vec ��ԭʼ��С
	cout << "vector size = " << vec.size() << endl;

	// ���� 5 ��ֵ��������
	for (i = 0; i < 5; i++) {
		vec.push_back(i);
	}

	// ��ʾ vec ��չ��Ĵ�С
	cout << "extended vector size = " << vec.size() << endl;

	// ���������е� 5 ��ֵ
	for (i = 0; i < 5; i++) {
		cout << "value of vec [" << i << "] = " << vec[i] << endl;
	}

	// ����vector��򵥵�д��
	for (auto autov : vec)
	{
		cout << autov << endl;
	}

	// ʹ�õ����� iterator ����ֵ
	vector<int>::iterator v = vec.begin();
	while (v != vec.end()) {
		cout << "value of v = " << *v << endl;
		v++;
	}

	// �жϿ�,boolapha���true or false
	cout << "�����Ƿ�Ϊ�գ�" << boolalpha << vec.empty() << endl;

	// ����size�ռ��capacity�ռ�
	vector<string> v1(10);
	cout << "ռ�ÿռ�size:" << v1.size() << "ռ�ÿռ�capacity:" << v1.capacity() << endl;
	v1.push_back("aaaa");
	cout << "ռ�ÿռ�size:" << v1.size() << "ռ�ÿռ�capacity:" << v1.capacity() << endl;
	v1.push_back("bbbb");
	cout << "ռ�ÿռ�size:" << v1.size() << "ռ�ÿռ�capacity:" << v1.capacity() << endl;
	v1.push_back("cccc");
	cout << "ռ�ÿռ�size:" << v1.size() << "ռ�ÿռ�capacity:" << v1.capacity() <<  endl;
	v1.pop_back();//��Ԫ�س�ջ
	cout << "ռ�ÿռ�size:" << v1.size() << "ռ�ÿռ�capacity:" << v1.capacity() << endl;
	
	// ����Ԫ�أ�β������push_back������λ�ò���insert
	vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);

	cout << "v2 push_back ����" << endl;
	for ( auto iter_v2: v2)
		cout << iter_v2 << endl;

	vector<int>::iterator it_v2 = v2.begin();
	it_v2++;
	v2.insert(it_v2,555);

	cout << "v2 insert value" << endl;
	for (auto iter_v2 : v2)
		cout << iter_v2 << endl;

	//v2.insert(it_v2, 4, 0);//insert 4 zero element at iterator it_v2
	//v2.insert(it_v2, v2.begin(), v2.end());// insert the whole v2

	// delete element
	vector<int> v3(4, 555);
	for (auto iter_v3 : v3)
		cout << iter_v3 << endl;
	// push to stack ,pop from statck top
	//v3.push_back(222);
	//v3.pop_back();
	for (auto iter_v3 : v3)
		cout << iter_v3 << endl;

	// delete any one element
	v3.erase(v3.begin());
	for (auto iter_v3 : v3)
		cout << iter_v3 << endl;
	// get element
	cout << v3[1] << endl;
	cout << v3.at(1) << endl;

	// delete the whole vector
	v3.erase(v3.begin(), v3.end());

	//�㷨
	vector<int> v8;
	v8.push_back(1);
	v8.push_back(5);
	v8.push_back(4);
	v8.push_back(2);
	v8.push_back(3);
	for (vector<int>::iterator iter = v8.begin(); iter != v8.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	reverse(v8.begin(), v8.end());//������Ҫ#include<algorithm>
	for (vector<int>::iterator iter = v8.begin(); iter != v8.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	sort(v8.begin(), v8.end()); //����
	for (vector<int>::iterator iter = v8.begin(); iter != v8.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	//��������ȽϺ������ɽ��н�������
	//sort(v8.begin(), v8.end(), 0); //����
	for (vector<int>::iterator iter = v8.begin(); iter != v8.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	//��ά����
	cout << "********��ά����********" << endl;
	vector<vector<int>> v9;
	vector<int> v9_0(3, 4);
	vector<int> v9_1(3, 6);
	v9.push_back(v9_0);
	v9.push_back(v9_1);
	for (int i = 0; i < v9.size(); i++)
	{
		for (int j = 0; j < v9[0].size(); j++)
			cout << v9[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	return 0;
}
