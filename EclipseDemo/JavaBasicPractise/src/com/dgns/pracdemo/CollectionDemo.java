package com.dgns.pracdemo;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;


public class CollectionDemo {
	public static void main(String[] args) {
		Collection<String> collect = new ArrayList<String>();
		ArrayList<String> array = new ArrayList<String>();
		
		collect.add("1");
		collect.add("2");
		collect.add("3");
		collect.add("4");
		array.add("123");
		array.add("abc");
		array.add("ccc");
		
		Iterator<String> iter = collect.iterator();
		
		System.out.println(collect);
		System.out.println(array);
		
		for(String str : array){
			System.out.println(str);
		}
		
		for(String str : collect){
			System.out.println(str);
		}
		
		while(iter.hasNext()){
			System.out.println(iter.next());
		}
		
		List<String> l = new ArrayList<String>();
		l.add("ss");
		l.add("ss");
		l.add("ss");
		System.out.println(l);
		
		LinkedList<String> ll = new LinkedList<String>();
		ll.addFirst(null);
		ll.add("1");
		ll.add("2");
		ll.add("3");
		ll.add("4");
		ll.addLast("END");
		
		System.out.println(ll);

		Iterator<String> it = ll.iterator();
		
		for(;it.hasNext();){
			System.out.println(it.next());
		}
	}
}
