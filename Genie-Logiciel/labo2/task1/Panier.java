import java.util.ArrayList;
import java.util.List;

public class Panier extends Fruit{

    private List<Fruit> panier;
    
    public Panier(){
        super();
        this.panier = new ArrayList<Fruit>();
    }

    public void addFruit(Fruit fruit){
        this.panier.add(fruit);
    } 

    public void removeFruit(Fruit fruit){
        this.panier.remove(fruit);
    }
        
    public void setNom(String nom){}
    
    public void setPepin(boolean pepin){}

    public String getNom(){
        String res = "Pannier(";
		for (Fruit f : this.panier){
			res += f.getNom() + " ";
		}
		return res + ")";
    }

    public boolean getPepin(){
		for (Fruit f : this.panier){
			if (f.getPepin()){
				return true;
			}
		}
		return false;
	}

   @Override 
    public void AfficherFruit(){
        System.out.println(this.getNom());
		System.out.println(this.getPepin() ? "Pannier avec pépins" : "Pannier sans pépin");
    }
} 