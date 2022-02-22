- sur le pc:

mpicc ex1.c

mpirun -n X a.out
si X > 6 -> mpirun -n X --oversubscribe a.out



- sur baobab:

scp exo.c baobab:

(le script marche que sur la machine babobab)

pour avoir mpicc : module load foss

mpicc exo.c
sbatch script.sh      # pour lancer un job
squeue -u dagierjo    # pour voir l'état du job
cat xxx.out           # pour voir l'output du programme

si on veut changer le nombre de thread on va directement dans script.sh


passer des arguments au script sbatch -> echo $1

si on veut changer la config, on met en commentaire la ligne et on la passe en paramètre

 ex: sbatch --ntasks=4 kek.sh