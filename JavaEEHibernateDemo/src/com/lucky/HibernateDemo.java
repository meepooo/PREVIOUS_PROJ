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
	//����
	@Test
	public void demo() {
		//1.���غ��������ļ�
		Configuration conf = new Configuration();
		conf.configure();
		
		//2.����һ��sessionFactory
		SessionFactory sessionFactory = conf.buildSessionFactory();		
		
		//3.����
		Session session = sessionFactory.openSession();
		
		//4.��������
		Transaction transaction = session.beginTransaction();	
		
		User user = new User();
		user.setId(100);
		user.setName("123");
		
		System.out.println(user.getId());
		
		//Ҳ������saveorupdate����
		session.save(user);
		
		transaction.commit();
		
		//5.�ͷ���Դ
		session.close();
		sessionFactory.close();
		
	}
	
	//��ѯ
	@Test
	public void demo2() {
		//1.���غ��������ļ�
		Configuration conf = new Configuration();
		conf.configure();
		
		//2.����һ��sessionFactory
		SessionFactory sessionFactory = conf.buildSessionFactory();		
		
		//3.����
		Session session = sessionFactory.openSession();
		
		//4.��������
		Transaction transaction = session.beginTransaction();	
		
		//get������ѯ
		User user = session.get(User.class, 100);
		System.out.println(user);
		
		//load������ѯ��������
		User user1 = session.load(User.class, 3);
		System.out.println(user1);
		transaction.commit();
		
		//5.�ͷ���Դ
		session.close();
		sessionFactory.close();
	}
	
	//ɾ��
	@Test
	public void demo3() {
		//1.���غ��������ļ�
		Configuration conf = new Configuration();
		conf.configure();
		
		//2.����һ��sessionFactory
		SessionFactory sessionFactory = conf.buildSessionFactory();		
		
		//3.����
		Session session = sessionFactory.openSession();
		
		//4.��������
		Transaction transaction = session.beginTransaction();	
		
		//ɾ��
		User user = new User();
		user.setId(100);
		
		//��get��ɾ����Ҳ��
		
		session.delete(user);
		
		transaction.commit();
		//5.�ͷ���Դ
		session.close();
		sessionFactory.close();
	}
	
	//��ѯ����
	@Test
	public void demo4() {
		//1.���غ��������ļ�
		Configuration conf = new Configuration();
		conf.configure();
		
		//2.����һ��sessionFactory
		SessionFactory sessionFactory = conf.buildSessionFactory();		
		
		//3.����
		Session session = sessionFactory.openSession();
		
		//4.��������
		Transaction transaction = session.beginTransaction();	
		
		//��ѯ���У�Userһ��Ҫд������
		Query query = session.createQuery("from User");
		List<User> list = query.list();
		for(User user : list) {
			System.out.println(user);
		}	
		
		//��ѯ����
		SQLQuery sqlQuery = session.createSQLQuery("select * from user");
		List<Object> sqllist = sqlQuery.list();
		for(Object obj: sqllist) {
			System.out.println(obj.toString());
		}
		
		
		transaction.commit();
		//5.�ͷ���Դ
		session.close();
		sessionFactory.close();
	}
}
