package ch.hepia.my_app;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;
import java.lang.Math;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import ch.hepia.my_app.Container;

class ContainerTest {

    @Test
    void test_transfer_3_1() {
        List<Integer> output = new ArrayList<>();
        List<Integer> expected = new ArrayList<>();
        
        output = Container.transfer(10, 3, 3, 3);
        expected = Arrays.asList(3, 3, 3);
        assert output.equals(expected);

        output = Container.transfer(10, 3, 3, 3, 3);
        expected = Arrays.asList(3, 3, 3, 1);
        assert output.equals(expected);

        output = Container.transfer(5, 3);
        expected = Arrays.asList(3);
        assert output.equals(expected);

        output = Container.transfer(0, 3);
        expected = Arrays.asList(0);
        assert output.equals(expected);

        output = Container.transfer(100, 10, 40, 30, 50);
        expected = Arrays.asList(10, 40, 30, 20);
        assert output.equals(expected);
    }

    @Test
    void test_transfert_3_2(){
        Container origin = Container.withCapacity(10);

        assert !origin.isFull();
        assert origin.quantity() == 0;
        assert origin.remaining() == 10;

        origin.fillToTheMax();
        
        assert origin.isFull();
        assert origin.quantity() == 10;
        assert origin.remaining() == 0;

        Container destination1 = new Container(5);
        destination1.fillWith(2);

        assert !destination1.isFull();
        assert destination1.quantity() == 2;
        assert destination1.remaining() == 3;
        
        Container destination2 = Container.withCapacity(3);
        Container destination3 = Container.withCapacity(10);
        
        origin.fillTo(destination1, destination2, destination3);

        assert origin.quantity() == 0;

        assert destination1.quantity() == 5;
        assert destination1.isFull();

        assert destination2.quantity() == 3;
        assert destination2.isFull();
 
        assert destination3.quantity() == 2;
        assert !destination3.isFull();

        assert destination2.remaining() == 0;
        destination2.remove(2);
        assert destination2.remaining() == 2;

        assert destination3.quantity() == 2;
        destination3.flush();
        assert destination3.quantity() == 0;

        origin.fillWith(7);
        assert origin.toString().equals("(Container: 7/10)");
        origin.flush();
    }
}
