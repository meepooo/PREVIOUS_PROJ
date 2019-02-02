package jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/*
 * ������
 * 1����ȡConnection
 * 2���ͷ���Դ
 */
public class JDBCUtils {

	//����Hive��Driver
	private static String driver = "org.apache.hive.jdbc.HiveDriver";
	//Oracle: oracle.jdbc.OracleDriver
	
	//URL��ַ
	private static String url = "jdbc:hive2://172.16.26.111:10000/default";
	
	//ע��Driver
	static{
		try {
			Class.forName(driver);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	//��ȡ����
	public static Connection getConnection(){
		try{
			return DriverManager.getConnection(url);
		}catch(Exception ex){
			ex.printStackTrace();
		}
		return null;
	}
	
	//�ͷ���Դ
	//���⣺�ܲ���ͨ��Java����ȥ��ԤGC��
	public static void release(Connection conn,Statement st,ResultSet rs){
		if(rs != null){
			try {
				rs.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}finally{
				rs = null;
			}
		}
		if(st != null){
			try {
				st.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}finally{
				st = null;
			}
		}
		if(conn != null){
			try {
				conn.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}finally{
				conn = null;
			}
		}
	}
	
}































