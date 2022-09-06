# Rapport HEPIA - HES-SO

[le rapport de Théo](https://sitehepia.hesge.ch/diplome/ITI/2020/documents/Pirkl-532)

[le git de Théo](https://gitedu.hesge.ch/theo.pirkl/bachelor-scrapper-058/-/tree/master/rapport)

[le cours de Perrot](https://cyberlearn.hes-so.ch/course/view.php?id=11170)

[le template de base](https://gitlab.com/hepia-magelfik/rapport-iti-hepia)

## Structure de dossiers et fichiers

- `figs` : l'endroits où stocker les images
- `templates` : La partie LaTeX du rapport.
- `text` : le rapport en markdown
- `config.yaml` : config du rapport
- `my.bib` : la bibliographie zotero ->  [@un_nom_dans_my_bib]
- `text/ZZ-glossaire.md`: le glossaire (voir le lien dans le fichier pour la doc)

## Compilation de votre rapport

`./run.sh`

## Indications d'usage

- les tableaux: `Table: <la légende de votre tableau>`
- les notes de bas de page: `word[^0]` et en bas du fichier: `[^0]: yes \url{https://github.com/thomasdgr}` 
- les liens: `[word](matching link)`
- les images:
```latex
% Insère une image (et l'ajoute dans la table des figures) :
\cimg{figs/malas_et_thomas.png}{scale=0.5}{yeeeees}{Source : tiré de \url{myurl.ch}, ref. URL01}
```
- la bibliographie: `word [@ref_in_my.bib]`
- mettre du code:
  ```c
  int main(){
      return 0;
  }
  ```
- citer une figure: `![This is the caption\label{mylabel}](/url/of/image.png) See figure \ref{mylabel}`.
- pour tout le reste: [la documentation Pandoc](https://pandoc.org/MANUAL.html)
