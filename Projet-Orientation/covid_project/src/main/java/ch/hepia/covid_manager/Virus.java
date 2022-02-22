package ch.hepia.covid_manager;

import java.util.List;
import java.util.ArrayList;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;


public class Virus{
    private double infectivity;
    private double lethality;
    private double resistance;
  
    private List<Perk> perkLst;
    //Design Pattern Observer
    private List<PropertyChangeListener> lstObservers;
    private int currentPoints;
  
    //Design Pattern Singleton
    private static Virus virus;

    public static Virus getInstance(){
        if (Virus.virus == null){
          Virus.virus = new Virus();
        }
        return Virus.virus;
    }

  
    private Virus(){
        //Takes constants "similar" to the real covid-19's "stats"
        this.infectivity =  0.15; //Aucune idée du chiffre a mettre au début
        this.lethality = 0.005; //0.5% de mortalitlé
        this.resistance = 0.005;

        this.currentPoints = 0;
        this.perkLst = new ArrayList<>();
        this.lstObservers = new ArrayList<>();
    }

    public double infectivity(){
        return this.infectivity;
    }

    public void addPoint(){
        this.currentPoints += 1;
        this.updateObservers();
    }

    public void addPoints(int num){
        this.currentPoints += num;
        this.updateObservers();
    }

    public void updateObservers(){
        this.lstObservers.forEach(i->
            i.propertyChange(new PropertyChangeEvent(this, "virus", Integer.valueOf(this.currentPoints - 1), Integer.valueOf(this.currentPoints)))
        );
    }

    public double lethality(){
        return this.lethality;
    }
  
    public double resistance(){
        return this.resistance;
    }

    public void applyInfectivityBonus(double bonus){
        this.infectivity *= (1 + bonus);
    }

    public void applyLethalityBonus(double bonus){
        this.lethality *= (1 + bonus);
    }

    public void applyResistanceBonus(double bonus){
        this.resistance *= (1 + bonus);
    }
    
    //This method needs to be called only when loading the virus
    public void freeUpgrade(Perk p){
        if(this.hasPerk(p)){
            return;
        }
        this.perkLst.add(p);
        p.update(this);
        this.updateObservers();
    }

    public void upgrade(Perk p){
        if (this.currentPoints < p.cost()){
            return;
        }
        if(this.hasPerk(p)){
            return;
        }
        this.currentPoints -= p.cost();
        this.perkLst.add(p);
        p.update(this);
        this.updateObservers();
    }

    public boolean hasEnoughPoints(Perk p){
        return p.cost() <= this.currentPoints;
    }

    public boolean hasPerk(Perk p){
        return this.perkLst.contains(p);
    }

  public List<Perk> getUnlockedPerks(){
    return this.perkLst;
  }
    @Override
    public String toString(){
        String output = "Virus{\n";
        output +=  "\tInfectivity: "+ this.infectivity + "\n";
        output +=  "\tLethality: "+ this.lethality + "\n";
        output +=  "\tResistance: "+ this.resistance + "\n";
        output +=  "\tPoints: "+ this.currentPoints + "\n";
        output +=  "\tPerks: "+ this.perkLst + "\n}";
        return output;
    }

    public void addListener(PropertyChangeListener pcl){
        this.lstObservers.add(pcl);
    }


    public int getPoints(){
        return this.currentPoints;
    }
}