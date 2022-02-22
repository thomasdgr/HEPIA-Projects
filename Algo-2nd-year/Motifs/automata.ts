import { table } from "node:console";

export class automata{

    public static state(msg: string, q: number, tmp: string){
        while (tmp.length > 0) {
            for (let i = q; i > 0; i--) {
                if (msg.slice(0, i) == tmp) {
                    return i;
                }
            }
            tmp = tmp.slice(1, tmp.length);
        }
        return 0;
    }

    public static createGrammar(msg: string){
        let gram: string = "";
        for (let i = 0; i < msg.length; i++) {
            if (!gram.includes(msg[i])) {
                gram += msg[i];
            }
        }
        return gram.split("").sort().join("");
    }

    public createArrayAndGrammar(msg: string){
        let gram: string = automata.createGrammar(msg);
        let array: Array<Array<number>> = [];
        for(let i: number = 0; i < msg.length + 1; i++){
            array[i] = new Array(gram.length);
            array[i].fill(0);
        }
        for (let i: number = 1; i <= msg.length; i++) {
            let q1: number = gram.indexOf(msg[i - 1]);
            let q2: number = array[i - 1][q1];
            array[i - 1][q1] = i;
            for (let j: number = 0; j < gram.length; j++) {
                array[i][j] = array[q2][j];
            }
        }
        return [gram, array];
    }
    
    public automata(T: string, M: string, tab: [string, Array<Array<number>>]){
        let positions: Array<number> = [];
        let gram: string = tab[0];
        let array: Array<Array<number>> = tab[1];
        let q: number = 0;
        for(let i = 0; i < T.length; i++){
            if(gram.indexOf(T[i]) != -1){
                q = array[q][gram.indexOf(T[i])];
                if(q == M.length){
                    positions.push(i - M.length + 2);
                }
            } else{
                q = 0;
            }
        }
        return positions;
    }
}