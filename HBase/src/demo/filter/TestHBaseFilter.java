package demo.filter;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.ResultScanner;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.filter.ColumnPrefixFilter;
import org.apache.hadoop.hbase.filter.CompareFilter.CompareOp;
import org.apache.hadoop.hbase.filter.FilterList;
import org.apache.hadoop.hbase.filter.FilterList.Operator;
import org.apache.hadoop.hbase.filter.MultipleColumnPrefixFilter;
import org.apache.hadoop.hbase.filter.RegexStringComparator;
import org.apache.hadoop.hbase.filter.RowFilter;
import org.apache.hadoop.hbase.filter.SingleColumnValueFilter;
import org.apache.hadoop.hbase.util.Bytes;
import org.junit.Test;

/*
 * �����Ĺ�����
 * 1����ֵ��������  select * from emp where sal=3000;
 * 2������ǰ׺����������ѯԱ��������   select ename from emp;
 * 3���������ǰ׺����������ѯԱ����������нˮ   select ename,sal from emp;
 * 4���м���������ͨ��Rowkey��ѯ������ͨ��Get��ѯ����
 * 5����ϼ�����������ѯ���ݣ�where ����1 and��or�� ����2
 */
public class TestHBaseFilter {

	@Test
	public void testSingleColumnValueFilter() throws Exception{
		//ָ����������Ϣ: ZooKeeper
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "192.168.157.111");
		
		//�ͻ���
		HTable table = new HTable(conf, "emp");		
		
		//����һ����ֵ������
		SingleColumnValueFilter filter = new SingleColumnValueFilter(Bytes.toBytes("empinfo"),     //����
				                                                     Bytes.toBytes("sal"),  //����
				                                                     CompareOp.EQUAL,  //�Ƚ������
				                                                     Bytes.toBytes("3000"));     //ֵ
		
		//�ѹ���������ɨ����
		Scan scan = new Scan();
		scan.setFilter(filter);
		
		//��ѯ����
		ResultScanner rs = table.getScanner(scan);
		for(Result r:rs){
			String name = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("ename")));
			System.out.println(name);
		}
		
		table.close();
	}
	
	
	@Test
	public void testColumnPrefixFilter() throws Exception{
		//ָ����������Ϣ: ZooKeeper
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "192.168.157.111");
		
		//�ͻ���
		HTable table = new HTable(conf, "emp");	
		
		//��������ǰ׺������
		ColumnPrefixFilter filter = new ColumnPrefixFilter(Bytes.toBytes("ename"));
		
		//�ѹ���������ɨ����
		Scan scan = new Scan();
		scan.setFilter(filter);
		
		//��ѯ���ݣ������ֻ��Ա��������
		ResultScanner rs = table.getScanner(scan);
		for(Result r:rs){		
			//��ȡ������нˮ
			String name = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("ename")));
			String sal = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("sal")));
			
			System.out.println(name+"\t"+sal);
		}
		
		table.close();
	}
	
	@Test
	public void testMultipleColumnPrefixFilter() throws Exception{
		//ָ����������Ϣ: ZooKeeper
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "192.168.157.111");
		
		//�ͻ���
		HTable table = new HTable(conf, "emp");	
	
		//����һ����ά���ֽ����ݣ�����������
		byte[][] names = {Bytes.toBytes("ename"),Bytes.toBytes("sal")};
		
		//����������ǰ׺����������ѯ��������нˮ
		MultipleColumnPrefixFilter filter = new MultipleColumnPrefixFilter(names);
		
		//�ѹ���������ɨ����
		Scan scan = new Scan();
		scan.setFilter(filter);
		
		//��ѯ���ݣ������ֻ��Ա��������
		ResultScanner rs = table.getScanner(scan);
		for(Result r:rs){		
			//��ȡ������нˮ
			String name = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("ename")));
			String sal = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("sal")));
			
			System.out.println(name+"\t"+sal);
		}
		
		table.close();		
	}
	
	@Test
	public void testRowFilter() throws Exception{
		//ָ����������Ϣ: ZooKeeper
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "192.168.157.111");
		
		//�ͻ���
		HTable table = new HTable(conf, "emp");	
		
		//����һ��RowFilter �м�������: ��ѯrowkey=7839��Ա��
		RowFilter filter = new RowFilter(CompareOp.EQUAL,   //�Ƚ������
				                         new RegexStringComparator("7839")); //�м���ֵ��ʹ�õ�һ��������ʽ
		//�ѹ���������ɨ����
		Scan scan = new Scan();
		scan.setFilter(filter);
		
		//��ѯ���ݣ������ֻ��Ա��������
		ResultScanner rs = table.getScanner(scan);
		for(Result r:rs){		
			//��ȡ������нˮ
			String name = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("ename")));
			String sal = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("sal")));
			
			System.out.println(name+"\t"+sal);
		}
		
		table.close();			
	}
	
	@Test
	public void testFilter() throws Exception{
		//�������������
		//��������ѯ���ʵ���3000��Ա������
		/*
		 * ��һ������������ֵ������
		 * �ڶ���������������ǰ׺������
		 */
		
		//ָ����������Ϣ: ZooKeeper
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "192.168.157.111");
		
		//�ͻ���
		HTable table = new HTable(conf, "emp");	
				
		//����һ����ֵ������
		SingleColumnValueFilter filter1 = new SingleColumnValueFilter(Bytes.toBytes("empinfo"),     //����
				                                                     Bytes.toBytes("sal"),  //����
				                                                     CompareOp.EQUAL,  //�Ƚ������
				                                                     Bytes.toBytes("3000"));     //ֵ
		//��������ǰ׺������
		ColumnPrefixFilter filter2 = new ColumnPrefixFilter(Bytes.toBytes("ename"));		
		
		//����һ��FilterList
		FilterList list = new FilterList(Operator.MUST_PASS_ALL);  //�൱�� and
		//FilterList list = new FilterList(Operator.MUST_PASS_ONE); // �൱��or
		list.addFilter(filter1);
		list.addFilter(filter2);
		
		//�ѹ���������ɨ����
		Scan scan = new Scan();
		scan.setFilter(list);
		
		//��ѯ���ݣ������ֻ��Ա��������
		ResultScanner rs = table.getScanner(scan);
		for(Result r:rs){		
			//��ȡ������нˮ
			String name = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("ename")));
			String sal = Bytes.toString(r.getValue(Bytes.toBytes("empinfo"), Bytes.toBytes("sal")));
			
			System.out.println(name+"\t"+sal);
		}
		
		table.close();		
	}
}


















