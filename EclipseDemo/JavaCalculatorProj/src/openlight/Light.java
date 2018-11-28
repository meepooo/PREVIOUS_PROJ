package openlight;

import java.io.*;

public class Light {
	public static int isLight = 0 ;
	
	private void openLight() {
		System.out.println("CLASS LIGHT openlight");
		this.isLight = 1;
	}
	
	private void closeLight() {
		System.out.println("CLASS LIGHT closelight");
		this.isLight = 0;
	}
	
	public void showLight() {
		if (isLight == 1) {
			this.openLight();
			System.out.println("Light is on!");
		}
		else if (isLight == 0) {
			this.closeLight();
			System.out.println("Light is off!");
		}
	}
}
