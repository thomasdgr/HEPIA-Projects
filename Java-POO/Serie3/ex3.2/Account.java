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

    public void deposite(double value){
        checkPositive(value);
        this.amount = this.amount + value;
    }

    public void withdraw(double value){
        checkPositive(value);
        if(this.amount < -2000.0){
            throw new RuntimeException("Votre solde doit être superieur à -2000.- pour retirer de l'argent");
        } else if(this.amount - value < -2000.0){
            throw new RuntimeException("le montant à retirer ne vous permet pas de rester au dessus du solde minimal de -2000.-");
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

    public static void main(String[] args){
        Account a1 = new Account("Thomas", "Dagier", 100.0);
        System.out.println("Création du compte a1:");
        System.out.println("owner: " + a1.OwnerCompleteName());
        System.out.println("amount: " + a1.Amount());
        System.out.println(a1.toString());
        System.out.println();

        System.out.println("Création du compte a2:");
        Account a2 = new Account("Antwan", "Blancy");
        System.out.println(a2.toString());
        System.out.println();

        a1.transferTo(a2, 400.0);
        Account.transfert(a1, a2, 100.0);
        System.out.println(a1.toString());
        System.out.println(a2.toString());
        System.out.println();

        System.out.println("Création du compte a3:");
        Account a3 = new Account("Antwan", "Blancy", 500.01);
        System.out.println(a3.toString());
        System.out.println();

        System.out.print("Les comptes " + a1.toString() + " et " + a3.toString() + " ");
        System.out.println(areAccountApproxEquals(a1, a3) ? "sont les mêmes" : "ne sont pas les mêmes");
        System.out.println();

        System.out.print("Les comptes " + a2.toString() + " et " + a3.toString() + " ");
        System.out.println(areAccountApproxEquals(a2, a3) ? "sont les mêmes" : "ne sont pas les mêmes");
    }
}