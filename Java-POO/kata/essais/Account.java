public class Account {

    private String owner;
    private double amount;

    public Account(String firstName, String lastName, double amount){
        CheckPositive(amount);
        this.owner = firstName + " " + lastName;
        this.amount = amount;
    }

    public Account(String firstName, String lastName){
        this.owner = firstName + " " + lastName;
    }

    public void CheckPositive(double number){
        if(number < 0.0){
            throw new RuntimeException("number must be positive");
        }
    }

    public String OwnerCompleteName(){
        return this.owner;
    }

    public double Amount(){
        return this.amount;
    }

    @Override
    public String toString(){
        return this.owner + " with : " + this.amount + ".-";
    }

    public void Deposite(double value){
        CheckPositive(value);
        this.amount = this.amount + value;
    }

    public void Withdraw(double value){
        CheckPositive(value);
        if(this.amount - value < -2000.0){
            throw new RuntimeException("Can't withdraw more than -2000.-");
        }
        this.amount = this.amount - value;
    }

    public void transferTo(Account dst, double value){
        this.Withdraw(value);
        dst.Deposite(value);
    }

    public static void transfert(Account src, Account dst, double value){
        src.transferTo(dst, value);
    }

    public static boolean areAccountApproxEquals(Account a1, Account a2){
        if(a1.owner.equals(a2.owner)){
            return Math.abs(a1.amount - a2.amount) <= 0.01;
        }
        return false;
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
        System.out.println(Account.areAccountApproxEquals(a1, a3) ? "sont les mêmes" : "ne sont pas les mêmes");
        System.out.println();

        System.out.print("Les comptes " + a2.toString() + " et " + a3.toString() + " ");
        System.out.println(Account.areAccountApproxEquals(a2, a3) ? "sont les mêmes" : "ne sont pas les mêmes");
    }
}