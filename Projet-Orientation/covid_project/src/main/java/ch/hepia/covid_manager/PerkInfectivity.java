package ch.hepia.covid_manager;

public class PerkInfectivity extends Perk{

    private double infectivity;
    
    //Design pattern FactoryMethod
    public PerkInfectivity(int id, String name, String description, double v1, int cost) {
        super(id, name, description, cost);
        this.infectivity =  Math.floor(v1 * 100) / 100;
    }

    @Override
    public void update(Virus v){
        v.applyInfectivityBonus(infectivity);
    }

    @Override
    public String toString(){
        return this.name() + ":\n  " + this.description() + "\n  +" + this.infectivity + " of infectivity\n  cost: " + this.cost() + " points";
    }
}