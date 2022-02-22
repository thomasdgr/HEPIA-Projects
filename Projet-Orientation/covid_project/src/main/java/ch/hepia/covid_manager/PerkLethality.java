package ch.hepia.covid_manager;

public class PerkLethality extends Perk{

    private double lethality;
    
    //Design pattern FactoryMethod
    public PerkLethality(int id, String name, String description, double v1, int cost) {
        super(id, name, description, cost);
        this.lethality = Math.floor(v1 * 100) / 100;
    }

    @Override
    public void update(Virus v){
        v.applyLethalityBonus(this.lethality);
    }

    @Override
    public String toString(){
        return this.name() + ":\n  " + this.description() + "\n  +" + this.lethality + " of lethality\n  cost: " + this.cost() + " points";
    }
}