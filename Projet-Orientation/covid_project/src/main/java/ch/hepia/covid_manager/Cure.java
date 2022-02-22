package ch.hepia.covid_manager;

import java.util.List;
import java.util.ArrayList;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class Cure{
    // impact of the cure on the virus -> 0 at first, then when progression == 100% -> grows
    private double impact;
    // current state of cure developpement
    private double progression;
  
    private List<PropertyChangeListener> lstObservers;

    //Design Pattern Singleton
    private static Cure cure;

    public static Cure getInstance(){
        if (Cure.cure == null){
            Cure.cure = new Cure();
        }
        return Cure.cure;
    }
  
    private Cure(){
        //Takes constants "similar" to the real covid-19's "stats"
        this.impact =  0.0; 
        this.progression = 0.0;
        this.lstObservers =  new ArrayList<>();
    }

    public double impact(){
        return this.impact;
    }

    public double progression(){
        return this.progression;
    }

    //Update research; and if research is done, increase impact
    public void updateCure(){
        if(this.progression < 100){
            this.progression += 0.05;
        } else{
            this.impact += 0.05;
        } 
        this.updateObservers();
    }

    // Design pattern observer
    public void updateObservers(){
        this.lstObservers.forEach(i->
            i.propertyChange(new PropertyChangeEvent(this, "cure", Double.valueOf(this.progression - 0.05), Double.valueOf(this.progression)))
        );
    }

    public void addListener(PropertyChangeListener pcl){
        this.lstObservers.add(pcl);
    }

    public void setImpact(double d){
        this.impact = d;
    }

    public void setProgress(double d){
        this.progression = d;
    }
}