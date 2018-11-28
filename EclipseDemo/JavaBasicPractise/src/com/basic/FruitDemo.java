package com.basic;

public class FruitDemo {
	public static void main(String[] args) {
		SupperTree s = new SupperTree();
		s.CreateFruit(new Apple());
		s.CreateFruit(new Banana());
		
		Apple a = new Apple();
		a.getcolor();
		
		Fruit f=new Apple();
		f.getcolor();
		
	}
}

class SupperTree {
	String name;
	String color;

	public void CreateFruit(Fruit f) {
		System.out.println("get a fruit");
		f.getcolor();
	}
}

interface Fruit {
	public abstract void getcolor();
}

class Apple implements Fruit {
	@Override
	public void getcolor() {
		System.out.println("green apple");
	}
}

class Banana implements Fruit {
	@Override
	public void getcolor() {
		System.out.println("yellow Banana");
	}
}
class Orange {
	Fruit f ;
}