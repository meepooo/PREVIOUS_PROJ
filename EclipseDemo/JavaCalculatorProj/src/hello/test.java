package hello;

import java.util.ArrayList;

public class test {
	public test() {
		
	}

	void sayHello() {
		System.out.println("Hello!");
		System.out.println("This is a test method!");
		System.out.println("Author:Lucky");
		int x=5;
		System.out.println(times(x));
	}
	
	int times(int x) {
		return x*2;
	}
	
	void arrayTest() {
		ArrayList array = new ArrayList();
		int iA = 11 ;
		double dA = 22.22;
		String sA = new String();
		sA = "hello Lucky";
		
		array.add(sA);
		array.add(iA);
		array.add(dA);
		
		System.out.println(array.get(0));
		System.out.println(array.get(1));
		System.out.println(array.get(2));
	}
}
