import java.util.*;

public class Main{

    public static void main(String args[]){
        Account a1 = Account.withName("Bip").withAmount(1000);
        Account a2 = Account.withName("Bop"); // initialisé à 0.-
        Account newA1 = a1.deposite(1000);

        Transaction t = newA1.transferTo(a2).amount(350);

        newA1.transferTo(a2).amount(350).ifSuccessOrElse(
          (src, dst, amount) -> {
            System.out.println("Transaction acceptée:");
            System.out.println("  infos émetteur: " + src.toString());
            System.out.println("  infos destinataire: " + dst.toString());
          },
          (String errorMsg) -> System.out.println("Transaction refusée: " + errorMsg)
        );
    }
}