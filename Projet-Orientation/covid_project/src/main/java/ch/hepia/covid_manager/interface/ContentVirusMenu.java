package ch.hepia.covid_manager;

import java.util.Map;
import java.util.LinkedHashMap;
import java.util.ArrayList;
import java.util.List;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.control.*;
import javafx.scene.paint.Color;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.Group;
import javafx.scene.input.MouseEvent;
import javafx.scene.Parent;
import javafx.scene.shape.Line;
import javafx.geometry.Insets;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.util.Duration;

/* Class used to add the content that will be displayed
 * in the cure side bar menu
 */
class ContentVirusMenu extends Group{

    private LinkedHashMap<Button, Perk> map;
    private List<Line> lines;

    private Button infectivity;
    private Button lethality;
    private Button resistance;
    private Label infos;

    private int status;

    private HBox topSection;
    private VBox currentMenu;
    private VBox buttonMenu;

    ContentVirusMenu(LinkedHashMap<Button, Perk> map, int width, int height){       
        this.lines = new ArrayList<>();
        this.topSection = new HBox();
        this.currentMenu = new VBox();
        this.buttonMenu = new VBox();
        this.status = 1;
        
        this.infos = new Label();
        this.infos.setWrapText(true);
        this.infos.setMinWidth(200);
        this.infos.setMinHeight(40);
        this.infos.setTextFill(Color.WHITE);
        this.infos.setStyle("-fx-font-size: 2em;");
        this.infos.setTranslateX(width / 2 - 125);
        this.infos.setTranslateY(height - 400);

        this.map = map;

        for(Button b: map.keySet()){
            Tooltip t = new Tooltip(map.get(b).toString());
            t.setShowDelay(new Duration(500));
            t.setHideDelay(new Duration(50));
            b.setTooltip(t);
        }

        this.generateMenuHeader();
        this.updateMenu();
        this.generatePerkButtons();
        this.generateLines();

        this.currentMenu.getChildren().add(this.buttonMenu);
        this.currentMenu.getChildren().add(this.infos);        
        this.getChildren().add(this.currentMenu);
    }

    // lines that link every buttons
    private void generateLines(){
        for(int i = 0; i < 4; i+=1){
            double x1 = (20 + 1*120);
            double x2 = (20 + 2*120);
            double x3 = (20 + 3*120);
            double y = (140 + i*160.5);

            Line lineb1b2 = new Line(x1,y, x2,y);
            lineb1b2.setStrokeWidth(5);
            lineb1b2.setViewOrder(10);
            
            Line lineb2b3 = new Line(x2,y,x3,y);
            lineb2b3.setStrokeWidth(5);  
            lineb2b3.setViewOrder(10);

            this.lines.add(lineb1b2);
            this.lines.add(lineb2b3);
        }
    }

    public void updateLines(){
        this.getChildren().removeAll(this.lines);
        int offset = 0;
        for(int i = 0 ; i < 8 ; i+=2){
            this.colorLines(this.lines.get(i), this.lines.get(i+1), (this.status-1)*12 + i + offset);
            offset +=1;
        }
        this.getChildren().addAll(this.lines);
    }


    private void colorLines(Line l1, Line l2, int i){
        List<Button> buttons = generateButtonList();
        
        if(Virus.getInstance().hasPerk(this.map.get(buttons.get(i)))){
            l1.setStroke(Color.WHITE);
        }else{
            l1.setStroke(Color.BLACK);
        }

        if(Virus.getInstance().hasPerk(this.map.get(buttons.get(i+1)))){
            l1.setStroke(Color.GREEN);
            l2.setStroke(Color.WHITE);
        }else{
            l2.setStroke(Color.BLACK);
        }
        
        if(Virus.getInstance().hasPerk(this.map.get(buttons.get(i+2)))){
            l2.setStroke(Color.GREEN);
        }
    }

