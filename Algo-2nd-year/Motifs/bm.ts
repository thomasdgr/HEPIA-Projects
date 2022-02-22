import { table } from "node:console";

export class bm{

    array1BM(msg: string){
        let map = new Map();
        for(let i = 0; i < msg.length; i++){
            map.set(msg[i], msg.length - 1 - i);
        }
        map.set("*", msg.length);
        return map;
    }

    array2BM(msg: string){
        let tab2: Array<number> = [];
        for (let i = msg.length - 1; i >= 0; i--){
            let prev = msg[0];
            if (i > 0){
                prev = msg[i - 1];
            }
            let crt = msg.slice(i, msg.length);
            if (i == 0){
                crt = crt.slice(1, crt.length);
            }
            let pos = msg.lastIndexOf(crt);
            while (pos > 0 && prev == msg[pos - 1]) {
                pos = msg.lastIndexOf(crt, pos - 1);
            }
            let shift = -1;
            if (pos == -1) {
                while (msg.indexOf(crt) != 0) {
                    if (msg.length == crt.length) {
                        shift = msg.length;
                        break;
                    } else {
                        crt = crt.slice(1, crt.length);
                    }
                }
                if (shift == -1) {
                    shift = msg.length - crt.length;
                }
            } else {
                shift = msg.length - crt.length - pos;
            }
            tab2[msg.length - i - 1] = shift;
        }
        return tab2;
    }
    
    boyerMoore(T: string, M: string, tab1, tab2: Array<number>){       
        let positions: Array<number> = [];
        let s: number = M.length;
        while (s <= T.length) {
            let j: number = M.length;
            while (j > 0 && T[s - M.length + j - 1] == M[j - 1]){
                j--;
            }
            if (j == 0) {
                positions.push(s - M.length + 1);
            }
            if (j == M.length) {
                if (tab1.has(T[s - 1])){
                    s += tab1.get(T[s- 1]);
                } else {
                    s += tab1.get("*");
                }
            } else {
                s += tab2[M.length - j - 1];
            }
        }
        return positions
    }
}