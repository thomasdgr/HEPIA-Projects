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

public class DatabaseHelper{
  public static Device randomDevice(){
    Random rand = new Random();
    int randomValue = rand.nextInt() % 4;
    switch(randomValue){
      case 0:
        return new Computer();
      case 1:
        return new Printer();
      case 2:
        return new Camera();
      default:
        return new CoffeeMachine();
    }
  }
  public static void populate(Database dataDevice, int number){
    for(int i=0; i< number; i++){
      Device newDevice = randomDevice();
      while(dataDevice.exists(newDevice.id())){
        newDevice.changeId();
      }
      dataDevice.add(newDevice);
    }
  }
  public static int[] stabilize(Database dataDevice){
    boolean checkAllOn=true;
    int[] valuesRestartAndStart = new int[2];
    int numberOfRestart = 0;
    int numberOfStart = 0;
    for(Device dev : dataDevice.devices()){
      while(!dev.status().isOn()){
        if(dev.status().isErr()){
          dev.reboot();
          numberOfRestart+=1;
        }
        if(dev.status().isOff()){
          dev.start();
          numberOfStart += 1;
        }
      }
    }
    valuesRestartAndStart[0]= numberOfRestart;
    valuesRestartAndStart[1]= numberOfStart;
    return valuesRestartAndStart;
  }
  public static void partition(Database dataDevice, List<Device> listOn, List<Device> listOff, List<Device> listErr){
    for(Device dev : dataDevice.devices()){
      switch(dev.status().statusInfo()){
        case "On":
          listOn.add(dev);
          break;
        case "Off":
          listOff.add(dev);
          break;
        case "Err":
          listErr.add(dev);
          break;
      }
    }
  }
}
