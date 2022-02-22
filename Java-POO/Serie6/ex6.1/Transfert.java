public class Transfert{
    private Account source;
    private Account destination;

    public Transfert(Account src, Account dst){
        this.source = src;    
        this.destination = dst;
    }

    public Transaction amount(double amount){
        MyEntry entry = this.source.withdraw(amount); 
        Account a1 = entry.account();
        String errorMsg = entry.errorMsg();
        Account a2;
        if(errorMsg.equals("none")){
            a2 = this.destination.deposite(amount);
        } else {
            a2 = this.destination;
        }
        return new Transaction(a1, a2, amount, errorMsg);
    }
}