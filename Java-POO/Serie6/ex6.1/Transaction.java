import java.util.*;
import java.util.function.Consumer;

public class Transaction{
    private Account source;
    private Account destination;
    private double amountOfTransfert;
    private String errorMsg;

    public Transaction(Account src, Account dst, double amount, String errorMsg){
        this.source = src;
        this.destination = dst;
        this.amountOfTransfert = amount;
        this.errorMsg = errorMsg;
    }

    @Override
    public String toString(){
        String res = this.errorMsg.equals("none") ? "valide" : ("refusée:" + this.errorMsg);
        return "Transaction: \n\t Source: " + this.source.toString() + "\n\t Destination: " + this.destination.toString() + "\n\t Montant du transfert: " + this.amountOfTransfert + "\n\t Transaction: " + res;
    }

    public void ifSuccessOrElse(TriConsumer consumer1, Consumer<String> consumer2){
        if(this.errorMsg.equals("none")){
            consumer1.accept(this.source, this.destination, this.amountOfTransfert);
        } else {
            consumer2.accept(this.errorMsg);
        }
    }
}