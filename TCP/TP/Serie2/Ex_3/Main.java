import java.io.*;

public class Main {
	public static void main(String[] args) {
        System.out.println("\n\n\n");
        System.out.printf("# Fichier testé : %-41s\n\n", args[0]);
		try {
			FileReader myFile = new FileReader(args[0]);
			Lexer myTP = new Lexer(myFile);
			parser myP = new parser(myTP);
			try {myP.parse();}
			catch (Exception ignored) {
				System.out.printf("parse error");
			}
 		}
		catch(Exception ignored) {
			System.out.printf("invalid file");
        }
        System.out.println();
	}
}
