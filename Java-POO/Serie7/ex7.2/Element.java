import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;

public class Element{

    private int value;
    private Optional<Element> nextElem;

    public Element(int value){
        this.value = value;
        this.nextElem = Optional.empty();
    }
    
    public Optional<Element> GetNextElem(){
        return this.nextElem;
    }

    public void SetNextElem(Element elem){
        this.nextElem = Optional.of(elem);
    }

    public int GetValueElem(){
        return this.value;
    }

    public void SetValueElem(int value){
        this.value = value;
    }
}