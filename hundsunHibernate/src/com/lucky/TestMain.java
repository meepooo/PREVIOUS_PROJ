package com.lucky;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

/*
 * c3p0
 */
public class TestMain {

	public static void main(String[] args) {
		test1();
	}
	
	public static void test1() {
		Configuration config = new Configuration().configure();
		
		SessionFactory sessionFactory = config.buildSessionFactory();
		
		Session session = sessionFactory.openSession();
		
		Transaction transaction = session.beginTransaction();
		
		User user = new User();
		user.setId(200);
		user.setName("wanggj2");
		
		session.save(user);
		
		transaction.commit();
		
		session.close();
		sessionFactory.close();
	}

}
