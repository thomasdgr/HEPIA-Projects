package ch.hepia.covid_manager;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.scene.paint.LinearGradient;
import javafx.scene.paint.CycleMethod;
import javafx.scene.paint.Stop;
import javafx.scene.layout.Border;
import javafx.scene.layout.BorderStroke;
import javafx.scene.layout.BorderStrokeStyle;
import javafx.scene.text.Font;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.image.ImageView;
import javafx.scene.image.Image;
import javafx.scene.Scene;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.VBox;
import javafx.scene.layout.HBox;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.text.Text;
import javafx.scene.paint.Color;
import javafx.scene.layout.CornerRadii;
import javafx.geometry.Pos;
import javafx.geometry.Insets;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderWidths;

import javafx.animation.FadeTransition;
import javafx.util.Duration;




public class LoginWindow extends HBox{

    private User userT = new User(1, "ThomasKek");
    private User userA = new User(2, "Banantwan");
    private User userG = new User(3, "Amon-Gus");

    private Stage secondStage = new Stage();
    private boolean loggedIn = false;

    private Button start;
    private Button load;
    private HBox items;

    public LoginWindow(){}
    
    public void loginScene() {

        this.start = this.generateMenuButtons("Start");
        this.load = this.generateMenuButtons("Continue");
        
        this.items = new HBox();
        this.items.setVisible(false);
        this.items.setOnMouseMoved(e -> {
            this.items.setVisible(false);    
        });

        VBox loginT = this.createUserVBox(this.userT, "images/user1.png");
        VBox loginA = this.createUserVBox(this.userA, "images/user2.png");
        VBox loginG = this.createUserVBox(this.userG, "images/user3.png");

        loginT.setAlignment(Pos.CENTER);
        loginA.setAlignment(Pos.CENTER);
        loginG.setAlignment(Pos.CENTER);
        this.items.setAlignment(Pos.CENTER);


        HBox loginHBox = new HBox(); 
        loginHBox.getChildren().addAll(loginT, loginA, loginG); 
        loginHBox.setAlignment(Pos.CENTER);
        
        makeFadeIn(loginHBox);

        Label label = new Label("Who's playing?");
        label.setStyle("-fx-text-fill: #ffffff; -fx-font-size: 64px;");
        label.setAlignment(Pos.CENTER);
        label.setMinWidth(1400);

        VBox loginVBox = new VBox();
        loginVBox.getChildren().addAll(label, loginHBox, this.items);
        loginVBox.setMargin(this.items, new Insets(30, 0, 0, 0));

        loginVBox.setAlignment(Pos.CENTER);
        loginVBox.setSpacing(35);

        Image img = new Image(this.getClass().getClassLoader().getResourceAsStream("images/logo.png"));
        ImageView logo = new ImageView(img);
        logo.setFitWidth(175);
        logo.setFitHeight(155);
        logo.setOpacity(0.85);

        BorderPane loginRoot = new BorderPane();
        loginRoot.setTop(logo);
        loginRoot.setCenter(loginVBox);
        loginRoot.setPrefSize(1200, 800);
        Color begin = Color.rgb(10,10,10);
        Color end = Color.rgb(20,20,20);
        Stop[] stops = new Stop[] { new Stop(0, begin), new Stop(1, end)};
        LinearGradient lg1 = new LinearGradient(0, 1, 0, 0, true, CycleMethod.REFLECT, stops);
        loginRoot.setBackground(new Background(new BackgroundFill(lg1, CornerRadii.EMPTY, Insets.EMPTY)));


        Scene scene = new Scene(loginRoot); 
        this.secondStage.setScene(scene); 
        this.secondStage.initStyle(StageStyle.UNDECORATED);
        this.secondStage.show();
    }

    public VBox createUserVBox(User user, String path){
        VBox vbox = new VBox();
        Image img = new Image(this.getClass().getClassLoader().getResourceAsStream(path));
        ImageView icon = new ImageView(img);
        icon.setFitWidth(135);
        icon.setFitHeight(135);
        icon.addEventHandler(MouseEvent.MOUSE_MOVED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                vbox.setBorder(new Border(new BorderStroke(Color.valueOf("#9E9E9E"),
                BorderStrokeStyle.SOLID,
                CornerRadii.EMPTY,
                BorderWidths.DEFAULT)));
                event.consume();
            }
        });

        icon.addEventHandler(MouseEvent.MOUSE_EXITED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                vbox.setBorder(new Border(new BorderStroke(Color.valueOf("#9E9E9E"),
                BorderStrokeStyle.SOLID,
                CornerRadii.EMPTY,
                BorderWidths.EMPTY)));
                event.consume();
            }
        });

        icon.setOnMouseClicked(e -> {
            this.items.getChildren().clear();
            vbox.setBorder(new Border(new BorderStroke(Color.valueOf("#9E9E9E"),
            BorderStrokeStyle.SOLID,
            CornerRadii.EMPTY,
            BorderWidths.EMPTY)));
            this.start.setOnAction(e1 -> {
                GameWindow game = new GameWindow(user.getUserId(), user.getUsername(), true);
                this.loginClose();
            });
            this.load.setOnAction(e2 -> {
                GameWindow game = new GameWindow(user.getUserId(), user.getUsername(), false);
                this.loginClose();
            });
            this.items.getChildren().addAll(this.start, this.load);
            this.items.setVisible(true);
        });
        icon.setOpacity(0.75);
        Label label = new Label(user.getUsername());
        label.setStyle("-fx-text-fill: #808080; -fx-font-size: 16px;");
        vbox.getChildren().addAll(icon, label);
        return vbox;
    }

    public void loginClose(){
        secondStage.close();
    }

    public void makeFadeIn(HBox hb){
        FadeTransition fd = new FadeTransition();
        fd.setDuration(Duration.seconds(7));
        fd.setNode(hb);
        fd.setFromValue(0);
        fd.setToValue(1);
        fd.play();
    }
    
    public User getUserById(int id){
        switch(id){
            case 0:
                return userT;
            case 1:
                return userA;
            case 2:
                return userG;
            default:
                return userT;
        }
    }

    private Button generateMenuButtons(String label){
        Button b = new Button(label);
        b.setTextFill(Color.WHITE);
        b.setStyle("-fx-border-color: #fff;-fx-border-width: 2;-fx-background-color: transparent;-fx-font-size: 1.5em;");
        b.setPrefWidth(200);
        b.setPrefHeight(50);
        b.addEventHandler(MouseEvent.MOUSE_ENTERED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent e) {
                b.setStyle("-fx-border-color: #808080;-fx-border-width: 2;-fx-background-color: transparent;-fx-font-size: 1.5em;");
            }
        });
        b.addEventHandler(MouseEvent.MOUSE_EXITED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent e) {
                b.setStyle("-fx-border-color: #fff;-fx-border-width: 2;-fx-background-color: transparent;-fx-font-size: 1.5em;");
          }
        });
        return b;
    }
}