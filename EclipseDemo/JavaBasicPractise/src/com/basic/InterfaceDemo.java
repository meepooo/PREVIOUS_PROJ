package com.basic;

public class InterfaceDemo {
	public static void main(String[] args) {
		// Animal a = new Animal();
/*		Dog d = new Dog("¶þ¹þ");
		d.eat();
		d.run();
		d.sex();*/
		
		Animal animal = new Dog("½ðÃ«");
		animal.sex();
		
		Action action = new Dog("¶þ¹þ");
		action.eat();
		action.run();
		
		Dog d = new Dog("");
		d.Animal();
	}
}

abstract class Animal {
	private String name;

	abstract public void sex();
	
	Animal(){	
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
}

class Dog extends Animal implements Action {
	private String name;

	@Override
	public void eat() {
		System.out.println("¹·¿Ð¹ÇÍ·");
	}

	@Override
	public void run() {
		System.out.println("¹·ÅÙµØ");
	}

	Dog(String str) {
		this.setName(str);
	}

	@Override
	public void sex() {
		System.out.println("¹·Æï¹·");
	}
	
	@Override
	public void Animal(){
		
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
}

class Cat extends Animal implements Action {

	@Override
	public void sex() {
		System.out.println("Ã¨ÆïÃ¨");
	}

	@Override
	public void eat() {
		System.out.println("Ã¨³ÔÓã");
	}

	@Override
	public void run() {
		System.out.println("Ã¨ÅÀÊ÷");
	}

	@Override
	public void Animal() {
		// TODO Auto-generated method stub
		
	}

}

interface Action {
	public abstract void eat();

	void Animal();

	public abstract void run();
}
