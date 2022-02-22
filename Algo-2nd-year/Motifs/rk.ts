import { table } from "node:console";

export class rk{

    // utiliser le motif 1212 uniquement et sur le fichier rkText.txt de préférence (mais les 2 marchent)

    public static hashRK(msg: string, base: number){
        if (msg.length === 0){
            return 0;
        }
        return parseInt(msg) + base * (rk.hashRK(msg.slice(0, msg.length - 1), base));
    }

    rabinKarp(T: string, M: string, B: number, q: number, length: number){
        let positions: Array<number> = [];
        if(T.length === 0){
            return rk.hashRK(M, B);
        }
        let h: number = rk.hashRK(M, B) % q;
        let t_s: number = +(T.slice(0, M.length));
        for (let s: number = 0; s <= T.length - M.length; s++){
            if (h === (t_s % q)){
                if (M === T.slice(s, s + M.length)){
                    positions.push(s+1);
                }
            }
            if (s + 1 < T.length - M.length){
                t_s = +(B * (t_s - Math.pow(B, M.length - 1) * +(T[s + 1])) + T[s + M.length + 1]);
            }
        }
        return positions;
    }
}