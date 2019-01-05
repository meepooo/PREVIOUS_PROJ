package demo.base;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.HBaseAdmin;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.ResultScanner;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.util.Bytes;
import org.junit.Test;


/*
 * ע�⣺��Ҫ��hamcrest-core-1.3.jar��
 */
public class TestHBase {

	@Test
	public void testCreateTable() throws Exception{
		//������
		//����ZooKeeper��ַ
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "172.16.26.111");
		
		//�õ�һ��HBase�Ŀͻ���
		HBaseAdmin client = new HBaseAdmin(conf);
		
		//���ã���������˼��������
		//1��ָ�����������
		HTableDescriptor htd = new HTableDescriptor(TableName.valueOf("mytable"));
		
		//2��ָ������
		htd.addFamily(new HColumnDescriptor("info"));
		htd.addFamily(new HColumnDescriptor("grade"));
		
		//������
		client.createTable(htd);
		
		//�رտͻ���
		client.close();
	}
	
	@Test
	public void testPutData() throws Exception{
		//��������
		//����ZooKeeper��ַ
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "172.16.26.111");		
		
		//�õ�һ���ͻ���
		HTable client = new HTable(conf, "mytable");
		
		//����һ��Put����һ������
		Put put = new Put(Bytes.toBytes("id001"));
		
		//ָ���е�ֵ
		/*
		put.addColumn(family,   ���������
		               qualifier,  �е�����
		               value)   ֵ
		*/
		put.addColumn(Bytes.toBytes("info"), Bytes.toBytes("name"), Bytes.toBytes("Tom"));
		
		// һ�β��������¼client.put(List);
		
		client.put(put);
		
		client.close();
	}
	
	@Test
	public void testGetData() throws Exception{
		//��ѯ����:ָ��Rowkey
		//����ZooKeeper��ַ
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "172.16.26.111");		
		
		//�õ�һ���ͻ���
		HTable client = new HTable(conf, "mytable");
		
		//����һ��Get����
		Get get = new Get(Bytes.toBytes("id001"));
		
		//ִ�в�ѯ: �൱��  select * from mytable where rowkey=???
		Result r = client.get(get);
		
		//���:ע�⣺HBase�У�û�����ݵ����ͣ��������Ͷ��Ƕ�����
		String name = Bytes.toString(r.getValue(Bytes.toBytes("info"), Bytes.toBytes("name")));
		System.out.println("�����ǣ�" + name);
		
		client.close();
	}

	@Test
	public void testScanData() throws Exception{
		//��ѯ����
		//����ZooKeeper��ַ
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "172.16.26.111");		
		
		//�õ�һ���ͻ���
		HTable client = new HTable(conf, "mytable");
		
		//����һ��ɨ����
		Scan scan = new Scan();
		//��������scan.setFilter(filter)
		
		//ͨ��ɨ������ѯ���е�����
		//�൱�ڣ�JDBC��ResultSet
		ResultScanner rs = client.getScanner(scan);
		
		//���
		for(Result r:rs){
			String name = Bytes.toString(r.getValue(Bytes.toBytes("info"), Bytes.toBytes("name")));
			System.out.println("�����ǣ�" + name);			
		}
		
		client.close();
	}
}



























