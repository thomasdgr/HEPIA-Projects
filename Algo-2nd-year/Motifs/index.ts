import { rk } from "./rk";
import { automata } from "./automata";
import { kpm } from "./kpm";
import { bm } from "./bm";

import * as process from 'process';
import * as fs from 'fs';

class Main {

    public static main(args: string[]){
        let fileName: string = null;
        let motif: string = null;
        let algo: number = 0;
        let content: string = "";
        let res, tab, current_algo;
        switch((args.length)){
            case 3:
                try{
                    fileName = args[2];
                    content = fs.readFileSync(fileName, 'utf-8');
                } catch(e){
                    content = "";
                }
            case 2:
                algo = parseInt(args[1]);
                motif = args[0];
                break;
            default:
                console.error("usage: npx ts-node <motif> <algo> (<fichier_texte>)");
                process.exit(1);
        }        
        switch(algo){
            case 1:
                console.info("Algorithme de Rabin-Karp:");
                current_algo = new rk();
                res = current_algo.rabinKarp(content, motif, 10, 1, motif.length);
                if(content.length > 0){
                    Main.display(res);
                } else {
                    console.info("   Le hash du motif: " + res);
                }
                break;
            case 2:
                console.info("Automates finis:");
                current_algo = new automata();
                tab = current_algo.createArrayAndGrammar(motif);
                res = current_algo.automata(content, motif, tab);
                if(content.length > 0){
                    Main.display(res);
                } else {
                    console.info("   L'automate du motif:");
                    console.info(tab[1]);
                }
                break;
            case 3:
                console.info("Algorithme de Knuth-Morris-Pratt:");
                current_algo = new kpm();
                tab = current_algo.arrayKPM(motif);
                res = current_algo.knuttMorrisPratt(content, motif, tab);
                if(content.length > 0){
                    Main.display(res);
                } else {
                    console.info("   Le tableau du motif:");
                    console.info(tab);
                }
                break;
            case 4:
                console.info("Algorithme de Boyer-Moore:");
                current_algo = new bm();
                tab = current_algo.array1BM(motif);
                let tab2 = current_algo.array2BM(motif);

                res = current_algo.boyerMoore(content, motif, tab, tab2);
                if(content.length > 0){
                    Main.display(res);
                } else {
                    console.info("   Le tableau des sauts en cas de mauvais caractères:");
                    console.info(tab);
                    console.info();
                    console.info("   Le tableau des sauts en cas de mauvase correspondance motif-texte:");
                    console.info(tab2);
                }
                break;
            default:
                console.error("Algorithm not implemented");
                process.exit(2);
        }
    }

    public static display(res){
        console.info("   Nombre d'occurences du motif: " + res.length);
        process.stdout.write("   Les positions dans le texte : ");
        for(let i = 0; i < res.length; i++){
            process.stdout.write(res[i].toString() + " ");
        }
        console.info();
    }

}
new Main.main(process.argv.slice(2));

