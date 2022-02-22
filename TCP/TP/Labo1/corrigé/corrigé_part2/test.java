import java.io.*;

public class test {
	public static void main(String[] args) {
        
        System.out.println("#############################################################");
        System.out.println("#          Labo3 : JFlex et CUP -- Analyseur SGML           #");
        System.out.println("#############################################################");
        System.out.println("# Auteur : Michaël MINELLI                                  #");
        System.out.println("# Classe : ITI Jour 2ème                                    #");
        System.out.println("#                                                           #");
        System.out.printf("# Fichier testé : %-41s #\n", args[0]);
        System.out.println("#############################################################");
        System.out.println("#                        Résultat                           #");
        System.out.println("#############################################################");
        
		try {
            
			FileReader myFile = new FileReader(args[0]);
			Labo3 myTP = new Labo3(myFile);
			parser myP = new parser(myTP);
			try {myP.parse();}
			catch (Exception ignored) {
				System.out.printf("parse error");
			}
 		}
		catch(Exception ignored) {
			System.out.printf("invalid file");
        }
        
        System.out.println("#############################################################");
	}
}
