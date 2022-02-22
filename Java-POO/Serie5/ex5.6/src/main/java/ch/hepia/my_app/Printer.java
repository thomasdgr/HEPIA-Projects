/**
 * Exercice 5.6
 * (exercice de groupe sur la classe Printer)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

package ch.hepia.my_app;
import java.util.UUID;

public class Printer implements Device {
    String deviceID;
    Status deviceStatus;

    public Printer(){
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