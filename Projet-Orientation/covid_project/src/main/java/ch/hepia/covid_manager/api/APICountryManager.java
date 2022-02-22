package ch.hepia.covid_manager;

import java.net.URL;
import java.net.URLConnection;
import java.net.HttpURLConnection;
import java.util.Scanner;
import java.util.concurrent.CompletableFuture;
import java.util.Map;
import java.util.HashMap;

import javax.management.RuntimeErrorException;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.net.ProtocolException;
import java.net.MalformedURLException;
import java.text.ParseException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import java.time.LocalDate;


/* Class used to get data from the covid19api
 * we use them to compare the actual situation from the game
 * with the real data at the same time (if we are not in the future)
 *
 * we used this class too previsously to get the data at the beggining of
 * the api (01.22.2020) that are now stored in the data base
 */
public class APICountryManager {

    private String apiLink; //https://api.covid19api.com

    public APICountryManager(String apiLink) {
        if (apiLink.charAt(apiLink.length() - 1) == '/') {
            apiLink = apiLink.substring(0, apiLink.length() - 1);
        }
        this.apiLink = apiLink;
    }

    // async function to get the data from a specific country from the beggining of the api to the
    // real day we are playing the game (not the one displayed in the game)
    public CompletableFuture<Map<LocalDate, Integer[]>> getCountryHistory(Country c) {
        return CompletableFuture.supplyAsync(()->{
            Map < LocalDate, Integer[] > map = new HashMap <> ();
            try {
                URL url = new URL(this.apiLink + "/total/country/" + c.slug());
                HttpURLConnection connexion = (HttpURLConnection) url.openConnection();
                connexion.setRequestMethod("GET");
                int response = connexion.getResponseCode();
                if (response != 200) {
                    System.out.println("HTTP Request failed with response code: " + response + "\n Data will be taken form contrycords.txt");
                }
                String content = "";
                Scanner sc = new Scanner(url.openStream());
                while (sc.hasNext()) {
                    content += sc.nextLine();
                }
                sc.close();
                JSONParser parser = new JSONParser();
                JSONArray data_obj = (JSONArray) parser.parse(content);
                for (Object i: data_obj) {
                    JSONObject a = (JSONObject) i;
                    String dateString = a.get("Date").toString();
                    Integer[] data = {
                        Integer.parseInt(a.get("Confirmed").toString()),
                        Integer.parseInt(a.get("Deaths").toString()),
                        Integer.parseInt(a.get("Recovered").toString()),
                        Integer.parseInt(a.get("Active").toString()),
                        0
                        };
                        map.put(LocalDate.parse(dateString.substring(0, 10)), data);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
                return map;
        });
        
    }
}