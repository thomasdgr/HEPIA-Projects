/**
 * Exercice 5.4
 * (exercice de groupe)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

public class Main{

  public static void main(String args[]){

    Socializer someStudent = new Student();
    Socializer someOtherStudent = new Student();

    Socializer someTeacher = new Teacher();
    Socializer someCoolerTeacher = new Teacher();

    Drink beer = new Beer();
    Drink soda = new Soda();



    for(int i=0; i < 30; i+=1){
      someTeacher.take(soda);
      someCoolerTeacher.take(beer);
    }
    

    someStudent.take(beer);
    someStudent.take(soda);

    while(someStudent.socialPoints() < someCoolerTeacher.socialPoints() && someStudent.credit() > 4){
      someStudent.take(beer);
    }
    
    if (someStudent.socialPoints() > someCoolerTeacher.socialPoints()){
      System.out.println("someStudent is cooler than someCoolerTeacher!!");
    }else{
      System.out.println("someCoolerTeacher is cooler than someStudent!!");
    }

  }
}