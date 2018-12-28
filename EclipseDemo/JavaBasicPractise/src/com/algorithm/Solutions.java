package com.algorithm;

public class Solutions {
	
	// ¶ş·Ö²éÕÒ
	public static boolean BinarySearch(int[] a, int b) {
		int begin=0;
		int end=a.length-1;
		int mid=a.length/2;
		while(end>begin) {
			System.out.println(begin+","+mid+","+end);
			if(b>a[mid]) {
				begin=mid+1;
				mid=(end-begin+1)/2;
			}
			else if (b<a[mid]) {
				end=mid-1;
				mid=(end-begin-1)/2;
			}
			else {
				return true;
			}
		}
		
		return false;
	}
}
