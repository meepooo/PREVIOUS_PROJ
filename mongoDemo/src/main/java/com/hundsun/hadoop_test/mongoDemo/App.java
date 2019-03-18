package com.hundsun.hadoop_test.mongoDemo;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );
        
        MongoClient mongoClient = new MongoClient("139.9.2.241", 27017);        
        MongoDatabase database = mongoClient.getDatabase("test");
        System.out.println("Connect to database successfully");
        
        MongoCollection<Document> collection = database.getCollection("test");
        System.out.println("集合创建成功");
    }
}
