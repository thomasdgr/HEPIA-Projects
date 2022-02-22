import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Dijkstra {

    private int[] dist;
    private int[] prev;
    private int size;
    
    public Dijkstra(int size){
        this.dist = new int[size];
        this.prev = new int[size];
        this.size = size;
    }

    public void applyDijkstra(City c, Cities cities){
        int i = cities.getIndexInCities(c.getName());
        for(int j = 0; j < this.size; j++){
            if(i == j){
                dist[j] = 0;
                prev[j] = -1;
            }else{
                dist[j] = Integer.MAX_VALUE;
                prev[j] = 0;
            }
        }
        List<Tuple> queue = new ArrayList<>();
        queue.add(new Tuple(i, 0));

        while(!queue.isEmpty()){
            Tuple elem = queue.remove(0);
            int index_src = elem.getX();
            Map<String, Integer> neighbours = cities.getCityFromIndex(index_src).getNeighbours();
            for (String s : neighbours.keySet()){
                int index_dst = cities.getIndexInCities(s);
                int d_new = dist[index_src] + neighbours.get(s);
                if(d_new < dist[cities.getIndexInCities(s)]){
                    dist[index_dst] = d_new;
                    prev[index_dst] = index_src;
                    queue.add(0, new Tuple(index_dst, d_new));
                }
            }
        }
    }

    public void printDist(Cities cities){
        for(City c : cities.getCities()){
            int index = this.dist[cities.getIndexInCities(c.getName())];
            System.out.print("[" + c.getName() + ":" + index + "] ");
        }
        System.out.println();
    }

    public void printDist(Cities cities, String dst){
        for(City c : cities.getCities()){
            int index = this.dist[cities.getIndexInCities(c.getName())];
            if(c.getName().equals(dst)){
                if(index != Integer.MAX_VALUE){
                    System.out.println(index);    
                    return;
                } else {
                    System.out.println(Integer.MAX_VALUE);    
                }
            }
        }
    }

    public void printPrev(Cities cities){
        for(City c : cities.getCities()){
            int index = this.prev[cities.getIndexInCities(c.getName())];
            if(index != -1){
                System.out.print("[" + cities.getCityFromIndex(index).getName() + "<-" + c.getName() + "] ");
            }
        }
        System.out.println();
    }

    public void printPrev(Cities cities, String dst){
        for(City c : cities.getCities()){
            int index = this.dist[cities.getIndexInCities(c.getName())];
            if(c.getName().equals(dst)){
                if(index == Integer.MAX_VALUE){ 
                    return;
                }
            }
        }
        int index_dst = cities.getIndexInCities(dst);
        String output = dst + "]";
        while(index_dst != -1){
            index_dst = this.prev[index_dst];
            output = cities.getCityFromIndex(index_dst).getName() + ":" + output;
        }
        output = "[" + output.substring(1);
        System.out.println(output);
    }
}
