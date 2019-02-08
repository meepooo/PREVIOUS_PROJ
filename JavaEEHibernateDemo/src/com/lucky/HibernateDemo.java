package com.lucky;

import java.util.List;

import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;
import org.junit.Test;

public class HibernateDemo {
	//插入
	@Test
	public void demo() {
		//1.加载核心配置文件
		Configuration conf = new Configuration();
		conf.configure();
		
		//2.创建一个sessionFactory
		SessionFactory sessionFactory = conf.buildSessionFactory();		
		
		//3.连接
		Session session = sessionFactory.openSession();
		
		//4.开启事务
		Transaction transaction = session.beginTransaction();	
		
		User user = new User();
		user.setId(100);
		user.setName("123");
		
		System.out.println(user.getId());
		
		//也可以用saveorupdate方法
		session.save(user);
		
		transaction.commit();
		
		//5.释放资源
		session.close();
		sessionFactory.close();
		
	}
	
	//查询
	@Test
	public void demo2() {
		//1.加载核心配置文件
		Configuration conf = new Configuration();
		conf.configure();
		
		//2.创建一个sessionFactory
		SessionFactory sessionFactory = conf.buildSessionFactory();		
		
		//3.连接
		Session session = sessionFactory.openSession();
		
		//4.开启事务
		Transaction transaction = session.beginTransaction();	
		
		//get方法查询
		User user = session.get(User.class, 100);
		System.out.println(user);
		
		//load方法查询，懒加载
		User user1 = session.load(User.class, 3);
		System.out.println(user1);
		transaction.commit();
		
		//5.释放资源
		session.close();
		sessionFactory.close();
	}
	
	//删除
	@Test
	public void demo3() {
		//1.加载核心配置文件
		Configuration conf = new Configuration();
		conf.configure();
		
		//2.创建一个sessionFactory
		SessionFactory sessionFactory = conf.buildSessionFactory();		
		
		//3.连接
		Session session = sessionFactory.openSession();
		
		//4.开启事务
		Transaction transaction = session.beginTransaction();	
		
		//删除
		User user = new User();
		user.setId(100);
		
		//先get再删除，也行
		
		session.delete(user);
		
		transaction.commit();
		//5.释放资源
		session.close();
		sessionFactory.close();
	}
	
	//查询所有
	@Test
	public void demo4() {
		//1.加载核心配置文件
		Configuration conf = new Configuration();
		conf.configure();
		
		//2.创建一个sessionFactory
		SessionFactory sessionFactory = conf.buildSessionFactory();		
		
		//3.连接
		Session session = sessionFactory.openSession();
		
		//4.开启事务
		Transaction transaction = session.beginTransaction();	
		
		//查询所有，User一定要写对象名
		Query query = session.createQuery("from User");
		List<User> list = query.list();
		for(User user : list) {
			System.out.println(user);
		}	
		
		//查询所有
		SQLQuery sqlQuery = session.createSQLQuery("select * from user");
		List<Object> sqllist = sqlQuery.list();
		for(Object obj: sqllist) {
			System.out.println(obj.toString());
		}
		
		
		transaction.commit();
		//5.释放资源
		session.close();
		sessionFactory.close();
	}
}
