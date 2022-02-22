/**
 * Exercice 5.7
 * (exercice de groupe)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

public class App {
    static class A{
        public A(){}
        public void test(){
            a();
            b();
        }
        public void a(){
            System.out.println("Function A.a");
        }
        public void b(){
            System.out.println("Function A.b");
        }

    }
    static class B{
        private A obj;
        public void test(){
            obj.test();
        }
        public B(){
            this.obj = new A(); 
        }
    }
    public static void main(String[] args){
        B objB = new B();
        objB.test();
    }
}