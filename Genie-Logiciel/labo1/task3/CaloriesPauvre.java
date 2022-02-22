import java.util.Arrays;

public class CaloriesPauvre implements Calories{
    private String[][] array = { {"Banane", "Ananas", "Fraise", "Orange"},
                                 {    "30",     "33",     "36",     "39"} };

    public CaloriesPauvre(){}

    public String calculCalories(String nom){
        return array[1][Arrays.asList(array[0]).indexOf(nom)];
    }
} 