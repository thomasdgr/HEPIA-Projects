import java.util.*;

/* ************************************************************************
 * Ex 1 - (15 pts)
 * La classe `Smurf` comporte plusieurs petites erreurs ou mauvaises
 * pratiques (env. cinq)
 * 1. corrigez-les 
 * 2. complétez ensuite le code pour que l'extrait ci-dessous puisse
 * fonctionner correctement.
 * ************************************************************************/

public class Smurf{

    private String name;
    private List<Smurf> friends = new ArrayList<>();

    public Smurf(String name) {
        this.name = name;
    }

    public void addFriend(Smurf friend) {
        this.friends.add(friend);
    }

    public int nbFriends() {
        return friends.size();
    }

    @Override
    public String toString(){
        String res = this.name;
        return "Smurf(" + res.toUpperCase() + ")";
    }

    @Override
    public boolean equals(Object o) {
        if(this == o) return true;
        if(o == null || o.getClass() != this.getClass()) {
          return false; 
        }
        Smurf other = (Smurf)o;
        return this.name == other.name && this.friends.equals(other.friends);
    }

    public static void main(String[] args) {
        // extrait -----------------------------------------------------------------
        Smurf s1 = new Smurf("Schtroumpfette");
        System.out.println( s1 ); // ==> affiche: Smurf@4b9af9a9
                                  // TODO: devrait affichier: Smurf(SCHTROUMPFETTE)
        Smurf s2 = new Smurf("Grognon");
        List<Smurf> smurfs = List.of(s1, s2);
        smurfs.contains( new Smurf("Grognon") ); // ==> false !!!
                                                 // TODO: aurait du retourner true
        // -------------------------------------------------------------------------
    }    
}