/**
 * Exercice 5.6
 * (exercice de groupe)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

package ch.hepia.my_app;
import java.lang.*;
import java.util.*;

public class App{
  public static void main(String[] args){
    System.out.println("\n\tImplémentation en utilisant une liste : \n");
    Database myListDataBase = new ListDevice();
    DatabaseHelper.populate(myListDataBase, 20);
    System.out.println("Liste de appareils présents dans la base de données et leurs status: ");
    System.out.println(myListDataBase.databaseInfo());
    List<Device> listOn = new ArrayList<>();
    List<Device> listOff = new ArrayList<>();
    List<Device> listErr = new ArrayList<>();

    System.out.println("Stabilisation des appareils...");
    int[] array = DatabaseHelper.stabilize(myListDataBase);
    System.out.println("Nombre d'appareils redémarrés :");
    System.out.println(array[0]);
    System.out.println("Nombre d'appareils démarrés :");
    System.out.println(array[1]);

    DatabaseHelper.partition(myListDataBase, listOn, listOff, listErr);
    System.out.println("\nListe des appareils allumés :");
    for(Device dev : listOn){
      System.out.print(dev.deviceInfo());
    }
    System.out.println("\nListe des appareils éteints :");
    for(Device dev : listOff){
      System.out.print(dev.deviceInfo());
    }
    System.out.println("\nListe des appareils qui ont un problème :");
    for(Device dev : listErr){
      System.out.print(dev.deviceInfo());
    }


    System.out.println("\n\n\tImplémentation en utilisant une hashmap : \n");
    Database myHashMapDataBase = new MapDevice();
    DatabaseHelper.populate(myHashMapDataBase, 20);
    System.out.println("Liste de appareils présents dans la base de données et leurs status: ");
    System.out.println(myHashMapDataBase.databaseInfo());
    List<Device> hashMapOn = new ArrayList<>();
    List<Device> hashMapOff = new ArrayList<>();
    List<Device> hashMapErr = new ArrayList<>();

    DatabaseHelper.partition(myHashMapDataBase, hashMapOn, hashMapOff, hashMapErr);
    System.out.println("\nListe des appareils allumés :");
    for(Device dev : hashMapOn){
      System.out.print(dev.deviceInfo());
    }
    System.out.println("\nListe des appareils éteints :");
    for(Device dev : hashMapOff){
      System.out.print(dev.deviceInfo());
    }
    System.out.println("\nListe des appareils qui ont un problème :");
    for(Device dev : hashMapErr){
      System.out.print(dev.deviceInfo());
    }

    System.out.println("\nStabilisation des appareils...");
    int[] hashMapArray = DatabaseHelper.stabilize(myHashMapDataBase);
    System.out.println("Nombre d'appareils redémarrés :");
    System.out.println(hashMapArray[0]);
    System.out.println("Nombre d'appareils démarrés :");
    System.out.println(hashMapArray[1]);
    System.out.println("\nListe de appareils après stabilisation : ");
    System.out.println(myHashMapDataBase.databaseInfo());
  }
}
