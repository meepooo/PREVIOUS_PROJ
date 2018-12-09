package com.dgns.pracdemo;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

/*
 * 使用HaspMap完成遍历
 * 1.使用mapSet
 * 2.使用entrySet
 */
public class HashMapDemo {
	public static void main(String[] args) {
		/*
		 * 使用父类Map对象初始化HashMap实例
		 */
		Map<String,Stud> map = new HashMap<String,Stud>();
		
		Stud stu1 = new Stud(18,"张三");
		Stud stu2 = new Stud(19,"李四");
		Stud stu3 = new Stud(20,"王五");
		Stud stu4 = new Stud(18,"赵六");
		/*
		 * put:映射功能
		 * 重复key插入不进去
		 */
		map.put("001", stu1);
		map.put("002", stu2);
		map.put("003", stu3);
		map.put("001", stu1);
		
		System.out.println(map.get("001"));
		System.out.println(map.size());
		
		/*
		 * 遍历：keySet()方法
		 */
		if(1==0){
			Set<String> keys = map.keySet();
			for(String key : keys){
				System.out.println(key);
				System.out.println(map.get(key));
			}
		}
		
		/*
		 * 遍历：entrySet()方法
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