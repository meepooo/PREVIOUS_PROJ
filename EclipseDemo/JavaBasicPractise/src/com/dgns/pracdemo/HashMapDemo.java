package com.dgns.pracdemo;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

/*
 * ʹ��HaspMap��ɱ���
 * 1.ʹ��mapSet
 * 2.ʹ��entrySet
 */
public class HashMapDemo {
	public static void main(String[] args) {
		/*
		 * ʹ�ø���Map�����ʼ��HashMapʵ��
		 */
		Map<String,Stud> map = new HashMap<String,Stud>();
		
		Stud stu1 = new Stud(18,"����");
		Stud stu2 = new Stud(19,"����");
		Stud stu3 = new Stud(20,"����");
		Stud stu4 = new Stud(18,"����");
		/*
		 * put:ӳ�书��
		 * �ظ�key���벻��ȥ
		 */
		map.put("001", stu1);
		map.put("002", stu2);
		map.put("003", stu3);
		map.put("001", stu1);
		
		System.out.println(map.get("001"));
		System.out.println(map.size());
		
		/*
		 * ������keySet()����
		 */
		if(1==0){
			Set<String> keys = map.keySet();
			for(String key : keys){
				System.out.println(key);
				System.out.println(map.get(key));
			}
		}
		
		/*
		 * ������entrySet()����
		 */
		Set<Map.Entry<String, Stud>> entrys = map.entrySet();
		for(Map.Entry<String, Stud> entry : entrys){
			System.out.println(entry.getKey());
			System.out.println(entry.getValue());
		}
	}
}

class Stud{
	private int age;
	private String name;
	
	@Override
	public String toString(){
		return name+":"+age;
	}
	public Stud(int age, String name){
		this.age = age;
		this.name = name;
	}
}