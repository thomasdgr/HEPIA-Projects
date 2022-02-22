/**
 * Exercice 5.6
 * (exercice de groupe sur la classe Device)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

package ch.hepia.my_app;
import java.lang.*;

interface Device {

  public default void start(){
    if (this.status().isOff()){
      if(Math.random() < 0.3){
        this.changeStatus(new Err());
      }else{
        this.changeStatus(new On());
      }
    }
  }

  public default void shutdown(){
    if (!this.status().isOff()){
      this.changeStatus(new Off());
    }
  }

  public default void reboot(){
    if (!this.status().isOff()){
      this.shutdown();
      this.start();
    }
  }

  public default String deviceInfo(){
    return "id:" + this.id() + " status: " + this.status().statusInfo() + "\n";
  }

  Status status();
  String id();
  void changeStatus(Status newStatus);
  void changeId();
}
