package ch.hepia.my_app;
import java.lang.Math;
import java.util.List;
import java.util.ArrayList;
import java.util.Objects;

public class Account {

    private String owner;
    private double amount; 

    public Account(String firstName, String lastName){
        this.owner = firstName + " " + lastName;
    }

    public Account(String firstName, String lastName, double amount){
        this(firstName, lastName);
        checkPositive(amount);
        this.amount = amount;
    }

    public double amount(){
        return this.amount;
    }

    public String owner(){
        return this.owner;
    }

    public void checkPositive(double value){
        if(value < 0.0){
            throw new RuntimeException("Amount must be a double greater than 0.0");
        }
    }

    public void deposite(double value){
        checkPositive(value);
        this.amount = this.amount + value;
    }

    public void withdraw(double value){
        checkPositive(value);
        if(this.amount < -2000.0){
            throw new RuntimeException("Your balance has to be greater than -2000.- to withdraw money");
        } else if(this.amount - value < -2000.0){
            throw new RuntimeException("The amount you want to withdraw is making your balance lower than -2000.- which is not allowed");
        }
        this.amount = this.amount - value;
    }

    public void transferTo(Account dest, double value){
        this.withdraw(value);
        dest.deposite(value);
    }

    public static void transfert(Account src, Account dest, double value){
        src.transferTo(dest, value);
    }
    
     @Override
     public String toString(){
         return "(Account: " + this.owner + " with " + this.amount + ".-)";
     }

     private static Boolean approxEquals(Account a1, Account a2, double tolerance){
        if(a1.owner.equals(a2.owner)){
            double ecart = Math.abs(a1.amount - a2.amount);
            if(ecart >= tolerance){
                return false;
            }
            return true;
        }
        return false;
    }

    public static Boolean approxEquals(Account a1, Account a2){
        return approxEquals(a1, a2, 0.01);
    }

    @Override
    public boolean equals(Object o){
        if(this == o){
            return true;
        } 
        Account other = (Account) o;
        if(o == null || o.getClass() != this.getClass() || other.hashCode() != this.hashCode()){
            return false;
        } 
        return this.owner.equals(other.owner) && this.amount == other.amount;
    }

    @Override
    public int hashCode(){
        return Objects.hash(this.owner + String.valueOf(this.amount));
    }

    public static void main(String[] args){
        Account a1 = new Account("Thomas", "Dagier", 100.0);
        System.out.println("Thomas' account creation:");
        System.out.println("owner: " + a1.owner());
        System.out.println("amount: " + a1.amount());
        System.out.println(a1.toString());
        System.out.println();

        System.out.println("Antwan's account creation:");
        Account a2 = new Account("Antwan", "Blancy");
        System.out.println(a2.toString());
        System.out.println();

        a1.transferTo(a2, 400.0);
        Account.transfert(a1, a2, 100.0);
        System.out.println(a1.toString());
        System.out.println(a2.toString());
        System.out.println();

        System.out.println("new Antwan's account creation:");
        Account a3 = new Account("Antwan", "Blancy", 500.01);
        System.out.println(a3.toString());
        System.out.println();

        System.out.print("Accounts " + a1.toString() + " and " + a3.toString());
        System.out.println(Account.approxEquals(a1, a3) ? " are the same" : " are not the same");
        System.out.println();

        System.out.print("Accounts " + a2.toString() + " and " + a3.toString());
        System.out.println(Account.approxEquals(a2, a3) ? " are the same" : " are not the same");

        a3.withdraw(0.01);
        System.out.print("Accounts " + a2.toString() + " and " + a3.toString());
        System.out.println(a2.equals(a3) ? " are the same" : " are not the same");
    }
}