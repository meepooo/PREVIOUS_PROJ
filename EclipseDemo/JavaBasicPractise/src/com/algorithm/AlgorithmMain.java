package com.algorithm;

import java.util.Arrays;

public class AlgorithmMain {
	public static void main(String[] args) {
		int[] a = {1,2,3,4,5,100,10};
		Arrays.sort(a);
		
		for(int i:a)
			System.out.println(i);
		
		Solutions.BinarySearch(a, 5);
//		System.out.println(Solutions.BinarySearch(a, 5));
	}
}
