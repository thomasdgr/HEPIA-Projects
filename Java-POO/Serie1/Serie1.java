import java.util.Arrays;
public class Serie1 {
  public static void whileWithDoWhile(int i){
    if(i >= 5){
      return;
    }
    do{
      System.out.println(i);
      i++;
    } while(i < 5);
  }
  public static void doWhileWithWhile(int i){
    while(i < 5){
      System.out.println(i);
      i++;
    }
  }
  public static void g(int n, float x){
    return;
  }
  public static void h(short s){
    return;
  }
  public static void main(String[] args){
    short s = 10;
    byte b = (byte)0;
    int i = s;
    long l = s;
    float f = 0.0F;
    double d;

// exercice 1.1
    Serie1.whileWithDoWhile(0);
    System.out.println("\n");
    Serie1.doWhileWithWhile(0);

// exercice 1.2
    //byte b = s; // ne compile pas car l'ensemble de def de s est plus grand que celui de b

// exercice 1.3
    //s = s + s; // ne marche pas car une addition de short retourne un int
    //s = s * 2; // même explication
    int jgrek = s + s;

// exercice 1.4
    i = s++;
    // après, i = 10 car l'affectation ++ se fait après
    // par contre on aurait aimé faire i = ++s; pour que i = 11

// exercice 1.5
    Serie1.g(i, f); // marche car i est un int et f un float
    Serie1.g(b+1, f); // marche car le résultat de b+1 est un int
    Serie1.g(b, f); // marche car b est converti implicitement en int
    //Loop.g(i, d); // ne marche pas car d est un double
    Serie1.g(i, i); // i est implicitement converti en float
    //Loop.g(i, 2.0*f); // le résultat de 2.0*f est un double donc ca ne marche pas

    Serie1.h(b); // marche car le byte est sur 1 octet et le short sur 2 octets
    //Loop.h(b+1); // ne marche pas car la convertion en int pose probleme
    //Loop.h(5); // ne marche pas car 5 est un int par defaut
    //Loop.h(5.0); // ne marche pas car 5.0 est un double (plus grand qu'un short)

// exercice 1.6
    for(int igrek = 0; igrek < args.length; igrek++){
      System.out.println(args[igrek]);
    }
    Arrays.asList(args).forEach(value -> System.out.println(value));
  }
}
