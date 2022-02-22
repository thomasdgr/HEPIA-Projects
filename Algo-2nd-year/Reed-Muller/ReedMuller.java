import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

//Nice code bro -ABL


public class ReedMuller{
    private int r;
    private int length;

    private int[][] G;
    private ArrayList<BigInteger> table;

    public ReedMuller(int r){
        this.r = r;
        this.length = (int)Math.pow(2, this.r);
        // construction de la matrice générale G
        this.G = new int[this.r + 1][this.length];
        for(int i = 0; i < length; i++){
            String i_binary = Integer.toBinaryString(i);
            String i_reverse = new StringBuilder(i_binary).reverse().toString();
            for(int j = 0; j < this.r; j++){
                if(j <= i_reverse.length() - 1){
                    this.G[j][i] = (j <= i_reverse.length() - 1) ? Integer.parseInt(String.valueOf(i_reverse.charAt(j))) : 0;
                }
            }
        }
        // la dernière ligne c'est que des 1
        for(int i = 0; i < this.length; i++){
            this.G[this.r][i] = 1;
        }
        // génération de la table des éléments
        this.table = new ArrayList<>();
        for(int x = 0; x < (int) Math.pow(2, this.r + 1); x++){
            this.table.add(codage(BigInteger.valueOf(x)));
        }
        System.out.println("\nr: " + this.r);
        System.out.println("\nlength: " + this.length);
        System.out.println("\nmatrice G: ");
        for(int[] kek : this.G){
            for(int i : kek){
                System.out.print(i + " ");
            }
            System.out.println();
        }
        System.out.println("\ntable: ");
        for(BigInteger i : this.table){
            System.out.println(i.toString());
        }
    }

    public BigInteger codage(BigInteger mot){
        BigInteger motCode = new BigInteger("0");
        int somme = 0;
        for(int i = 0; i < this.G[0].length; i++){
            for(int j = 0; j < this.r + 1; j++){
                int newBit = (mot.testBit(j)) ? 1 : 0;
                somme += newBit * this.G[j][i];
            }
            if((somme % 2) == 1){
                motCode = motCode.setBit(i);
            }
            somme = 0;
        }
        return motCode;
    }

    public BigInteger decodage(BigInteger motCode){
        BigInteger motDecode = new BigInteger("0");
        // si le nombre binaire est négatif, on inverse tous bits
        if(motCode.testBit(0)){
            motCode = motCode.not();
            motDecode = motDecode.setBit(r);
        }
        // pour chaque puissance de 2 plus petite que r, on stock la position
        for(int i = 0; i < this.r; i++){
            motDecode = (motCode.testBit((int) Math.pow(2, i))) ? motDecode.setBit(i) : motDecode.clearBit(i);
        }
        return motDecode;
    }

    // calcul la distance de hamming entre 2 mots (nombre de bits différents entre 2 mots)
    private int hamming(BigInteger mot1, BigInteger mot2){
        int d = 0;
        for(int i = 0; i < Integer.max(mot1.bitLength(), mot2.bitLength()); i++){
            if(mot1.testBit(i) != mot2.testBit(i)){
                d++;
            }
        }
        return d;
    }

    public BigInteger debruitageSemiExhaustif(BigInteger mot){
        int closer = -1;
        int distance = Integer.MAX_VALUE;
        for(int i = 0; i < table.size(); i++){
            int newDistance = hamming(mot, this.table.get(i));
            // calcule de la première moitié
            if(newDistance < distance){
                closer = i;
                distance = newDistance;
            }
            // calcule de la seconde moitié
            if(this.length - newDistance < distance){
                distance = this.length - newDistance;
                closer = i + this.length;
            }
        }
        return this.table.get(closer);
    }

    // methode rapide -> doit prendre un mot codé et bruité
    public BigInteger debruitageDecodage(BigInteger mot){
        // on remplace tous les 0 par des 1 et tous les 1 par des -1
        // car c'est plus efficace que la distance de hamming
        int[] F = new int[this.length];
        for(int i = 0; i < this.length; i++){
            F[i] = (mot.testBit(i)) ? -1 : 1;
        }
        // on calcul F à partir des nouvelles données
        for(int i = 0; i < this.r; i++){
            int[] newF = new int[this.length];
            for (int k = 0; k < Math.pow(2, this.r); k++){
                BigInteger q = BigInteger.valueOf(k).flipBit(i);
                newF[k] = (q.testBit(i)) ? F[k] + F[q.intValue()] : F[q.intValue()] - F[k];
            }
            F = newF;
        }
        // on transforme F en prennant la valeur absolue en chaque point de F
        ArrayList<Integer> absF = new ArrayList<>();
        for(int i = 0; i < F.length; i++){
            absF.add(Math.abs(F[i]));
        }
        // on a besoin de la plus grande valeur présente dans F
        int maxF = Collections.max(absF);
        return (F[absF.indexOf(maxF)] < 0) ? 
            new BigInteger(Integer.toString((absF.indexOf(maxF) + this.length))) : 
            new BigInteger(Integer.toString(absF.indexOf(maxF)));
    }

    // PARTIE POUR LES IMAGES
    public List<BigInteger> codage(List<BigInteger> content){
        List<BigInteger> newContent = new ArrayList<>();
        // pour chaque valeur du pgm, on appelle la fonction deja faite pour les BigInteger
        for(BigInteger i : content){
            newContent.add(codage(i));
        }
        return newContent;
    }

    public List<BigInteger> decodage(List<BigInteger> content){
        List<BigInteger> newContent = new ArrayList<>();
        for(BigInteger i : content){
            newContent.add(decodage(i));
        }
        return newContent;
    }

    public List<BigInteger> debruitageSemiExhaustif(List<BigInteger> content){
        List<BigInteger> newContent = new ArrayList<>();
        for(BigInteger i : content){
            newContent.add(debruitageSemiExhaustif(i));
        }
        return newContent;
    }

    public List<BigInteger> debruitageDecodage(List<BigInteger> content){
        List<BigInteger> newContent = new ArrayList<>();
        for(BigInteger i : content){
            newContent.add(debruitageDecodage(i));
        }
        return newContent;
    }
}