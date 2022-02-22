import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.lang.Math;
import java.util.ArrayList;
import java.util.Random;
import java.text.DecimalFormat;

public class App{
    
    // retourne la valeur de la classe prédite à partir des poids actuels et des attributs du noeud
    static double predict_output(ArrayList<Integer> data, ArrayList<Double> weights){
        double predict = 0.0;
        for(int i = 0; i < weights.size(); i++){
            predict += weights.get(i) * data.get(i+1);
        }
    // fonction d'activation identité
        //return predict;
    // fonction d'activation sigmoide
        return sigmoid(predict);
    }

    static ArrayList<Double> train(ArrayList<ArrayList<Integer>> data){
        ArrayList<Double> weights = new ArrayList<>();
        for(int i = 0; i < data.get(0).size()-1; i++){
            double max = 0.001;
            double min = -0.001;
            weights.add((Math.random()*((max-min)+1))+min);
        }
        for(int j = 0; j <= 5000; j+=1){
            Random rand = new Random();
            int curr = rand.nextInt(data.size());
            int output = data.get(curr).get(0);
            for(int k = 0; k < weights.size(); k++){
                double w = weights.get(k);
            // formule pour la fonction d'identité (and-or-xor)
                //double delta_w = 0.1 * (output - predict_output(data.get(curr), weights)) * data.get(curr).get(k+1);
            // formule pour la fonction sigmoide (monks)
                double delta_w = 0.1 * (output - predict_output(data.get(curr), weights)) * data.get(curr).get(k+1) * (1 - predict_output(data.get(curr), weights));                                
                weights.set(k, w + delta_w);
            }
            // calcul de l'erreur quadratique et affichage toutes les 100 ittérations
            double sum = 0.0;
            for(ArrayList<Integer> item : data){
                sum += Math.pow(predict_output(item, weights), 2);
            }
            if(j % 100 == 0){
                System.out.println("Erreur quadratique " + j + ": " + sum/2);
            }
        }
        return weights;
    }

    // retourne la classe qui aura été prédite en fonction des poids finaux et des attributs
    // d'un noeud pris dans l'ensemble de test
    static int test(ArrayList<Integer> data, ArrayList<Double> weights){
        return (predict_output(data, weights) < 0.5) ? 0 : 1;
    }

    // fonction sigmoide utilisée pour l'activation
    static double sigmoid(double x){
        return (1.0 / (1.0 + Math.exp(-x)));
    }

    // lecture d'un fichier et stockage des informations de chaque noeud dans une liste
    // /!\ le biais (qui vaut toujours 1) est ajouté à la main pour chauque noeud comme un attribut "x0"
    // structure d'un noeud : <classe> <biais/x0> <x1> <x2> <x3> <x4> <x5> <x6>
    static ArrayList<ArrayList<Integer>> read_file(String fileName){
        BufferedReader reader;
        ArrayList<ArrayList<Integer>> data = new ArrayList<>();
		try {
			reader = new BufferedReader(new FileReader(fileName));
			String line = "";
            int j = 0;
			while (line != null) {
				line = reader.readLine();
                if(line != null){
                    data.add(new ArrayList<>());
                    String[] integerStrings = line.split(" ");
                    for(int i = 0; i < integerStrings.length-1; i++){
                        if(integerStrings[i] != ""){
                            data.get(j).add(Integer.parseInt(integerStrings[i]));
                        }
                    }
                    // ajout du biais
                    data.get(j).add(1, 1);
                }
                j++;
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
        return data;
    }

    // 100% avec le set "and" et le set "or"
    // 75% 50% ou 25% avec le set "xor" -> on a vu que c'était normal
    // environ 62% avec le set "monks"
    public static void main(String[] args){
        // lecture du fichier
        DecimalFormat f = new DecimalFormat("##.00");
        ArrayList<ArrayList<Integer>> data_train = read_file("./data/monks-1.train");
        // apprentissage
        ArrayList<Double> finalWeights = train(data_train);
        System.out.println("\nListe des poids:");
        for(int i = 0; i < finalWeights.size(); i+=1){
            System.out.println("  w" + i + "=" + f.format(finalWeights.get(i)));
        }
        // test sur les poids retournés pour valider l'apprentissage
        ArrayList<ArrayList<Integer>> data_test = read_file("./data/monks-1.test");
        int count = 0;
        for(ArrayList<Integer> item : data_test){
            count += (item.get(0) == test(item, finalWeights)) ? 1 : 0;
        }
        System.out.println("\nTaux d'apprentissage: " + f.format(Double.valueOf(count) / Double.valueOf(data_test.size()) * 100.0) +"%");
    }
}