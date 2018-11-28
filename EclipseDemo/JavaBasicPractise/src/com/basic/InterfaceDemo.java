package com.basic;

public class InterfaceDemo {
	public static void main(String[] args) {
		// Animal a = new Animal();
/*		Dog d = new Dog("����");
		d.eat();
		d.run();
		d.sex();*/
		
		Animal animal = new Dog("��ë");
		animal.sex();
		
		Action action = new Dog("����");
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
		System.out.println("���й�ͷ");
	}

	@Override
	public void run() {
		System.out.println("���ٵ�");
	}

	Dog(String str) {
		this.setName(str);
	}

	@Override
	public void sex() {
		System.out.println("���ﹷ");
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
		System.out.println("è��è");
	}

	@Override
	public void eat() {
		System.out.println("è����");
	}

	@Override
	public void run() {
		System.out.println("è����");
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
