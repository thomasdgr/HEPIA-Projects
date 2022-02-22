package ch.hepia.covid_manager;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;
import java.util.Random; 

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class Country {
    // données communes
    private String name;
    private String slug;
    private int latitude;
    private int longitude;
    private int size;
    private int totalPopulation;

    // données joueur
    private int totalCases;
    private int dailyCases;
    private int totalDeaths;
    private int dailyDeaths;
    private int totalRecovered;
    private int dailyRecovered;
    private int totalCured;
    private int dailyCured;
    private int totalActive;
    private int nbPpl = 12;
    private int confinementDays;

    private Circle circles[];

    // données réelles
    private Map < LocalDate, Integer[] > countryHistory = new HashMap < > ();

    public Country(String name, int latitude, int longitude,
                   int totalCases, int dailyCases, 
                   int totalDeaths, int dailyDeaths, 
                   int totalRecovered, int dailyRecovered,
                   int size, int totalPopulation, String slug, int totalCured){

        this.slug = slug;
        this.name = name;
        this.latitude = latitude;
        this.longitude = longitude;
        this.totalCases = totalCases;
        this.dailyCases = dailyCases;
        this.totalDeaths = totalDeaths;
        this.dailyDeaths = dailyDeaths;
        this.totalRecovered = totalRecovered;
        this.dailyRecovered = dailyRecovered;
        this.totalCured = 0;
        this.dailyCured = 0;
        this.totalActive = totalCases - (totalRecovered + totalDeaths + totalCured);
        this.size = size;
        this.totalPopulation = totalPopulation;
        this.totalCured = totalCured;
    }

    public int playerTotalCases() {
        return this.totalCases;
    }

    public int playerDailyCases() {
        return this.dailyCases;
    }

    public int getTotalCasesByDate(LocalDate date) {
        if (this.countryHistory.keySet().contains(date)) {
            return this.countryHistory.get(date)[0];
        } else {
            // Should never be reached
            throw new RuntimeException("Date is not in the country's history");
        }
    }

    public int getDailyCasesByDate(LocalDate date) {
        return this.getTotalCasesByDate(date) - this.getTotalCasesByDate(date.minusDays(1));
    }

    public int playerTotalDeaths() {
        return this.totalDeaths;
    }

    public int playerDailyDeaths() {
        return this.dailyDeaths;
    }

    
    public void setTotalCured(int tc){
        this.totalCured = tc;
    }

    
    public int getTotalDeathsByDate(LocalDate date) {
        if (this.countryHistory.keySet().contains(date)) {
            return this.countryHistory.get(date)[1];
        } else {
            // Should never be reached
            throw new RuntimeException("Date is not in the country's history");
        }
    }

    public int getDailyDeathsByDate(LocalDate date) {
        return this.getTotalDeathsByDate(date) - this.getTotalDeathsByDate(date.minusDays(1));
    }

    public int playerTotalRecovered() {
        return this.totalRecovered;
    }

    public int playerDailyRecovered() {
        return this.dailyRecovered;
    }

    public int getTotalRecoveredByDate(LocalDate date) {
        if (this.countryHistory.keySet().contains(date)) {
            return this.countryHistory.get(date)[2];
        } else {
            // Should never be reached
            throw new RuntimeException("Date is not in the country's history");
        }
    }

    public int getDailyRecoveredByDate(LocalDate date) {
        return this.getTotalRecoveredByDate(date) - this.getTotalRecoveredByDate(date.minusDays(1));
    }

    public int playerTotalCured() {
        return this.totalCured;
    }

    public int playerDailyCured() {
        return this.dailyCured;
    }

    public int getTotalCuredByDate(LocalDate date) {
        if (this.countryHistory.keySet().contains(date)) {
            return this.countryHistory.get(date)[3];
        } else {
            // Should never be reached
            throw new RuntimeException("Date is not in the country's history");
        }
    }

    public int getDailyCuredByDate(LocalDate date) {
        return this.getTotalCuredByDate(date) - this.getTotalCuredByDate(date.minusDays(1));
    }
 
    public int playerTotalActive() {
        return this.totalActive;
    }

    public int getTotalActiveByDate(LocalDate date) {
        if (this.countryHistory.keySet().contains(date)) {
            return this.countryHistory.get(date)[3];
        } else {
            // Should never be reached
            throw new RuntimeException("Date is not in the country's history");
        }
    }

    public int size() {
        return this.size;
    }

    public int totalPopulation() {
        return this.totalPopulation;
    }
    
    public String slug() {
        return this.slug;
    }

    public String name() {
        return this.name;
    }

    public int[] coordinates() {
        return new int[] {this.latitude, this.longitude};
    }

    @Override
    public String toString() {
        return this.name + ":" +
            "\n\tcases: " + this.totalCases + " (+" + this.dailyCases + ")" +
            "\n\tactive: " + this.totalActive +
            "\n\tdeaths: " + this.totalDeaths + " (+" + this.dailyDeaths + ")" +
            "\n\tcured: " + this.totalCured + " (+" + this.dailyCured + ")" +
            "\n\trecovered: " + this.totalRecovered + " (+" + this.dailyRecovered + ")\n";
    }

    // display the data for a specific date (took from the api)
    public String realData(LocalDate date){
        if(date.isAfter(LocalDate.now().minusDays(2))){
            return "Real data Unvailable (You are \n  now in the future) " + date.toString() + ":" +
            "\n\tcases: ?? (??)" +
            "\n\tactive: ?? (??)" +
            "\n\trecovered: ?? (??)\n";
        }
        return "Real data for the " + date.toString() + ":" +
            "\n\tcases: " + this.getTotalCasesByDate(date) + " (+" + this.getDailyCasesByDate(date) + ")" +
            "\n\tactive: " + this.getTotalActiveByDate(date) +
            "\n\tdeaths: " + this.getTotalDeathsByDate(date) + " (+" + this.getDailyDeathsByDate(date) + ")" +
            "\n\trecovered: " + this.getTotalRecoveredByDate(date) + " (+" + this.getDailyRecoveredByDate(date) + ")\n";
    }

    // get the color to show the current situation of the country
    public Color getColorFromCountry() {
        double ratio = (double)this.playerTotalActive() / (double)this.totalPopulation();
        ratio += (double)this.playerDailyDeaths() / (double)this.totalPopulation();
        if (ratio <0.075){
            return Color.GREEN;
        } else if (ratio < 0.15){
            return Color.ORANGE;
        } else if (ratio < 0.8){
            return Color.RED;
        } else{
            return Color.GREY;
        }
    }

    // get the circle size based on the current situation of the country
    public double getCircleWidth() {
        double ratio = (double)this.playerTotalActive() / (double)this.totalPopulation();
        ratio += (double)this.playerDailyDeaths() / (double)this.totalPopulation();
        if (ratio <0.075){
            return 15;
        } else if (ratio < 0.15){
            return 20;
        } else {
            return 25;
        }
    }

    // call once to get history of the real situation for the country
    public void updateCountryHistory() {
        //Use API to read history
        if(this.countryHistory.keySet().size() == 0){
            APICountryManager ap = new APICountryManager("https://api.covid19api.com");
            try{
                this.countryHistory = ap.getCountryHistory(this).get();
            }catch(Exception e){
                throw new RuntimeException(e);
            }
        }
    }

    public Map<LocalDate, Integer[]> getCountryHistory(){
        return this.countryHistory;
    }

    // update country's data from the real ones at a specific date
    public void goToDate(LocalDate date){
        Integer[] data = this.countryHistory.get(date);
        this.totalActive =  this.getTotalActiveByDate(date);
        this.totalCases =  this.getTotalCasesByDate(date);
        this.totalDeaths =  this.getTotalDeathsByDate(date);
    }

    private void newCases(){
        //Chance to infect depends on whether or not masks are enforced etc...
        double chanceToInfect = Virus.getInstance().infectivity()*0.05;
        //This depends on the measures taken by the country ( i.e. confinement or remote work etc...)
        if(this.dailyCases >= this.totalPopulation / 2500 || this.dailyDeaths >= this.totalPopulation / 5000){
            this.confinementDays = 31;
        }
        if(this.confinementDays >    0){
            this.nbPpl = 4; // comme l'effet d'un confinement 
            chanceToInfect /= 3.0;
            this.confinementDays -= 1;
        } else if(this.dailyCases >= this.totalPopulation / 1250 || this.dailyDeaths >= this.totalPopulation / 2500){
            this.nbPpl = 8; // comme l'effet d'un couvre feu
            chanceToInfect /= 1.5;
        }
        int newCases = (int) Math.round(this.totalActive*this.nbPpl*chanceToInfect)+2;

        if (newCases < this.getTotalInfectible() && newCases >= 0){
            this.dailyCases = newCases;
            this.totalActive += newCases;
            this.totalCases += newCases;
        }else{
            this.dailyCases = 0;
        }       
    }

    private void newRecoveries(){
        Random rand = new Random();
        //Basic + inaccurate formula to find new recoveries
        double randDouble =  (rand.nextGaussian() + 1)*(0.01-Virus.getInstance().resistance());
        int newRecov = (int) Math.abs(randDouble * this.totalActive);


        this.totalActive = Math.max((this.totalActive -newRecov), 1);
        this.totalRecovered += newRecov;
    }

    private void newDeaths(){
        Random rand = new Random();
        //Basic + inaccurate formula to find new deaths
        double randDouble =  rand.nextGaussian()*0.05*Virus.getInstance().lethality() ;
        int newDead = (int) Math.abs(randDouble * this.totalActive);

        this.totalActive = Math.max((this.totalActive -newDead), 1);
        this.dailyDeaths = newDead;

        this.totalDeaths += newDead;
    }

    //People that get the vaccine
    private void newCured(){
        if(this.totalCases > 1000000){
            Random rand = new Random();  
            // The value is not accurate
            double randDouble =  rand.nextGaussian()*Cure.getInstance().impact();
            // we need to know the population that can be infected -> (totalpop-recovered-active-death-cured)
            int newCured = (int) Math.abs(randDouble * this.getTotalInfectible());
    
            this.totalCured += newCured;
        }
    }

    private void updateState(){
        //System.out.println("State updates not implemented yet");
    }


    //update everything as if a day has passed
    public void elapseDay(){
        this.newCases();
        this.newRecoveries();
        this.newDeaths();
        this.newCured();
        this.circles[1].setFill(this.getColorFromCountry());
        this.circles[0].setRadius(this.getCircleWidth() + 2);
        this.circles[1].setRadius(this.getCircleWidth());
    }   


    //Get an array of circles representing the country cirlce and a bigger, black circle to have an outline around the circle
    public Circle[] getCountryCircles() {
        this.circles =  new Circle[] {
            new Circle(this.latitude, this.longitude, this.getCircleWidth() + 2 , Color.BLACK ),
            new Circle(this.latitude, this.longitude, this.getCircleWidth() , this.getColorFromCountry())
        };
        return this.circles;
    }


    //Setters for initialization with the database

    public void setTotalCases(int val){
        this.totalCases = val;
    }

    public void setTotalActive(int val){
        this.totalActive = val;
    }

    public void setTotalDeaths(int val){
        this.totalDeaths = val;
    }

    public void setTotalRecovered(int val){
        this.totalRecovered = val;
    }

    private int getTotalInfectible(){
        return this.totalPopulation - this.totalActive - this.totalCured - this.totalDeaths - this.totalRecovered;
    }
}