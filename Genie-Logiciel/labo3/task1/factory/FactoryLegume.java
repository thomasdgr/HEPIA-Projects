package factory;

import legumes.Legume;
import legumes.LegumeCuisson;
import legumes.LegumePotage;
import legumes.LegumeSalade;
import legumes.LegumeVapeur;

public class FactoryLegume extends Factory{

    public FactoryLegume(){} 

    public Legume menu(String famille){
        if(famille.equals("Potage")){
            return new LegumePotage();
        }
        else if(famille.equals("Salade")){
            return new LegumeSalade();
        } 
        else if(famille.equals("Vapeur")){
            return new LegumeVapeur();
        }
        else if(famille.equals("Cuisson")){
            return new LegumeCuisson();
        } else{
            System.out.println("La famille de légumes spécifiée n'exisite pas");
            return null;
        }
    } 
} 
