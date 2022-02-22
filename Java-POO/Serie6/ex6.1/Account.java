import java.util.*;
import java.util.function.Consumer;

public class Account {
    
    private final String owner;
    private final double amount; 
    
    public Account(String firstName, String lastName){
        this.owner = firstName + " " + lastName;
        this.amount = 0.0;
    }

    public Account(String firstName, String lastName, double amount){
        this.owner = firstName + " " + lastName;
        this.amount = amount;
    }

    public Account(String name, double amount){
        this.owner = name;
        this.amount = amount;
    }

    public double Amount(){
        return this.amount;
    }

    public String OwnerCompleteName(){
        return this.owner;
    }

    public void checkPositive(double value){
        if(value < 0.0){
            throw new RuntimeException("le montant doit etre positif");
        }
    }

    public Account deposite(double value){
        checkPositive(value);
        return new Account(this.owner, this.amount + value);
    }

    public MyEntry withdraw(double value){
        checkPositive(value);
        String errorMsg = "none";
        if(this.amount < -2000.0){
            errorMsg = "Votre solde doit être superieur à -2000.- pour retirer de l'argent";
            return new MyEntry(new Account(this.owner, this.amount), errorMsg);
        } else if(this.amount - value < -2000.0){
            errorMsg = "Le montant à retirer ne vous permet pas de rester au dessus du solde minimal de -2000.-";
            return new MyEntry(new Account(this.owner, this.amount), errorMsg);
        }
        return new MyEntry(new Account(this.owner, this.amount - value), errorMsg);
    }

    public Transfert transferTo(Account dst){
        return new Transfert(this, dst);
    }
    
     @Override
     public String toString(){
         return "(" + this.owner + " avec: " + this.amount + "-.)";
     }

     private static Boolean areAccountApproxEquals(Account a1, Account a2, double tolerance){
        if(a1.owner.equals(a2.owner)){
            double ecart = Math.abs(a1.amount - a2.amount);
            if(ecart >= tolerance){
                return false;
            }
            return true;
        }
        return false;
    }

    public static Boolean areAccountApproxEquals(Account a1, Account a2){
        return areAccountApproxEquals(a1, a2, 0.01);
    }

    public static Account withName(String name){
        return new Account(name, 0.0);
    }

    public Account withAmount(double amount){
        return new Account(this.owner, amount);
    }
}