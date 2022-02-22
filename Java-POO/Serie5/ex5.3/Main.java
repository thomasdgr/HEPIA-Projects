import java.util.*;

public class Main{
    public static void main(String[] args) {

        Article atutut = new Car("pouet", 4.0);
        Article pouetpouet = new Car("pouet", 5.0);
        Article lavoila = new Car("pouet", 6.0);
        Article latotomobile = new Car("pouet", 7.0);

        Article[] jeuset = new Article[3];
        jeuset[0] = atutut;
        jeuset[1] = pouetpouet;
        jeuset[2] = lavoila;
        Container c1 = new Container(jeuset);

        Article[] setetmatch = new Article[3];
        setetmatch[0] = atutut;
        setetmatch[1] = pouetpouet;
        setetmatch[2] = lavoila;
        Container c2 = new Container(setetmatch);

        Container[] c = new Container[2];
        c[0] = c1;
        c[1] = c2;

        Transport lebato = new Boat("michel", c);
        double price = 0.0;
        for(Container kek : lebato.containers()){
            price += kek.totalPrice();
        }
        System.out.println(price);
    }
}

interface Transport{
    public Container takeNext();
    public Container[] containers();
}
interface Article{
    public double price();
}
class Car implements Article{
    private String brand;
    private double price;
    public Car(String brand, double price){
        this.brand = brand;
        this.price = price;
    }
    @Override
    public double price(){
        return this.price;
    }
}
class Container{
    private Article[] articles;
    
    public Container(Article[] articles){
        this.articles = articles;
    }
    public double totalPrice(){
        double total = 0.0;
        for(Article a : this.articles){
            total += a.price();
        }
        return total;
    }
}
class Boat implements Transport{
    private Container[] containers;
    private String name;
    private int index;
    
    public Boat(String name, Container[] containers){
        this.name = name;
        this.containers = containers;
        this.index = 0;
    }

    @Override
    public Container[] containers(){
        return this.containers;
    }

    @Override
    public Container takeNext(){
        if(index < this.containers.length){
            this.index += 1;
            return containers[index];
        } else {
            throw new RuntimeException("yaplu");
        }
    }
}