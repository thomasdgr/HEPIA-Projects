/**
 * Exercice 5.4
 * (exercice de groupe sur la classe Socializer)
 *
 * @author Blancy Antoine
 * @author Rod Quentin
 * @author Dagier Thomas
 */

interface Socializer{
  public void take(Drink drink);
  public double socialPoints();
  public double credit();
}

class Student implements Socializer{
  private double socialPoints;
  private double credit;
  public Student(){
    this.credit=0;
    this.socialPoints=0;
  }

  public void take(Drink drink){
    this.socialPoints += drink.socialBenefit();
    this.credit -= drink.price();
  }

  public double socialPoints(){
    return this.socialPoints;
  }

  public double credit(){
    return this.credit;
  }

}
class Teacher implements Socializer{
  private double socialPoints;
  public Teacher(){
    this.socialPoints=0;
  }

  public void take(Drink drink){
    this.socialPoints += drink.socialBenefit() / 2;
  }

  public double socialPoints(){
    return this.socialPoints;
  }

  public double credit(){
    return Double.MAX_VALUE;
  }

}
