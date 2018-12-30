package com.mapreduce.sort;

public class Student implements Comparable<Student>{
	public int stuID;
	public String stuName;
	public int getStuAge() {
		return stuAge;
	}

	public void setStuAge(int stuAge) {
		this.stuAge = stuAge;
	}
	public int stuAge;
	
	@Override
	public int compareTo(Student o) {
		if(this.stuAge>o.stuAge)
			return 1;
		else
			return -1;
	}
		
	@Override
	public String toString() {
		return this.stuID + ":"+ this.stuName + ","+this.stuAge;
	}

	public int getStuID() {
		return stuID;
	}
	public void setStuID(int stuID) {
		this.stuID = stuID;
	}
	public String getStuName() {
		return stuName;
	}
	public void setStuName(String stuName) {
		this.stuName = stuName;
	}
}
