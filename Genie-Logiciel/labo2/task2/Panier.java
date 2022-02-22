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
    
    // ca ne sert a rien de faire les méthodes setNom() et setPepin()
    // elles ne servent a rien mais c'est possible de les appeler
    // et de toute facon on devrait pas pouvoir modifier le nom du pannier
    // ou s'il contient des pépins

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