package com.dgns.pracdemo;

public class ExceptionDemo2 {
	public static void main(String[] args) {
		int[] arr = null;
		try {
			function(arr);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void function(int[] arr) throws Exception {
		if (arr == null)
			throw new Exception("null point Exception");
		
	}
}
