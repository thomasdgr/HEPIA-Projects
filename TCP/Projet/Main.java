import java.io.*;
import java.util.*;

public class Main {

    // affichage de la table des Symboles
    public static void TDStoString(HashMap<String, Symbole> TDS){
        for (String k : TDS.keySet()){
            System.out.println("\t" + TDS.get(k).toString());
        }
        System.out.println();
    }
    public static void main(String[] args) {
        System.out.println("\n\n\n");
        System.out.printf("# Fichier testé : %-41s\n\n", args[0]);
		try {
			FileReader myFile = new FileReader(args[0]);
			Lexer myTP = new Lexer(myFile);
			parser myP = new parser(myTP);
			try {
				// on lance le parsing, et on récupère l'AST
                ProgramDeclaration program = (ProgramDeclaration)myP.parse().value;
                if (program == null){
                    System.out.println("Unable to create tree from this input");
                    return;
                }

                // on récupère la TDS générée dans le CUP et on l'affiche
                System.out.println("Table des symboles :");
                HashMap<String, Symbole> TDS = program.getTDS();
                TDStoString(TDS);

                // on parcours notre AST pour afficher le code source qui a été lu
                SourceCodeGenerator sourceGenerator = new SourceCodeGenerator();
                System.out.println("Lecture de l'arbre abstrait :");
                program.accept(sourceGenerator);
                System.out.println(sourceGenerator.getCode());
                
                // même démarche que le code source, cette fois-ci on vérifie la sémantique
                SemanticAnalyzer kek = new SemanticAnalyzer(TDS);
                System.out.print("\nAnalyse Sémantique :");
                program.accept(kek);
                System.out.println(" OK");

                // même démarche que la sémantique, cette fois-ci on génère le bytecode
                CodeProducer kek2 = new CodeProducer(TDS);
                System.out.print("\nProduction du Code : ");
                program.accept(kek2);
                
                // création et écriture du fichier contenant le bytcode généré
                File f = new File("main.j");
                FileOutputStream oFile = new FileOutputStream(f, false); 
                PrintWriter out = new PrintWriter("main.j");
                out.println(kek2.cible());
                out.close();

                // pour toute exception générée au cours du processus
                } catch (Exception e) {
                    System.out.println("Error: " + e);
                    e.printStackTrace();
                }
 		}
		catch(Exception ignored) {
			System.out.printf("invalid file");
        }
	}
}
