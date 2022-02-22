import java.io.*;
import java.util.*;
import java.math.*;

public class Main{
    public static void main(String[] args) throws IOException{
        Scanner in;
        switch(args.length){
            case 0:
                in = new Scanner(System.in);
                break;
            case 1:
                in = new Scanner(new File(args[0]));
                break;
            default:
                String source = args[0];
                for (int i = 1; i < args.length; i++)
                   source += " " + args[i];
                in = new Scanner(source);
        }

        System.err.println("Mot en clair de (r+1)-bits à encoder sur (2^r)-bits.");
        System.err.println("Choisir la valeur de r: ");
        int r = in.nextInt();
        System.err.println("\nLe seuil de bruit est la probabilité d'inverser un bit.");
        System.err.println("Choisir un seuil de bruit (nombre entre 0.0 et 1.0): ");
        double seuil = in.nextDouble();
        
        System.err.println("\nMenu initial");
        System.err.println("0: Quitter");
        System.err.println("1: Traiter un mot");
        System.err.println("2: Traiter une image");
        int mode = in.nextInt();
        
        BigInteger mot = new BigInteger("0");
        ReedMuller rm = new ReedMuller(r);
        Bruitage b = new Bruitage();

        String menu = "\nMenu opérations\n" 
            + "0: Quitter\n" 
            + "1: Encoder\n" 
            + "2: Décoder\n" 
            + "3: Bruiter\n"
            + "4: Débruiter\n" 
            + "5: Débruiter + décoder (rapide)\n" 
            + "6: Réinitialiser\n" 
            + "Opération choisie:";
        int choix = 6;
        if(mode == 1){
            do{
                switch(choix){
                    case 1:
                        mot = rm.codage(mot);
                        break;
                    case 2:
                        mot = rm.decodage(mot);
                        break;
                    case 3:
                        mot = b.bruit(mot, seuil);
                        break;
                    case 4:
                        mot = rm.debruitageSemiExhaustif(mot);
                        break;
                    case 5:
                        mot = rm.debruitageDecodage(mot);
                        break;
                    case 6:
                        System.err.println("\nEntrer un mot (en décimal de 0 à " + (2 << r) + ")");
                        mot = new BigInteger(in.next());
                        break;
                }
                if(choix != 6){
                    System.out.println(mot);
                    System.out.println(mot.toString(2));
                }
                System.err.println(menu);
                choix = in.nextInt();
            } while (choix != 0);
        } else if(mode == 2){
            choix = 6;
            PGM myFile = new PGM();
            String fileName = "";
            List<BigInteger> content = new ArrayList<>();
            do{
                switch(choix){
                    case 1:
                        content = rm.codage(content);
                        break;
                    case 2:
                        content = rm.decodage(content);
                        break;
                    case 3:
                        content = b.bruit(content, seuil);
                        break;
                    case 4:
                        content = rm.debruitageSemiExhaustif(content);
                        break;
                    case 5:
                        content = rm.debruitageDecodage(content);
                        break;
                    case 6:
                        System.err.println("Nom du fichier de l'image à charger (format pgm):");
                        fileName = in.next();
                        myFile.readFile(fileName);
                        content = myFile.getContent();
                        break;
                }
                if(choix != 6){
                    System.err.println("Nom du fichier où sauver l'image courante (format pgm):");
                    fileName = in.next();
                    PGM.writeFile(fileName, myFile.getHeader(), content);
                }
                System.err.println(menu);
                choix = in.nextInt();
            } while(choix != 0);
        }
        in.close();
    }
}