package openlight;
import java.io.*;

public interface Lightin{

	public static void on() {
		System.out.println("light on");
	}
	
	public static void off() {
		System.out.println("light off");
	}
	
	public static void bright() {
		System.out.println("light bright");
	}
	
	public static void dim() {
		System.out.println("light dim");
	}
}
