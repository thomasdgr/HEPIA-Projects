import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Cities {
    private List<City> cities = new ArrayList<>();

    public Cities() {}

    public Cities(List<City> cities){
        this.cities = cities;
    }

    public void print(){
        int i = 0;
        String res = "";
        for (City c : this.getCities()){
            res += ("[" + i + ":" + c.getName() + "] ");
            i += 1;
        }
        System.out.println(res.trim());
    }

    public List<City> getCities(){
        return this.cities;
    }

    public City getCityFromName(String name){
        if(exist(name)){
            for(City c : this.getCities()){
                if(c.getName().equals(name)){
                    return c;
                }
            }
        }
        // ne peut pas être atteint
        return new City("", -1, -1);
    }


    public int getIndexInCities(String name){
        if(exist(name)){
            int i = 0;
            for(City c : this.getCities()){
                if(c.getName().equals(name)){
                    return i;
                }
                i++;
            }
        }
        // ne peut pas être atteint
        return -1;
    }

    public City getCityFromIndex(int index){
        if(index >= 0 && index <= this.cities.size()){
            int i = 0;
            for(City c : this.getCities()){
                if(i == index){
                    return c;
                }
                i++;
            }
        }
        // ne peut pas être atteint
        return new City("", -1, -1);
    }

    public int size(){
        return this.getCities().size();
    }

    public void printWeight(){
        for (City c : this.getCities()) {
            String res = "";
            Map<String, Integer> neighbours = c.getNeighbours();
            for (String s : neighbours.keySet()) {
                res += "[" + s + ":" + neighbours.get(s) + "] ";
            }
            System.out.println(c.getName() + " " + res.trim());
        }
    }

    public void add(City c){
        this.cities.add(c);
    }

    public void addNeighbours(String src, String dst, int time){
        if(exist(src) && exist(dst)){
            for(City c : this.getCities()){
                if(c.getName().equals(src)){
                    c.addNeighbours(dst, time);
                } else if(c.getName().equals(dst)){
                    c.addNeighbours(src, time);
                }
            }
        }
    }

    public void removeByName(String name){
        if(exist(name)){
            for(City c1 : this.getCities()){
                if(c1.getName().equals(name)){
                    for(City c2 : this.getCities()){
                        if(c2.isNeighbours(c1)){
                            c2.removeNeighbours(c1.getName());
                        }
                    }
                    this.cities.remove(c1);
                    break;
                }
            }
        }
    }

    public void removeNeighboursByName(String src, String dst){
        if(exist(src) && exist(dst)){
            for(City c : this.getCities()){
                if(c.getName().equals(src)){
                    c.removeNeighbours(dst);
                } else if(c.getName().equals(dst)){
                    c.removeNeighbours(src);
                }
            }
        }
    }

    public boolean exist(String name){
        for(City c : this.getCities()){
            if(c.getName().equals(name)){
                return true;
            }
        }
        throw new RuntimeException("city: " + name + " doesn't exist");
    }

    @Override
    public String toString(){
        String res = "";
        for (City city : this.getCities()) {
            res += city.toString();
        }
        return res;
    }
}