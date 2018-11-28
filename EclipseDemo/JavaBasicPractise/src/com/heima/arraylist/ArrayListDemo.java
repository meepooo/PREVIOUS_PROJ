package com.heima.arraylist;

import java.awt.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.ListIterator;

public class ArrayListDemo {
	public static void main(String[] args) {
		ArrayList<String> array = new ArrayList<String>();

		array.add("hello");
		array.add("world!");
		array.add("ÄãºÃ");
		array.add("ÊÀ½ç");

		System.out.println(array);

		String str = array.get(0);
		System.out.println(str);
		System.out.println(array.size());
		System.out.println(array.remove("hell"));

		ListIterator<String> iter = array.listIterator();
		Iterator<String> iter1 = array.iterator();

		System.out.println("ListIterator:");
//		for (int i = 0; i < array.size(); i++) {
//			System.out.println(array.get(i));
//		}
		
		while (iter.hasNext()) {
			System.out.println(iter.next());
		}

		System.out.println("\nIterator:");
		while (iter1.hasNext()) {
			System.out.println(iter1.next());
		}

		List list = new List();
		list.add("we ");
		list.add("are ");
		list.add("one!");

		System.out.println(list.getItem(0));
	}
}
