# OVS Faucet lab

comprend pas j'ai meme pas les meme sortis, avec des untagged port et ils sont down donc wtf

https://docs.openvswitch.org/en/latest/tutorials/faucet/

> telnet gns3.hepiapp.ch 15001
> ssh -p 15002 iti@gns3.hepiapp.ch


## Performance

2 types of paths :
- slow path
- fast path
Some factors can force a flow or a packet to take the slow path, any flow that modifies ARP fields is processed in the slow path.

The megaflow cache is the key cache to consider for performance tuning.



br0 fait le lien avec le plan de controle, c'est pourquoi on creer un canal entre le switch openflow et le controller

dps = datapaths

configuration purement au niveau du plan de control, pour informer faucet. pas du tout dans le plan de donnée

log du switch dans le ficheir sandbox/ovs-vswitchd.log :
partie négociation entre le switch et le controller, état des ports du switch etc ...

le controller initialise ensuite le plan de donnée, en ajoutant des tables de flux dans le switch, et remet tout à zéro (le switch ne connait aucun src ni dst, les tables sont vides, donc lors du premier packet le switch va faire un copie et lenvoyer au controller pour mettre a jour sa/ses table de flux)


## Openflow Layer

8 tables dans Faucet

traitement des vlans dans les premiers tables (couche 2)

couches 3 -> table 4 et 5 et 6


openFlow à quoi sert le cookie ? -> une fois qu'on a le cookie (id unique du flux), quand on contacte le controller on lui passe le cookie et comme ça le controller sait directement de quoi on parle (va plus rapide)

Table 0 -> lie les paquets vers le vlan sinon drop
plus priority haute plus va se faire en first
0x8100 précise le vlan 100, le 0x8 devant un pour le protocole

Table 1 -> pour apprendre les MAC, et éviter de flooder
On va apprendre la MAC src des paquets traversant le switch, cette table est inclut par le controller (c'est pas hardcoder dans le switch)

drop broadcast et multicast, si vlan 100 ou 200 on va passer


Table 2 fait rien, juste redirige dans table 3


Table 3 drop paquet STP (pour eviter des boucles), si on a du broadcast on enleve le tag et on forward sur le bon port suivant le vlan, si pas dst broadcast on dé-tag et on forward


## Tracing

envoi un trame sur le port p1 du switch br0
> ovs-appctl ofproto/trace br0 in_port=p1
permet de debbuger, pour savoir quel entrée des tables sont matcher suivant notre paquet


## Triggering MAC Learning

ajout d'entrée de la table de flux n°1, car mtn il connait l'adresse MAC, si le paquet est taggé en table 1 par vlan 1 il est directe forwarder en table 2



## Openflow layer with router


## Tracing with router

ARP est super galère à sécurisé, car utilise du broadcast


## ACLs
ACLs est un firewall, il est en couche 2 et 3




