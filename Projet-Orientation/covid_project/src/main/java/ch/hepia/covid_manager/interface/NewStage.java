package ch.hepia.covid_manager;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.stage.Modality;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.text.Text;
import javafx.scene.paint.Color;
import javafx.geometry.Insets;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;

import java.time.LocalDate;

class NewStage {

    NewStage(Country c, Stage primaryStage, double x, double y, LocalDate date, CasesBar cb, Countries countries, int newWidth, int newHeight){
        Stage detailStage = new Stage();
        detailStage.setTitle(c.name());

        Text countryDetail = new Text("\n\n" + c.toString());
        c.updateCountryHistory();
        Text countryMoreDetail = new Text("\n\n" + c.realData(date));

        Boolean sw = true;
        Button btn1 = new Button();
        btn1.setText("More informations");
        btn1.setOnAction(aevent -> { toggleStage(detailStage); });

        Button btn2 = new Button();
        btn2.setText("X");
        btn2.setStyle("-fx-background-color: transparent; -fx-font-weight: bold");
        btn2.setOnAction(aevent -> {
            cb.setDisplay(false);
            cb.update(countries, newWidth, newHeight);
            detailStage.hide();
        });
        
        VBox detailRoot = new VBox();
        detailRoot.getChildren().add(btn2);
        detailRoot.getChildren().add(countryDetail);
        detailRoot.getChildren().add(btn1);
        detailRoot.getChildren().add(countryMoreDetail);

        VBox.setMargin(btn2, new Insets(5, 5, 0, 200));
        VBox.setMargin(btn1, new Insets(5, 0, 0, 5));
        VBox.setMargin(countryDetail, new Insets(-45, 0, -15, 5));
        VBox.setMargin(countryMoreDetail, new Insets(0, 0, 0, 5));

        Scene detailScene = new Scene(detailRoot, 0, 0, Color.BLACK);

        detailStage.setScene(detailScene);
        detailStage.initModality(Modality.APPLICATION_MODAL);
        detailStage.initOwner(primaryStage);
        detailStage.setX(x);
        detailStage.setY(y);
        detailStage.setWidth(230);
        detailStage.setHeight(150);
        detailStage.initStyle(StageStyle.UNDECORATED);
        detailStage.setOpacity(0.8);
        
        detailStage.focusedProperty().addListener((obs, wasFocused, isNowFocused) -> {
            if (! isNowFocused) {
                detailStage.hide();
            }
        });

        detailStage.show();
    }

    NewStage(Perk p, Stage primaryStage, double x, double y){
        Stage detailStage = new Stage();
        detailStage.setTitle(p.name());

        VBox detailRoot = new VBox();
        detailRoot.getChildren().add(new Text("\n\n" + p.description()));

        Scene detailScene = new Scene(detailRoot, 0, 0, Color.BLACK);

        detailStage.setScene(detailScene);
        detailStage.initModality(Modality.APPLICATION_MODAL);
        detailStage.initOwner(primaryStage);
        detailStage.setX(x);
        detailStage.setY(y);
        detailStage.setWidth(250);
        detailStage.setHeight(150);
        detailStage.initStyle(StageStyle.UNDECORATED);
        detailStage.setOpacity(0.8);
        
        detailStage.focusedProperty().addListener((obs, wasFocused, isNowFocused) -> {
            if (! isNowFocused) {
                detailStage.hide();
            }
        });

        detailStage.show();
    }

    void toggleStage(Stage detailStage){ 
        if(detailStage.getHeight() == 260){
            detailStage.setHeight(150);
        }else{
            detailStage.setHeight(260);
        }
    }
}