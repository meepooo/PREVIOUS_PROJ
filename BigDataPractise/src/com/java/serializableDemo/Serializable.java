package com.java.serializableDemo;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class Serializable {
	public static void main(String[] args) throws IOException {
		Student s1 = new Student("lilei", 18);
		Student s2 = new Student("hanmeimei", 17);
		
		FileOutputStream fos = new FileOutputStream("t.tmp");
	    ObjectOutputStream oos = new ObjectOutputStream(fos);
	    
	    oos.writeObject(s1);
	    oos.writeObject(s2);
	    
	    oos.close();
	    fos.close();
	}
}
