package openlight;

public class Person {
	private void pressBotton(Light l) {
		System.out.println("CLASS PERSON pressbotton");
		l.isLight = (l.isLight + 1) % 2 ;
	}
	
	public static void main(String[] args) {
		Person p = new Person();
		Light l = new Light();
		l.showLight();
		
		p.pressBotton(l);
		l.showLight();
		
		p.pressBotton(l);
		l.showLight();
		

	}
}
