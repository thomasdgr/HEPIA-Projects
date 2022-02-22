import java.util.Map;

import java.util.List;
import java.util.ArrayList;

public class Matrix {
    private int col;
    private int row;
    private int data[];

    public Matrix(int col, int row){
        this.col = col;
        this.row = row;
        this.data = new int[col*row];
    }

    public void fill(Cities cities){
        int i = 0;
        for(City src : cities.getCities()){
            Map<String,Integer> neighbours = src.getNeighbours();
            for (City dst : cities.getCities()){
                if(src.isNeighbours(dst)){
                    this.data[i++] = neighbours.get(dst.getName());
                } else if(src.getName().equals(dst.getName())){
                    this.data[i++] = 0;
                } else { 
                    this.data[i++] = Integer.MAX_VALUE;
                }
            }
        }
    }

    public int[] getData(){
        return this.data;
    }

    public void print(){
        String res = "";
        for(int i = 0; i < this.col * this.row; i++){
            if(i % this.col == 0){
                System.out.println(res.trim());
                res = "";
            }
            if(data[i] == Integer.MAX_VALUE){
                res += "inf ";
            } else {
                res += (data[i] + " ");
            }
        }
        System.out.println(res.trim());
    }

    public int getCol(){
        return this.col;
    }
    
    public int getRow(){
        return this.row;
    }

    public Matrix reverse(){
        Matrix mat = new Matrix(this.getCol(), this.getRow());

        for (int i = 0; i < mat.getCol(); i++) {
            for (int j = 0; j < mat.getCol(); j++) {
                mat.getData()[i * mat.getCol() + j] = this.getData()[j * mat.getCol() + i];
            }
        }
        return mat;
    }
}
