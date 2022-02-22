import java.util.Map;
import java.util.LinkedHashMap;

public class City {

    private String name;
    private int latitude;
    private int longitude;
    private Map<String, Integer> neighbours = new LinkedHashMap<>();


    public City(String name,int latitude,int longitude){
        this.name = name;
        this.latitude = latitude;
        this.longitude = longitude;
    }

    public City(String name,int latitude,int longitude, Map<String, Integer> neighbours){
        this.name = name;
        this.latitude = latitude;
        this.longitude = longitude;
        this.neighbours = neighbours;
    }

    public String getName(){
        return this.name;
    }

    public Integer getLatitude(){
        return this.latitude;
    }

    public Integer getLongitude(){
        return this.longitude;
    }

    public Map<String, Integer> getNeighbours(){
        return this.neighbours;
    }

    public void addNeighbours(String name, int time){
        if(!this.neighbours.containsKey(name)){
            this.neighbours.put(name,time);
        }
    }

    public void removeNeighbours(String name){
        if(this.neighbours.containsKey(name)){
            this.neighbours.remove(name);
        }
    }

    public boolean isNeighbours(City c){
        return this.neighbours.containsKey(c.getName());
    }

    @Override
    public String toString(){
        String res = "City :\n\tnom : " + this.name + "\n\tlongitude : " + this.longitude + "\n\tlatitude : " + this.latitude + "\n\tvoisins:";
        for(String s : this.neighbours.keySet()){
            res += ("\n\t\t" + s + ": " + this.neighbours.get(s).toString());
        }
        return res;
    }
}
