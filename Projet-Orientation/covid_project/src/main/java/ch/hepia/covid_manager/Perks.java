package ch.hepia.covid_manager;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import javafx.scene.paint.Color;

import java.lang.Math;
import java.sql.ResultSet;

import javafx.scene.control.*;
import java.util.Optional;

import java.util.concurrent.CompletableFuture;

public class Perks{

    private List < Perk > perks = new ArrayList < > ();

    public Perks() {}

    public Perks(List < Perk > listOfPerks) {
        this.perks = listOfPerks;
    }

    public void addPerk(Perk p) {
        this.perks.add(p);
    }

    public Optional<Perk> getPerkById(int id) {
        for (Perk p: this.perks) {
            if (p.id() == id) {
                return Optional.of(p);
            }
        }
        return Optional.empty();
    }

    public List<Perk> listOfPerks() {
        return this.perks;
    }

    // return a liste of buttons assigned to each perks from the db
    // used in the right side bar bar menu to unlock perks
    public LinkedHashMap < Button, Perk > buttonsPerksMap() {
        LinkedHashMap< Button, Perk> perksMap = new LinkedHashMap<>();
        for(Perk p: this.perks){
            Button b = new Button(p.name());
            b.setPrefWidth(120);
            b.setPrefHeight(60);
            perksMap.put(b, p);
        }
        return perksMap;
    }

    // init perks from the database
    public void init(){
        try{
            this.perks = this.getPerksFromDb().get();
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }

    //Reads the perks from the database asynchronously
    public static CompletableFuture<List<Perk>> getPerksFromDb(){
        return CompletableFuture.supplyAsync( () ->{
            List<Perk> res = new ArrayList<>();

            String driver = "com.mysql.cj.jdbc.Driver";
            String url = "jdbc:mysql://localhost";
            String req = "SELECT * FROM Perk";

            try{
                DataBaseCommunicator dbc = new DataBaseCommunicator(driver, url, "root", "root");
                dbc.executeQuery("USE covid");
                ResultSet rs = dbc.executeQuery(req);
                while (rs.next()){
                    res.add(Perk.perkFactory(rs.getInt(1), rs.getString(2), rs.getString(3), rs.getInt(4), (double)rs.getFloat(5), rs.getString(6)));
                }
                dbc.closeConnection();
            }catch(Exception e){
                throw new RuntimeException(e);
            }
            return res;
        });
    }
}