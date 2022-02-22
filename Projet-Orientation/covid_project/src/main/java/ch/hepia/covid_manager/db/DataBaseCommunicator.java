package ch.hepia.covid_manager;

import java.sql.Connection;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;

import ch.hepia.covid_manager.Cure;
import ch.hepia.covid_manager.Virus;

public class DataBaseCommunicator {

  private String dbDriver;
  private String url;
  private String user;
  private String pass;
  private Connection co;

  public DataBaseCommunicator(
    String driver,
    String url,
    String user,
    String pass
  )
    throws SQLException, ClassNotFoundException {
    this.dbDriver = driver;
    this.url = url;
    this.user = user;
    this.pass = pass;
    this.co = DriverManager.getConnection(this.url, this.user, this.pass);
  }

  public ResultSet executeQuery(String query)
    throws SQLException, ClassNotFoundException {
    Class.forName(this.dbDriver);
    PreparedStatement pSt = this.co.prepareStatement(query);
    ResultSet rs = pSt.executeQuery();
    return rs;
  }

  public int executeUpdate(String query)
    throws SQLException, ClassNotFoundException {
    Class.forName(this.dbDriver);
    PreparedStatement pSt = this.co.prepareStatement(query);
    int rs = pSt.executeUpdate();
    return rs;
  }

  public void closeConnection() throws SQLException, ClassNotFoundException {
    this.co.close();
  }

  public CompletableFuture<Countries> loadCountries(User u, boolean newGame) {
    return CompletableFuture.supplyAsync(
      () -> {
        Countries countries = new Countries();
        try {
          this.executeQuery("USE covid");
          // faire une transaction si on veut insert
          ResultSet rs = this.executeQuery("SELECT * FROM Country;");
          while (rs.next()) {
            int totalPop = rs.getInt(6);
            int totalCases = rs.getInt(7);
            int totalActive = rs.getInt(8);
            int totalDeaths = rs.getInt(9);
            int totalRecovered = totalCases - totalActive - totalDeaths;
            int size = rs.getInt(3);
            int lat = rs.getInt(4);
            int longi = rs.getInt(5);
            countries.addCountry(
              new Country(
                rs.getString(2),
                lat,
                longi,
                totalCases,
                0,
                totalDeaths,
                0,
                totalRecovered,
                0,
                size,
                totalPop,
                rs.getString(1),
                0
              )
            );
          }
          //On va lire les données "personnelles" à l'utilisateur
          rs =
            this.executeQuery(
                "SELECT * FROM State WHERE `game_id` = " + u.getUserId() + ";"
              );
          if (!newGame) {
            while (rs.next()) {
              String slug = rs.getString(2);
              int totalCases = rs.getInt(3);
              int totalActive = rs.getInt(4);
              int totalDeaths = rs.getInt(5);
              int totalCured = rs.getInt(6);
              Country tmp = countries
                .listOfCountries()
                .stream()
                .filter(c -> c.slug().equals(slug))
                .findFirst()
                .get();
              tmp.setTotalCases(totalCases);
              tmp.setTotalActive(totalActive);
              tmp.setTotalDeaths(totalDeaths);
              tmp.setTotalCured(totalCured);
              tmp.setTotalRecovered(totalCases - totalActive - totalDeaths);
            }
          }
        } catch (Exception e) {
          throw new RuntimeException(e);
        }
        return countries;
      }
    );
  }

  public void save(Virus v, Countries c, User user, LocalDate ld) {
    String req =
      "UPDATE `Virus` SET `infectivity`=" +
      v.infectivity() +
      ",`lethality`=" +
      v.lethality() +
      ",`resistance`=" +
      v.resistance() +      
      ",`points`=" +
      v.getPoints() +
      ", `cure_progress`=" +
      Cure.getInstance().progression() +
      ", `cure_impact` = "+
      Cure.getInstance().impact()+
      " WHERE `id`=" +
      user.getUserId();
    try {
      this.executeQuery("USE covid");
      this.executeUpdate(req);
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
    req =
      "UPDATE `Game` SET `current_date`= '" +
      ld.toString() +
      "' WHERE `virus_id`=" +
      user.getUserId();

    try {
      this.executeUpdate(req);
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
    v
      .getUnlockedPerks()
      .forEach(
        (Perk p) -> {
          try {
            this.executeUpdate(
                "INSERT INTO `UnlockedPerk`(`perk_id`, `virus`) VALUES (" +
                p.id() +
                "," +
                user.getUserId() +
                ") ON DUPLICATE KEY UPDATE `perk_id`=`perk_id`"
              );
          } catch (Exception e) {
            throw new RuntimeException(e);
          }
        }
      );

    c
      .listOfCountries()
      .forEach(
        (Country co) -> {
          try {
            this.executeUpdate(
                "INSERT INTO `State`(`game_id`, `slug`, `current_total_cases`, `current_total_active`, `current_total_deaths`, `current_total_cured`) VALUES (" +
                user.getUserId() +
                ",'" +
                co.slug() +
                "'," +
                co.playerTotalCases() +
                "," +
                co.playerTotalActive() +
                ", " +
                co.playerTotalDeaths() +
                "," +
                co.playerTotalCured() +
                ") ON DUPLICATE KEY UPDATE `current_total_cases` = " +
                co.playerTotalCases() +
                ", `current_total_active` = " +
                co.playerTotalActive() +
                ", `current_total_deaths` = " +
                co.playerTotalDeaths() +
                ", `current_total_cured` = " +
                co.playerTotalCured()
              );
          } catch (Exception e) {
            throw new RuntimeException(e);
          }
        }
      );
  }

  public CompletableFuture<Virus> loadVirus(User u, Perks p) {
    return CompletableFuture.supplyAsync(
      () -> {
        try {
          this.executeQuery("USE covid");
          String req =
            "SELECT * FROM UnlockedPerk WHERE `virus` = " + u.getUserId();
          ResultSet rs = this.executeQuery(req);
          while (rs.next()) {
            if (p.getPerkById(rs.getInt(1)).isPresent()) {
              Virus
                .getInstance()
                .freeUpgrade(p.getPerkById(rs.getInt(1)).get());
            }
          }
          rs = this.executeQuery("SELECT * FROM Virus WHERE `id` = " + u.getUserId());
          if(rs.next()){
            Virus.getInstance().addPoints(rs.getInt(6));
            Cure.getInstance().setProgress(rs.getFloat(7));
            Cure.getInstance().setImpact(rs.getFloat(8));
          }
        } catch (Exception e) {
          throw new RuntimeException(e);
        }
        return Virus.getInstance();
      }
    );
  }

  public CompletableFuture<LocalDate> loadDate(LocalDate ld, User u) {
    return CompletableFuture.supplyAsync(
      () -> {
        try {
          this.executeQuery("USE covid");
          String req = "SELECT * FROM Game WHERE `virus_id` = " + u.getUserId();
          ResultSet rs = this.executeQuery(req);
          if (rs.next()) {
            return LocalDate.parse(rs.getString(3));
          }
        } catch (Exception e) {
          throw new RuntimeException(e);
        }
        return ld;
      }
    );
  }
}
