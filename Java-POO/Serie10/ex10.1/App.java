import java.util.*;

public class App{

    static class A {}
    static class B extends A{ }
    static class C extends A{ }
    static class D extends B{ }
    static class E extends B{ }
    static class F extends C{ }
    static class G extends C{ }
    static class H extends G{ }
    static class I extends G{ }

    public static void main(String[] args) {
    // covariance (classe fille est class mère)
        Box<? extends B> bd = new Box<D>( new D() ); // D est un B donc c'est bon
        //D d = bd.get(); // le get() retourne un B et B n'est pas un D (par contre D est un B)
        B b = bd.get(); // le get() retourne un B c'est bon
        //bd.set( new E() ); //  pas de set() en covariance

    // contravariance (classe mère est classe fille)
        Box<? super B> bd2 = new Box<A>( new C() ); // C est un A donc c'est bon
        //D d = bd2.get();  // pas de get() en contravariance
        //B b = bd2.get();  // pas de get() en contravariance
        bd2.set( new D() ); // le set prend un B en paramètre. Ici D est un B donc c'est bon
 
    // invariance
        Box<A> aa = new Box<A>( new B() ); // A est un B
        //Box<B> bd3 = new Box<D>( new D() ); // D n'est pas un B (invariance pas de extends ou de super)

    // covariance                                     // fille est mère
        //Box<? extends C> ca = new Box<A>( new G() ); // A n'est pas un C (c'est de la contravariance)
        Box<? extends C> cg = new Box<G>( new I() ); // G est un C et I est un G donc c'est bon
        Box<? extends C> cg2 = new Box<G>( new H() ); // G est un C et H est un G donc c'est bon

    // contravariance                              // mere est fille
        Box<? super G> ga = new Box<A>( new B() ); // A est un G et B est un A donc c'est bon
        Box<? super D> db = new Box<B>( new E() ); // B est un D et E est un B donc c'est bon
        //Box<? super D> da = new Box<C>( new C() ); // C n'est pas un D 
    }    
}
