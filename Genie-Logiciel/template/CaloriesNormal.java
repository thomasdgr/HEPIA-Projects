import java.util.Arrays;

public class CaloriesNormal implements Calories{
    private String[][] array = { {"Banane", "Ananas", "Fraise", "Orange"},
                                 {    "40",     "43",     "46",     "49"} };

    public CaloriesNormal(){}

    public String calculCalories(String nom){
        return array[1][Arrays.asList(array[0]).indexOf(nom)];
    }
} 