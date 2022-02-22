import java.util.*;

/* ************************************************************************
 * Ex 3 - (30 pts)
 * Vous devez réaliser une structure de données qui représente le 
 * chargement d'un convoi ferroviaire. A chaque chargement, calculé en 
 * tonnage, nous cherchons un wagon qui peut contenir celui-ci. Si aucun 
 * wagon ne peut accepter le chargement, un nouveau wagon est ajouté au convoi.
 *
 * Lors de la création d'un convoi, représenter par un train, nous informons
 * la capacité maximale de chaque wagon.
 * Réalisez la classe `Train` pour que le code ci-dessous s'exécute 
 * correctement.
 *
 * N'exposez publiquement que les fonctionnalités visibles dans l'extrait 
 * du code ci-dessous. Rien de plus !!
 * En outre, inutile de redéfinir les méthodes de comparaison.
 *
 * A côté de chaque instruction, l'état du train avec ses wagons est
 * représenté à titre indicatif. 
 * Ex: Train([2,2,1]) indique que le convoi à trois wagons
 * avec des chargements respectifs de 2 tonnes, 2 tonnes et 1 tonne.
 * ************************************************************************/

public class Train {
    private List<Integer> content;
    private static int cap;

    public Train(int capacity){
        this.content = new ArrayList<>();
        this.cap = capacity;    
    }

    public static Train withWagonCapacity(int capacity){
        checkPositive(capacity);
        return new Train(capacity);
    }

    public static void checkPositive(double value){
        if(value <= 0){
            throw new RuntimeException("la capacité doit être supérieure à 0");
        }
    }

    public void add(int value){
        checkPositive(value);
        if(value > this.cap){
            throw new RuntimeException("la cargaison est plus grande que la capacité");
        }
        if(this.content.size() == 0){
            this.content.add(value);
        } else {
            int last = this.content.get(this.content.size()-1);
            if(last + value > this.cap){
                this.content.add(value);
            } else{
                this.content.set(this.content.size()-1, last + value);
            }
        }
    }

    public int nbWagons(){
        return this.content.size();
    }

    public int weight(){
        int res = 0;
        for(int current : this.content){
            res = res + current;
        }
        return res;
    }

    @Override
    public String toString(){
        return "Train(" + this.content.toString() + ")";
    }

    public static void main(String[] args){
        // Construit un train dont les wagons ont une capacité max de 10 tonnes
        Train train = Train.withWagonCapacity(10); // Train([])

        // Ajoute du chargement
        train.add(3); // Train([3])
        train.add(3); // Train([6])
        train.add(3); // Train([9])
        train.add(3); // Train([9, 3])
        train.add(2); // Train([9, 5])
        train.add(1); // Train([10, 5])
        train.add(8); // Train([10, 5, 8])

        System.out.println( train ); // affiche: Train([10, 5, 8])
        int nb = train.nbWagons(); // nb = 3
        int totalWeight = train.weight(); // totalWeight = 23
        System.out.println(totalWeight);

        //train.add(15); // lève une exception ! 15 est plus grand que la capacité d'un wagon (10)
    }
}