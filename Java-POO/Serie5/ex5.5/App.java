/**
 * Exercice 5.5
 * (exercice de groupe sur la classe Status)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

import java.lang.Math;
public class App{
  static interface Status{
    public static Status process(){
      switch((int) (Math.random() * 3)){
          case 0:
            return new On();
          case 1:
            return new Off();
          case 2:
            return new Err("Undefined");
      }
      return new Err("Undefined");
    }
    public boolean isOn();
    public boolean isOff();
    public boolean isErr();
    public String getErrorMessage();
    public static Status makeError(String errorMessage){
      return new Err(errorMessage);
    }
  }
  static class On implements Status{
    public boolean isOn(){
      return true;
    }
    public boolean isOff(){
      return false;
    }
    public boolean isErr(){
      return false;
    }
    public String getErrorMessage(){
      return "Il n'y a pas d'erreur";
    }
  }
  static class Off implements Status{
    public boolean isOn(){
      return false;
    }
    public boolean isOff(){
      return true;
    }
    public boolean isErr(){
      return false;
    }
    public String getErrorMessage(){
      return "Il n'y a pas d'erreur";
    }
  }
  static class Err implements Status{
    private String errorMessage;
    public Err(String errorMessage){
      this.errorMessage=errorMessage;
    }
    public boolean isOn(){
      return false;
    }
    public boolean isOff(){
      return false;
    }
    public boolean isErr(){
      return true;
    }
    @Override
    public String getErrorMessage(){
      return this.errorMessage;
    }
  }
  public static void main(String[] args){
    Status s1 = Status.process();
    if( s1.isOn() ) {
      System.out.println("L'appareil fonctionne");
    } else if( s1.isOff() ) {
      System.out.println("L'appareil est éteint");
    } else {
      System.out.println("L'appareil est instable: " + s1.getErrorMessage());
    }
    Status s2 = Status.makeError("Oups");
    System.out.println("L'appareil est instable: " + s2.getErrorMessage());

  }


}
