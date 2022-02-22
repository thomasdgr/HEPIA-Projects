import { table } from "node:console";

export class kpm{
    
    arrayKPM(msg: string){
        let pi_array: Array<number> = [0];
        let q1: number = 0;
        let q2: number = 1;
        while (q2 < msg.length){
            if (msg[q1] === msg[q2]){
                pi_array[q2] = q1 + 1;
                q2++;
                q1++;
            } else if (q1 === 0){
                pi_array[q2] = 0;
                q2++;
            } else {
                q1 = pi_array[q1 - 1];
            }
        }
        return pi_array;
    }

    knuttMorrisPratt(T: string, M: string, pi_array: Array<number>){
        let positions: Array<number> = [];
        let q1: number = 0;
        let q2: number = 0;
        while(q1 < T.length){
            if(T[q1] === M[q2]){
                if (q2 === M.length - 1){
                    positions.push((q1 - M.length) + 2);
                }
                q2++;
                q1++;
            } else if(q2 > 0){
                q2 = pi_array[q2 - 1];
            } else{
                q2 = 0;
                q1++;
            }
        }
        return positions;
    }
}