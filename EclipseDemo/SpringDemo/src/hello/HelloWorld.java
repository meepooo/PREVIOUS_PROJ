package hello;

public class HelloWorld {
    private String name;
    
    public HelloWorld() {
        System.out.println("HelloWorld constructor...");
    }
    
    public HelloWorld(String name) {
       System.out.println("HelloWorld constructor with paramter...");
        this.name = name;
    }
     
    public void setName(String name) {
        System.out.println("HelloWorld setName...");
         this.name = name;
    }
     
   public void hello() {
         System.out.println("hello: " + this.name);
     }
}