package ch.hepia.covid_manager;

import javafx.animation.Interpolator;
import javafx.application.Application;
import javafx.scene.Node;
import javafx.scene.Group;
import javafx.scene.control.*;
import javafx.scene.shape.*;
import javafx.animation.Transition.*;
import javafx.animation.TranslateTransition;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.Parent;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.util.Duration;

class RightSideBar extends HBox{
    private double expandedLength;
    private double hiddenLength;
    private TranslateTransition tt = new TranslateTransition(Duration.millis(300), this);
    private boolean isAnimating = false;
    private boolean isShowing = false;

    public RightSideBar(final double expandedLength, final double hiddenLength, Node... nodes){
        this.expandedLength = expandedLength;
        this.hiddenLength = hiddenLength;

        getChildren().addAll(nodes);

        tt.setOnFinished(e -> isAnimating = false);
        tt.setInterpolator(new Interpolator(){
            @Override
            protected double curve(double t){
                return (t == 1.0 ? 1.0 : 1-Math.pow(2.0, -10*t));
            }
        });
    }

    //Animations for opening and closing the sideBar
    public void animate(boolean isOtherVisible, LeftSideBar lsb, DropdownMenu d){
        if(getTranslateX() <= hiddenLength ){
            tt.setToX(getTranslateX() + expandedLength);
            isShowing = false;
        } else {
            if(isOtherVisible){
                lsb.animate(isShowing, this, d);
                d.manageDisplayFirstMenu();

            }
            tt.setToX(getTranslateX() - expandedLength);
            isShowing = true;
        }
        tt.play();
    }

    public boolean isAnimating(){
        return this.isShowing;
    }
}