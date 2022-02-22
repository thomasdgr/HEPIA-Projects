import java.util.Arrays;

public class CaloriesEnrichi implements Calories{
    private String[][] array = { {"Banane", "Ananas", "Fraise", "Orange"},
                                 {    "50",     "53",     "56",     "59"} };

    public CaloriesEnrichi(){}

    public String calculCalories(String nom){
        return array[1][Arrays.asList(array[0]).indexOf(nom)];
    } 
} 
