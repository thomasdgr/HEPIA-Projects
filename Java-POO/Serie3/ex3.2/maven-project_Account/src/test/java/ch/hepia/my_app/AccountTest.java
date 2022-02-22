package ch.hepia.my_app;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;
import java.lang.Math;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import ch.hepia.my_app.Account;

class AccountTest {

    @Test
    void test_amount() {
        Account a1 = new Account("Thomas", "Dagier", 100.0);
        assert a1.owner().equals("Thomas Dagier");
        assert a1.amount() == 100.0;
        assert a1.toString().equals("(Account: Thomas Dagier with 100.0.-)");

        Account a2 = new Account("Antwan", "Blancy");
        a1.transferTo(a2, 400.0);
        assert a1.amount() == -300.0;

        Account.transfert(a1, a2, 100.0);
        assert a1.amount() == -400.0;
        assert a2.amount() == 500.0;

        Account a3 = new Account("Antwan", "Blancy", 500.01);
        assert a3.toString().equals("(Account: Antwan Blancy with 500.01.-)");

        assert !Account.approxEquals(a1, a3);
        assert Account.approxEquals(a2, a3);

        a3.withdraw(0.01);
        System.out.print("Accounts " + a2.toString() + " and " + a3.toString());
        assert a2.equals(a3);
    }        
}
