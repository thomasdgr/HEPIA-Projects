/**
 * Exercice 5.6
 * (exercice de groupe sur la classe Status inspirée du 5.5)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

package ch.hepia.my_app;
import java.lang.Math;

  interface Status{
    public static Status process(){
      double randomDouble = Math.random();
      if(randomDouble <= 0.5){
        return new On();
      }else if(randomDouble <= 0.8){
        return new Off();
      }else{
        return new Err();
      }
    }
    public boolean isOn();
    public boolean isOff();
    public boolean isErr();
    public String getErrorMessage();
    public static Status makeError(String errorMessage){
      return new Err(errorMessage);
    }

    default public String statusInfo(){
      if(this.isOn()){
        return "On";
      }else if(this.isOff()){
        return "Off";
      }else{
        return "Err";
      }
    }

  }
  class On implements Status{
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
  class Off implements Status{
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
  class Err implements Status{
    private String errorMessage;

    public Err(String errorMessage){
      this.errorMessage=errorMessage;
    }

    public Err(){
      double randomDouble = Math.random();
      if(randomDouble <= 0.25){
        this.errorMessage="Material Communication Error";
      }else if(randomDouble <= 0.5){
        this.errorMessage="Updating Windows 3.1 Error";
      }else if (randomDouble <= 0.75){
        this.errorMessage="Protocol Error";
      }else{
        this.errorMessage="Undefined Error";
      }
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
