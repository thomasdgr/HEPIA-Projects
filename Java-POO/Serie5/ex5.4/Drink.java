/**
 * Exercice 5.4
 * (exercice de groupe sur la classe Drink)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

interface Drink {
  int socialBenefit();
  int price();
}

class Beer implements Drink {
    int socialBenefit;
    int price;

    public Beer(){
        this.socialBenefit = 3;
        this.price = 4;
    }

    public int socialBenefit(){
        return this.socialBenefit;
    }

    public int price(){
        return this.price;
    }
}

class Soda implements Drink {
    int socialBenefit;
    int price;

    public Soda(){
        this.socialBenefit = 1;
        this.price = 3;
    }

    public int socialBenefit(){
        return this.socialBenefit;
    }

    public int price(){
        return this.price;
    }
}
