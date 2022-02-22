/**
 * Exercice 5.6
 * (exercice de groupe sur la classe CoffeeMachine)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

package ch.hepia.my_app;
import java.util.UUID;

public class CoffeeMachine implements Device {
    String deviceID;
    Status deviceStatus;

    public CoffeeMachine(){
        this.deviceID = UUID.randomUUID().toString();
        this.deviceStatus = Status.process();
    }

    public Status status(){
        return this.deviceStatus;
    }

    public String id(){
        return this.deviceID;
    }
    public void changeStatus(Status newStatus){
        this.deviceStatus = newStatus;    
    }
    public void changeId(){
        this.deviceID = UUID.randomUUID().toString();
    }
}