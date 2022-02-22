import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public class PGM{
    private String header;
    private List<BigInteger> content;

    public PGM(){
        this.header = "";
        this.content = new ArrayList<>();
    }

    public void readFile(String filename){
        try{
            FileReader fr = new FileReader(filename);
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();

            //read header
            this.header += line;
            do{
                line = br.readLine();
                this.header += "\n" + line;
            }
            while(line != null && line.charAt(0) == '#');
            this.header += "\n" + br.readLine();
            
            // read content
            line = br.readLine();
            while(line != null){
                for(String item : line.split("\\s+")){
                    try{
                        Integer tmp = Integer.parseInt(item.trim());
                        this.content.add(new BigInteger(tmp.toString()));
                    } catch (NumberFormatException e){}
                }
                line = br.readLine();
            }
            br.close();
        }
        catch (FileNotFoundException e1){
            System.out.println("File \"" + filename + "\" not found.");
        }
        catch (IOException e2){
            System.out.println("Error while parsing file:");
            e2.printStackTrace();
        }
    }

    public String getHeader(){
        return this.header;
    }

    public List<BigInteger> getContent(){
        return this.content;
    }

    public static void writeFile(String filename, String header, List<BigInteger> content){
        try{
            FileWriter fw = new FileWriter(filename);
            BufferedWriter bw = new BufferedWriter(fw);
            String newContent = "";
            for(BigInteger i : content){
                newContent += i.toString() + " ";
            }
            bw.write(header + "\n" + newContent);
            bw.newLine();
            bw.flush();
            bw.close();
        }
        catch (FileNotFoundException e1){
            System.out.println("File \"" + filename + "\" not found.");
        }
        catch (IOException e2){
            e2.printStackTrace();
        }
    }
}