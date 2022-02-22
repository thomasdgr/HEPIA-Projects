package ch.hepia.covid_manager;

import javafx.geometry.Bounds;
import javafx.geometry.Point2D;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Node;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.VBox;
import javafx.geometry.BoundingBox;
import javafx.scene.input.ScrollEvent;

import java.lang.Math;

public class ZoomableScrollPane extends ScrollPane {
    private double scaleValue = 0.3865453013812797;
    private double zoomIntensity = 0.02;
    private Node target;
    public Node zoomNode; 
    private double width;
    private double height;

    public ZoomableScrollPane(Node target, double width, double height) {
        super();
        this.target = target;
        this.zoomNode = new Group(target);
        this.width = width;
        this.height = height;
        setContent(outerNode(zoomNode));
        setPannable(true);
        setHbarPolicy(ScrollPane.ScrollBarPolicy.NEVER); 
        setVbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
        setFitToHeight(true);
        setFitToWidth(true);
        updateScale();
    }

    private Node outerNode(Node node) {
        Node outerNode = centeredNode(node);
        outerNode.addEventFilter(ScrollEvent.ANY, e-> {
        });
        return outerNode;
    }

    private Node centeredNode(Node node) {
        VBox vBox = new VBox(node);
        vBox.setAlignment(Pos.CENTER);
        return vBox;
    }

    private void updateScale() {
        target.setScaleX(scaleValue);
        target.setScaleY(scaleValue);
    }

    public double getZoomWidth(){
        return zoomNode.getLayoutBounds().getWidth();
    }

    public void onScroll(double wheelDelta, Point2D mousePoint) {
        Bounds innerBounds = zoomNode.getLayoutBounds();
        Bounds viewportBounds = getViewportBounds();
        double valX = this.getHvalue() * (innerBounds.getWidth() - viewportBounds.getWidth());
        double valY = this.getVvalue() * (innerBounds.getHeight() - viewportBounds.getHeight());
        double zoomFactor =  Math.exp(wheelDelta * zoomIntensity);    
        if( ((innerBounds.getHeight() >= height*3.7) && zoomFactor > 1) || 
            ((innerBounds.getWidth() < 1800) && zoomFactor < 1)){
                zoomFactor = 1;
        }
        scaleValue = scaleValue * zoomFactor;
        updateScale();
        this.layout();
        // convert target coordinates to zoomTarget coordinates
        Point2D posInZoomTarget = target.parentToLocal(zoomNode.parentToLocal(mousePoint));
        // calculate adjustment of scroll position (pixels)
        Point2D adjustment = target.getLocalToParentTransform().deltaTransform(posInZoomTarget.multiply(zoomFactor - 1));
        Bounds updatedInnerBounds = zoomNode.getBoundsInLocal();
        this.setHvalue((valX + adjustment.getX()) /(updatedInnerBounds.getWidth() - viewportBounds.getWidth()));
        this.setVvalue((valY + adjustment.getY()) / (updatedInnerBounds.getHeight() - viewportBounds.getHeight()));
    }
}