import java.io.*;
import java.util.*;

// il y a un problème avec le choix 11 du fichier 9

public class Main {

    public static void main(String[] args) throws IOException {
        // permet de prendre les entrées pour le menu
        // soit du clavier, d'un fichier ou de la ligne de commande
        Scanner in;
        switch (args.length) {
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

        String filePath = System.getProperty("user.dir") + File.separator + "villes.xml";
        XMLManager xml = new XMLManager();
        Cities cities = xml.XMLReader("villes.xml");
        Matrix mat;
        FloydWarshall fw;
        Dijkstra d;
        System.err.println("Le fichier XML " + filePath + " a été chargé\n");
        int choix = 0;
        do {
            // les impressions du menu sont envoyées sur le canal d'erreur
            // pour les différencier des sorties de l'application
            // lesquelles sont envoyées sur la sortie standard
            System.err.println("Choix  0: quitter");
            System.err.println("Choix  1: liste des villes");
            System.err.println("Choix  2: matrice des poids");
            System.err.println("Choix  3: liste des poids");
            System.err.println("Choix  4: matrice des temps de parcours (Floyd)");
            System.err.println("Choix  5: matrice des précédences (Floyd)");
            System.err.println("Choix  6: temps de parcours entre deux villes (Floyd)");
            System.err.println("Choix  7: parcours entre deux villes (Floyd)");
            System.err.println("Choix  8: tableau des temps de parcours (Dijkstra)");
            System.err.println("Choix  9: tableau des précédences (Dijkstra)");
            System.err.println("Choix 10: temps de parcours entre deux villes (Dijkstra)");
            System.err.println("Choix 11: parcours entre deux villes (Dijkstra)");
            System.err.println("Choix 12: ajout d'une ville");
            System.err.println("Choix 13: ajout d'une liaison");
            System.err.println("Choix 14: suppression d'une ville");
            System.err.println("Choix 15: suppression d'une liaison");
            System.err.println("Choix 16: graphe connexe?");
            System.err.println("Choix 17: sauver (format XML)"); 
            System.err.println("Entrez votre choix: ");
            choix = in.nextInt();
            String str1, str2, str3;
            switch (choix) {
            case 1:
                cities.print();
                break;
            case 2:
                mat = new Matrix(cities.size(), cities.size());
                mat.fill(cities);
                mat.print();
                break;
            case 3:
                cities.printWeight();
                break;
            case 4:
                fw = new FloydWarshall(cities);
                mat = fw.getMatWeight();
                mat.print();
                break;
            case 5:
                fw = new FloydWarshall(cities);
                mat = fw.getMatNext();
                mat.print();
                break;
            case 6:
                System.err.println("Ville d'origine:");
                str1 = in.next();
                System.err.println("Ville de destination:");
                str2 = in.next();
                System.err.print("Distance: ");
                fw = new FloydWarshall(cities);
                System.out.println(fw.getWeightFromNames(str1, str2));
                break;
            case 7:
                System.err.println("Ville d'origine:");
                str1 = in.next();
                System.err.println("Ville de destination:");
                str2 = in.next();
                System.err.print("Parcours: ");
                fw = new FloydWarshall(cities);
                fw.printPathFromNames(str1, str2);
                break;
            case 8:               
                System.err.println("Ville d'origine:");
                str1 = in.next();
                d = new Dijkstra(cities.size());
                d.applyDijkstra(cities.getCityFromName(str1), cities);
                d.printDist(cities);
                break;
            case 9:
                System.err.println("Ville d'origine:");
                str1 = in.next();
                d = new Dijkstra(cities.size());
                d.applyDijkstra(cities.getCityFromName(str1), cities);
                d.printPrev(cities);
                break;
            case 10:
                System.err.println("Ville d'origine:");
                str1 = in.next();
                System.err.println("Ville de destination:");
                str2 = in.next();
                System.err.print("Distance: ");
                d = new Dijkstra(cities.size());
                d.applyDijkstra(cities.getCityFromName(str1), cities);
                d.printDist(cities, str2);
                break;
            case 11:
                System.err.println("Ville d'origine:");
                str1 = in.next();
                System.err.println("Ville de destination:");
                str2 = in.next();
                System.err.print("Parcours: ");
                d = new Dijkstra(cities.size());
                d.applyDijkstra(cities.getCityFromName(str1), cities);
                d.printPrev(cities, str2);
                break;
            case 12:
                System.err.println("Nom de la ville:");
                str1 = in.next();
                //System.err.println("latitude:");
                //str2 = in.next();
                //System.err.println("longitude:");
                //str3 = in.next();
                //cities.add(new City(str1, Integer.parseInt(str2), Integer.parseInt(str3)));
                cities.add(new City(str1, 0, 0));
                break;
            case 13:
                System.err.println("Ville d'origine:");
                str1 = in.next();
                System.err.println("Ville de destination:");
                str2 = in.next();
                System.err.println("Temps de parcours:");
                str3 = in.next();
                cities.addNeighbours(str1, str2, Integer.parseInt(str3));
                break;
            case 14:
                System.err.println("Nom de la ville:");
                str1 = in.next();
                cities.removeByName(str1);
                break;
            case 15:
                System.err.println("Ville d'origine:");
                str1 = in.next();
                System.err.println("Ville de destination:");
                str2 = in.next();
                cities.removeNeighboursByName(str1, str2);
                break;
            case 16:
                fw = new FloydWarshall(cities);
                System.out.println(fw.checkConectivity());
                break;
            case 17:
                System.err.println("Nom du fichier XML:");
                xml.XMLWriter(cities, in.next());
                break;
            }
        } while (choix != 0);
    }
}