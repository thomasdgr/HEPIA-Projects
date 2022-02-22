/* ************************************************************************
 * Ex 4 - (15 pts)
 * Réalisez le code minimaliste pour que l'extrait ci-dessous fonctionne.
 * Inutile de redéfinir les méthodes de Object (toString, equals...)
 * 
 * Une référence de type MaybeInt a deux états. Soit il contient un entier
 * et il est possible de le récupérer. Soit il ne contient rien et il
 * ne devrait donc pas être possible de récupérer une valeur.
 * ************************************************************************/

public interface MaybeInt{
    public abstract boolean exists();
    public abstract int get();

    public static void main(String[] args) {
        MaybeInt m1 = new Something(1); 
        MaybeInt m2 = new Nothing(); 
        if (m1.exists()) { // ==> true car m1 référence quelquechose qui contient 1
            int i = m1.get(); // ==> i = 1
        } else {
            System.out.println("m1 n'a aucune valeur");
        }
        System.out.println( m2.exists() ); // ==> affiche `false`
        int j = m2.get(); // ==> lève une exception ! il n'y a rien à récupérer...
    }
}