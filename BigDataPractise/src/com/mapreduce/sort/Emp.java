package com.mapreduce.sort;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.WritableComparable;

public class Emp implements WritableComparable<Emp> {

	@Override
	public int compareTo(Emp o) {
		if (this.deptno > o.getDeptno())
			return 1;
		else if (this.deptno < o.getDeptno())
			return -1;
		else {
			if(this.sal>o.getSal())
				return 1;
			else
				return -1;
		}
	}

	@Override
	public void readFields(DataInput input) throws IOException {
		// 实现反序列化
		// InputStream中读取对象
		input.readInt();
		input.readUTF();
		input.readUTF();
		input.readInt();
		input.readUTF();
		input.readInt();
		input.readInt();
		input.readInt();
	}

	@Override
	public void write(DataOutput output) throws IOException {
		// 实现序列化
		// OutputStream
		output.writeInt(empno);
		output.writeBytes(ename);
		output.writeBytes(job);
		output.writeInt(mgr);
		output.writeBytes(hiredate);
		output.writeInt(sal);
		output.writeInt(comm);
		output.writeInt(deptno);
	}

	@Override
	public String toString() {
		return "Emp [empno=" + empno + ", ename=" + ename + ", sal=" + sal + ", deptno=" + deptno + "]";
	}

	private int empno;
	private String ename;
	private String job;
	private int mgr;
	private String hiredate;
	private int sal;
	private int comm;
	private int deptno;

	public int getEmpno() {
		return empno;
	}

	public void setEmpno(int empno) {
		this.empno = empno;
	}

	public String getEname() {
		return ename;
	}

	public void setEname(String ename) {
		this.ename = ename;
	}

	public String getJob() {
		return job;
	}

	public void setJob(String job) {
		this.job = job;
	}

	public int getMgr() {
		return mgr;
	}

	public void setMgr(int mgr) {
		this.mgr = mgr;
	}

	public String getHiredate() {
		return hiredate;
	}

	public void setHiredate(String hiredate) {
		this.hiredate = hiredate;
	}

	public int getSal() {
		return sal;
	}

	public void setSal(int sal) {
		this.sal = sal;
	}

	public int getComm() {
		return comm;
	}

	public void setComm(int comm) {
		this.comm = comm;
	}

	public int getDeptno() {
		return deptno;
	}

	public void setDeptno(int deptno) {
		this.deptno = deptno;
	}

}
