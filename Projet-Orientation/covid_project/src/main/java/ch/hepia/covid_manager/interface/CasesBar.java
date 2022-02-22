package ch.hepia.covid_manager;

import javafx.scene.paint.Color;
import javafx.scene.layout.Region;
import javafx.scene.shape.Rectangle;
import javafx.scene.control.Label;


/* Class used to display the cases according to the world or the country
 * we clicked on.
 * It shows the cases (in red), the cured (in blue),  the deaths (in black) and the other one (in green)
 */
public class CasesBar{

    private Region sickBar = new Region();
    private Region vaccinatedBar = new Region();
    private Region deathBar = new Region();
    private Rectangle healthyBar = new Rectangle();
    private Label barName = new Label("World");
    private boolean display;

    // each bar are layered over the others
    public CasesBar(int newWidth, int newHeight, Countries countries) {        
        this.healthyBar.setWidth(newWidth/3);
        this.healthyBar.setHeight(20.0);
        this.healthyBar.setFill(Color.GREEN);
        this.healthyBar.opacityProperty().set(0.75);
        this.healthyBar.setStroke(Color.WHITE);
        this.healthyBar.setStrokeWidth(3.0);
        this.healthyBar.setTranslateX(newWidth/3);
        this.healthyBar.setTranslateY(newHeight-47);
        this.healthyBar.setArcWidth(30.0);        
        this.healthyBar.setArcHeight(20.0);
        
        this.sickBar.opacityProperty().set(0.75);
        this.sickBar.setPrefSize((newWidth/(3.0 * countries.totalPop() / 100000.0)) * (countries.totalCases() / 100000.0), 16.0);
        this.sickBar.setStyle("-fx-background-color: red; -fx-background-radius: 10 0 0 10");
        this.sickBar.setTranslateX(newWidth/3 + 2);
        this.sickBar.setTranslateY(newHeight-45);
        
        this.deathBar.setPrefSize((newWidth/(3.0 * countries.totalPop() / 100000.0)) * (countries.totalDeaths() / 100000.0), 16.0);
        this.deathBar.setStyle("-fx-background-color: black; -fx-background-radius: 10 0 0 10");
        this.deathBar.setTranslateX(newWidth/3 + 2);
        this.deathBar.setTranslateY(newHeight-45);
        
        this.vaccinatedBar.opacityProperty().set(0.75);
        this.vaccinatedBar.setPrefSize((newWidth/(3.0 * countries.totalPop() / 100000.0)) * (countries.totalCured() / 100000.0), 16.0); //je mets 0 parce qu'on a pas de données
        this.vaccinatedBar.setStyle("-fx-background-color: blue; -fx-background-radius: 0 10 10 0");
        this.vaccinatedBar.setTranslateX(2*newWidth/3);
        this.vaccinatedBar.setTranslateY(newHeight-45);

        this.barName.setStyle("-fx-font-size: 1.4em;");
        this.barName.setTextFill(Color.WHITE);
        this.barName.setTranslateX(newWidth/2 - 30);
        this.barName.setTranslateY(newHeight - 73);

        this.barName.setPrefWidth(Region.USE_COMPUTED_SIZE);
        this.barName.setPrefHeight(Region.USE_COMPUTED_SIZE);
    }

    public Region getSickBar(){
        return this.sickBar;
    }

    public void setSickBar(double newWidth, double newHeight){
        this.sickBar.setPrefSize(newWidth, newHeight);
    }

    public Region getDeathBar(){
        return this.deathBar;
    }

    public void setDeathBar(double newWidth, double newHeight){
        this.deathBar.setPrefSize(newWidth, newHeight);        
    }

    public Region getVaccinatedBar(){
        return this.vaccinatedBar;
    }

    public void setVaccinatedBarX(double newWidth){
        this.vaccinatedBar.setTranslateX(newWidth);
    }

    public void setVaccinatedBar(double newWidth){
        this.vaccinatedBar.setPrefWidth(newWidth);
    }

    public Rectangle getHealthyBar(){
        return this.healthyBar;
    }

    public Label getBarName(){
        return this.barName;
    }

    public void setBarName(String newName){
        this.barName.setText(newName);
    }

    public void setDisplay(boolean value){
        this.display = value;
    }

    // update the bar to show the values of a specific country
    public void update(Country c, double newWidth, double newHeight){
        if(this.display){
            this.setSickBar((newWidth/(3.0 * c.totalPopulation() / 10000.0)) * (c.playerTotalCases() / 10000.0), 16.0);
            this.setDeathBar((newWidth/(3.0 * c.totalPopulation() / 10000.0)) * (c.playerTotalDeaths() / 10000.0), 16.0 );
            this.setVaccinatedBarX((2*newWidth/3) - (newWidth/(3.0 * c.totalPopulation() / 100000.0)) * (c.playerTotalCured() / 100000.0));
            this.setVaccinatedBar((newWidth/(3.0 * c.totalPopulation() / 100000.0)) * (c.playerTotalCured() / 100000.0));
            this.setBarName(c.name());
        }
    }

    // update the bar to show the values of the world
    public void update(Countries countries, double newWidth, double newHeight){
        if(!this.display){
            this.setSickBar((newWidth/(3.0 * countries.totalPop() / 10000.0)) * (countries.totalCases() / 10000.0), 16.0);
            this.setDeathBar((newWidth/(3.0 * countries.totalPop() / 10000.0)) * (countries.totalDeaths() / 10000.0), 16.0 );
            this.setVaccinatedBarX((2*newWidth/3) - (newWidth/(3.0 * countries.totalPop() / 100000.0)) * (countries.totalCured() / 100000.0));
            this.setVaccinatedBar((newWidth/(3.0 * countries.totalPop() / 100000.0)) * (countries.totalCured() / 100000.0));
            this.setBarName("World");
        }
    }
}