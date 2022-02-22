import java.util.Optional;
import java.util.function.Consumer;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

public class LinkedListInt implements ListInt{
    
    private Element firstElem;

    public LinkedListInt(){}

    @Override
    public int size(){
        int count = 0;
        Element elem = this.FirstElement();
        if(elem != null){
            Optional<Element> crt = Optional.of(elem);
            while(crt.isPresent()){
                count = count + 1;
                elem = crt.get();
                crt = elem.GetNextElem();
            }
        } else {
            return 0;
        }
        return count;    
    }

    @Override
    public void insert(int i){
        Element elem = this.FirstElement();
        Element newElem = new Element(i);
        if(elem != null){
            elem = getLastElem(elem);
            elem.SetNextElem(newElem);
        } else {
            setHead(newElem);
        }
    }

    @Override
    public Element FirstElement(){
        return this.firstElem;
    }

    @Override
    public void clear(){
        setHead(null);
    }

    @Override
    public int get(int i){
        int count = 0;
        Element elem = this.FirstElement();
        if(elem != null && i != 0){
            Optional<Element> crt = Optional.of(elem);
            while(crt.isPresent() && count != i){
                elem = crt.get();
                crt = elem.GetNextElem();
                count = count + 1;
            }
            return elem.GetNextElem().get().GetValueElem();
        } else if(i == 0){
            return headValue();
        } else {
            throw new RuntimeException("list is empty");
        }
    }

    private void setHead(Element elem){
        this.firstElem = elem;
    }

    private Element getLastElem(Element elem){
        Optional<Element> crt = Optional.of(elem);
        while(crt.isPresent()){
            elem = crt.get();
            crt = elem.GetNextElem();
        }
        return elem;
    }

    @Override
    public void printLinkedListInt(){
        String result = "[";
        Element elem = this.FirstElement();
        Optional<Element> crt = Optional.of(elem);
        while(crt.isPresent()){
            elem = crt.get();
            result += elem.GetValueElem() + ",";
            crt = elem.GetNextElem();
        }
        System.out.println(result.substring(0, result.length()-1) + "]");
    }

      // classe imbriquée pour ittérer sur une liste de int
    class LinkedListIntIterator implements Iterator<Integer> {

        private int current = 0;
        
        public boolean hasNext() {
            return current < LinkedListInt.this.size();
        }

        public Integer next() {
            int res = LinkedListInt.this.get(current);
            current += 1;
            return res;
        }
    }

    public Iterator<Integer> iterator() {
        return new LinkedListIntIterator();
    }
}