/**
 * Exercice 5.6
 * (exercice de groupe sur la classe Database)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

package ch.hepia.my_app;
import java.lang.RuntimeException;
import java.util.*;

interface Database{

  public void add(Device d); // ajoute ou remplace un périphérique

  /* retourne le périph qui a l'id spécif.
   * une exception sinon */
  default Device device(String id){
    for(Device dev : this.devices()){
      if(dev.id().equals(id)){
        return dev;
      }
    }
    throw new RuntimeException("Ce périphérique n'est pas présent.");
  }

  List<Device> devices();

  default boolean exists(String id) {

    for(Device dev : this.devices()){
      if(dev.id().equals(id)){
        return true;
      }
    }
    return false;
  }
  // retourne le nombre de périphériques enregistrés dans la BD
  default int count() {
    return this.devices().size();
  }

  /* supprime le périph. qui a l'id spécif. et le retourne
   * une exception sinon */
  public Device remove(String id);

  default public String databaseInfo(){
    String output = "";
    for(Device dev : this.devices()){
      output += dev.deviceInfo();
    }
    return output;
  }
}

class ListDevice implements Database{
  List<Device> list;
  public ListDevice(){
    this.list = new ArrayList<>();
  }
  @Override
  public void add(Device d){
    this.list.add(d);
  }
  @Override
  public Device remove(String id){
    for(Device dev : list){
      if(dev.id().equals(id)){
        this.list.remove(dev);
        return dev;
      }
    }
    throw new RuntimeException("Aucun objet ayant cet ID n'est présent dans la liste");
  }

  @Override
  public List<Device> devices(){
    return List.copyOf(this.list);
  }
}

class MapDevice implements Database{
  private Map<String,Device> map;

  public MapDevice(){
    this.map = new HashMap<>();
  }

  @Override
  public void add(Device d){
    this.map.put(d.id(), d);
  }
  @Override
  public List<Device> devices(){
    return new ArrayList<Device>(this.map.values());
  }
  @Override
  public Device remove(String id){
    return this.map.remove(id);
  }
}
