public class FloydWarshall {
    
    private Matrix weight;
    private Matrix next;
    private Cities cities;


    public FloydWarshall(Cities cities){
        this.cities = cities;
        this.next = new Matrix(cities.size(), cities.size());
        this.weight = new Matrix(cities.size(), cities.size());
        this.weight.fill(cities);
        createMatWeightAndNext();
    }
    
    public void createMatWeightAndNext(){
        int num = this.cities.size();
        for(int i = 0; i < num; i++){
            for(int j = 0; j < num; j++){
                this.next.getData()[i*num + j] = Integer.MIN_VALUE;
            }
        }
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                if(this.weight.getData()[(i * num ) + j] != Integer.MAX_VALUE){
                    this.next.getData()[(i * num ) + j] = j;
                }
                if (i == j) {
                    this.next.getData()[(i * num ) + j] = -1;
                    this.weight.getData()[(i * num ) + j] = 0;
                }
            }
        }

        for (int k = 0; k < num; k++) {
            for (int i = 0; i < num; i++) {
                for (int j = 0; j < num; j++) {
                    if(this.weight.getData()[ (i * num ) + j ] > (this.weight.getData()[(i * num ) + k] + this.weight.getData()[(k * num ) + j]) ){
                        if(this.weight.getData()[(i * num) + k] != Integer.MAX_VALUE && weight.getData()[(k * num ) + j] != Integer.MAX_VALUE){
                           this.weight.getData()[(i * num) + j] = this.weight.getData()[(i * num ) + k] + this.weight.getData()[(k * num ) + j];
                           this.next.getData()[(i * num) + j] = this.next.getData()[(i * num ) + k];
                        } 
                    }                       
                }
            }
        }
        this.next = this.next.reverse();
    }

    public Matrix getMatWeight(){
        return this.weight;
    }

    public Matrix getMatNext(){
        return this.next;
    }

    public int getWeightFromNames(String src, String dst){
        int i = this.cities.getIndexInCities(src);
        int j = this.cities.getIndexInCities(dst);
        return this.weight.getData()[i * this.cities.size() + j];
    }

    public void printPathFromNames(String src, String dst){
        int i = this.cities.getIndexInCities(src);
        int j = this.cities.getIndexInCities(dst);

        City s = this.cities.getCityFromName(src);
        City d = this.cities.getCityFromName(dst);

        if(this.weight.getData()[i * this.cities.size() + j] == Integer.MAX_VALUE){
            return;
        }
        String output = dst + "]";
        while(i != j){
            j = this.next.getData()[i * this.cities.size() + j];
            d = this.cities.getCityFromIndex(j);
            output = (d.getName() + ":") + output;
        }
        System.out.println("[" + output);
    }

    public boolean checkConectivity(){
        for(int i = 0; i < this.weight.getCol() * this.weight.getRow(); i++){
            if(this.weight.getData()[i] == Integer.MAX_VALUE){
                return false;
            }
        }
        return true;
    }
}