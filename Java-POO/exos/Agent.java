import java.util.*;

/* ************************************************************************
 * Ex 2 - (10 pts)
 * Nous souhaitons réaliser un jeu où différent types de personnage 
 * (appelé Agent) coopèrent pour réaliser des tâches.
 * Deux interfaces sont à compléter. Nous souhaitons réduire la duplication
 * du code en réalisant les méthodes par défaut.
 * Ne complétez donc que celles-ci !
 * ************************************************************************/

interface Agent {

    boolean isWorking();

    // un agent dort lorsqu'il ne travaille pas
    default boolean isSleeping() {
        return !this.isWorking();
    }

    /* réveil un agent. 
     * Retourne une exception si l'agent est déjà en train de travailler ! */
    void wakeUp();

    // retourne le nombre de tâches que l'agent doit encore réaliser
    default int nbTasksToComplete() {
        return this.currentTasksToComplete().size();
    }

    // retourne la liste des tâches que l'agent doit encore réaliser
    List<Task> currentTasksToComplete();
}
interface AgentManager {

    // retourne tous les agents
    List<Agent> allAgents();

    // réveil tous les agents qui dorment et qui ont trois tâches ou plus à compléter
    default void wakeUpOnlySleepingAndBusyAgents() {
        List<Agent> res = this.allAgents();
        for(Agent crtAgent : res){
            if(crtAgent.nbTasksToComplete() >= 3 || crtAgent.isSleeping()){
                crtAgent.wakeUp();
            }
        }
    }
}