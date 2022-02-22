import java.math.BigInteger;
import java.util.Random;
import java.util.ArrayList;
import java.util.List;

public class Bruitage{
    public Bruitage(){}

    public BigInteger bruit(BigInteger mot, double seuil){
        Random random = new Random();
        for(int i = 0; i < mot.bitCount(); i++){
            if(seuil > random.nextFloat()){
                mot = mot.flipBit(i);
            }
        }
        return mot;
    }
    
    public List<BigInteger> bruit(List<BigInteger> content, double seuil){
        List<BigInteger> newContent = new ArrayList<>();
        for(BigInteger i : content){
            newContent.add(bruit(i, seuil));
        }
        return newContent;
    }
}