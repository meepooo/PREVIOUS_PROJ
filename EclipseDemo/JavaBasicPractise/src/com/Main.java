package com;

/**
 * @author lixin on 2018/9/24.
 */
public class Main {

 public static void main(String[] args) {

        PlalindromeString ps = new PlalindromeString();

        String[] testStrArr = new String[] {
 "abcdcef",
 "adaelele",
 "cabadabae",
 "aaaabcdefgfedcbaa",
 "aaba",
 "aaaaaaaaa"
        };

 for(String str : testStrArr) {
            System.out.println(String.format("ԭ�ִ� : %s", str));
            System.out.println(String.format("����Ĵ� : %s", ps.findLongestPlalindromeString(str)));
            System.out.println();
        }

    }

}