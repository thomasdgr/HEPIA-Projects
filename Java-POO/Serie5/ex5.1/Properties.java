/**
 * Exercice 5.1
 * (exercice de groupe sur la classe Properties)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

import java.util.*;

class Properties {

  private Map<String, String> map;

  public Properties(){
    this.map = new HashMap<>(); 
  }

  // correction : ajout de la détéction d'un retour null
  public String getProperty(String key) {
    String res = this.map.get(key);
    if(res == null){
      throw new RuntimeException("Warning : " + key + " has no match");
    }
    return this.map.get(key);
  }

  public String getPropertyOrElse(String key, String defaultValue)
  {
    String val = this.map.get(key);
    if (val == null){
      return defaultValue;
    }else{
      return val;
    }
  }

  public void addProperty(String key, String value) {
    this.map.put(key, value);
  }

  public List<String> keys() {
    return new ArrayList<>(this.map.keySet());
  }

  public List<String> values() {
    return List.copyOf(this.map.values());
  }

  public Map<String, String> allProperties() {
    return Map.copyOf(this.map);
  }

  public static void main(String args[]){

    Properties test = new Properties();
    test.addProperty("quentin","rod");
    test.addProperty("jean","jla");
    test.addProperty("blo","blou");
    String val1= test.getProperty("quentin");
    System.out.println(val1);
    String val2= test.getProperty("jean");
    System.out.println(val2);
    String val3= test.getPropertyOrElse("lo", "nop");
    System.out.println(val3);
    List<String> keys = test.keys();
    List<String> values = test.values();
    System.out.println(keys.toString());
    System.out.println(values.toString());
      
  }

}