    private void updateButtonStates(){
        List<Button> buttons = generateButtonList();
        buttons.forEach(b->{
            if(Virus.getInstance().hasEnoughPoints(map.get(b))){
                b.setStyle("-fx-background-color: white;-fx-font-size: 1.5em;-fx-border-color: black;-fx-border-width:3px;");
                b.setOnAction(e -> {
                    Virus.getInstance().upgrade(map.get(b));
                    this.generatePerkButtons();
                    this.refreshDisplay();
                    this.infos.setText("New perk purchased!");
                });
            }else{
                b.setStyle("-fx-background-color: grey;-fx-font-size: 1.5em;-fx-border-color: black;-fx-border-width:3px;");
                b.setOnAction(e -> {
                    this.infos.setText("Not enough points!");
                });
            }
            if(Virus.getInstance().hasPerk(this.map.get(b))){
                b.setStyle("-fx-border-color: green; -fx-border-width: 3px;-fx-font-size: 1.5em");
                b.setOnAction(e -> {
                    this.infos.setText("Perk already unlocked!");
                });
            }
            int index = buttons.indexOf(b);
            if(index % 3 != 0){
                if(!Virus.getInstance().hasPerk( map.get(buttons.get(index - 1)) ) ){
                    b.setStyle("-fx-background-color: grey;-fx-font-size: 1.5em;-fx-border-color: black;-fx-border-width:3px;");
                    b.setOnAction(e -> {
                        this.infos.setText("Unlock previous perk!");
                    });
                }
            }
        });        
    }

    public void refreshDisplay(){
        this.updateButtonStates();
        this.updateLines();
        this.updateLabel();
    }



    private List<Button> generateButtonList(){
        List<Button> buttons = new ArrayList<>();
        for(Button b: map.keySet()){
            buttons.add(b);
        }
        return buttons;
    }


    private Button generateMenuButtons(String label, int pos){
        Button b = new Button(label);
        b.setTextFill(Color.WHITE);
        b.setStyle("-fx-border-color: #fff;-fx-border-width: 3;-fx-background-color: transparent;-fx-font-size: 1.5em;-fx-border-radius: 5px;");
        b.setTranslateX(7 * pos);
        b.hoverProperty().addListener( e -> {
            this.updateMenu();
        });
        return b;
    }

    private void generateMenuHeader(){
        this.infectivity = generateMenuButtons("Transmission", 1);
        this.infectivity.setOnAction(e -> {
            if(this.status != 1){
                this.status = 1;
                this.generatePerkButtons();
                this.refreshDisplay();
                this.updateMenu();
            }
        });
        topSection.getChildren().add(this.infectivity);
        
        this.lethality = generateMenuButtons("Lethality", 2);
        this.lethality.setOnAction(e -> {
            if(this.status != 2){
                this.status = 2;
                this.generatePerkButtons();
                this.refreshDisplay();
                this.updateMenu();
            }
        });
        topSection.getChildren().add(this.lethality);
        
        this.resistance = generateMenuButtons("Resistance", 3);
        this.resistance.setOnAction(e -> {
            if(this.status != 3){
                this.status = 3;
                this.generatePerkButtons();
                this.refreshDisplay();
                this.updateMenu();
            }
        });
        topSection.getChildren().add(this.resistance);
        this.currentMenu.getChildren().add(topSection);
        this.currentMenu.setMargin(topSection, new Insets(10, 0, 60, 30));
    }

    private void generatePerkButtons(){
        List<Button> buttons = this.generateButtonList();
        this.buttonMenu.getChildren().clear();

        for(int i = 0; i < 4; i++){
            HBox tmp = new HBox();
            for(int j = 0; j < 3; j++){
                Button b = buttons.get(i*3+j + 12*(this.status - 1));
                tmp.getChildren().add(b);
                tmp.setTranslateY((100 * i)+1);
                tmp.setMargin(b, new Insets(0,30,0,0));
            }
            this.buttonMenu.getChildren().add(tmp);
            this.buttonMenu.setMargin(tmp, new Insets(0, 0, 0, 30));
        }
        this.buttonMenu.getChildren().add(this.infos);
        this.buttonMenu.setViewOrder(0);
    }

    public void updateLabel(){
        this.infos.setText("");
    }

    private void updateMenu(){
        if(this.status == 1){
            emphasisButton(this.infectivity);
            clearButton(this.lethality);
            clearButton(this.resistance);
        } else if(this.status == 2){
            clearButton(this.infectivity);
            emphasisButton(this.lethality);
            clearButton(this.resistance);
        } else if(this.status == 3){
            clearButton(this.infectivity);
            clearButton(this.lethality);
            emphasisButton(this.resistance);
        }
    }

    private void emphasisButton(Button b){
        b.setTextFill(Color.web("0x808080"));
        b.setStyle("-fx-border-color: #808080;-fx-border-width: 3;-fx-background-color: transparent;-fx-font-size: 1.5em;-fx-border-radius: 5px;");
    }

    private void clearButton(Button b){
        b.setTextFill(Color.WHITE);
        b.setStyle("-fx-border-color: #fff;-fx-border-width: 3;-fx-background-color: transparent;-fx-font-size: 1.5em;-fx-border-radius: 5px;");
    }
}
