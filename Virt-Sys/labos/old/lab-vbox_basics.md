# Réponse TP1:
## ex1
- Lors de la création d'un disque de stockage virtuel, quelle est la différence entre un disque alloué dynamiquement et un disque de taille fixe ? Lequel devrait offrir les meilleures performances et pourquoi ?

Prenons exemple d'une espace de 50Gb qu'on veut alloué, un disque de taille fixe va alloué 50Gb dans la mémoire même si il y a peut-être en réalité 10 GB utilisée. Tant dis qu'un disque alloué dynamiquement va augmenté l'espace alloué au fur à mesure que le nombre de Byte utilisée. Donc si nous avons une espace de 50Gb et nous utilisons 10Gb, il y a que 10Gb qui va être utilisée, toutfois, l'espace déjà alloué ne peut pas rétrécir. 

- Quelles différences remarquez-vous entre le matériel (hardware) de la VM et celui de la machine hôte (host) ?

le nombre de processeur utilisés, le nombre de thread par coeur, le nombre de coeur par socket, le type de virtualisation, le nombre de coeur numa, le nombre de périphérique utilisées -> le type de périphérique change de peu aussi.

- Que réalise chaque commande système qui vous a été indiquée ci-dessus (lscpu, free, lspci, lsblk, df) ?

"lscpu" indique les informations sur l'architecture du processeur.
"free" indique le nombre de mémoire Ram libre disponible.
"lspci" est un utilité pour afficher les informations concernant les PCI bus dans le système et les devices connectés aux PCI bus.
"lsblk" affiche des renseignements sur tout ou partie des périphériques bloc disponibles.
"df" est utilisé pour afficher la valeur d'espace disque dispo des systèmes de fichier dont l'utilisateur possède l'accès en lecture.

- Où se trouvent les fichiers liés à votre VM ? Enumérez chaque fichier et décrivez précisément son rôle.

les fichiers liés à notre vm sont dans le dossier: "VirtualBoxVms/FirstVM":
    FirstVM.vbox -> indique les paramètres de la vm telsque la VM name, type OS, mémoire système, sont utilisés pour lancer les machines virtuelle. -> présente sous format xml
    FirstVM.vbox-prev -> pareil
    FirstVM.vdi -> l'image du disk que la vm (.vbox) référence

## ex2
link réponse: https://docs.oracle.com/en/virtualization/virtualbox/6.0/user/clone.html

- Quelle est la différence entre Full Clone et Linked Clone ?
Full-clone: A full clone is an independent copy of a virtual machine that shares nothing with the parent virtual machine after the cloning operation. Ongoing operation of a full clone is entirely separate from the parent virtual machine
Linked-clone: A linked clone is a copy of a virtual machine that shares virtual disks with the parent virtual machine in an ongoing manner. This conserves disk space, and allows multiple virtual machines to use the same software installation

- quelle est la différence entre Current machine state et Everything ?
Everything: Clones the current machine state and all its snapshots.
Current Machine State and All Children: Clones a VM snapshot and all its child snapshots. 

- Quelle est la différence entre un répertoire partagé de type Transient et de type Machine ?

Transient shared : that are added at runtime and disappear when the VM is powered off. These can be created using a check box in the VirtualBox Manager, or by using the --transient option of the VBoxManage sharedfolder add command. 

- Trouvez-vous des modules liés à Virtualbox ? Si oui, le ou lesquels ?
vboxsf

- Trouvez-vous un ou plusieurs nouveaux modules liés à Virtualbox ? Si oui, le ou lesquels ?
vboxsf

- Un nouveau module nommé vboxsf devrait être chargé dans votre noyau. Quel est le rôle de ce module à votre avis ?
D'après la commande modinfo: "follow symlinks:Let host resolve symlinks rather than showing them (int)"

- Quelle ligne avez-vous ajoutée dans /etc/fstab ?
sharedfolder2SecondVM /home/firstVM vboxsf defaults 0 0

## ex3
link réponse: https://blog.scottlowe.org/2016/11/10/intro-to-vbox-cli/

- listez les VMs installées sur votre host: "vboxmanage list vms"
- allumer et éteindre les 2 vms: 
vboxmanage startvm nom_vm
vboxmanage controlvm nom_vm poweroff
- changez la quantité de RAM:
vboxmanage modifyvm nom_vm --memory ram_in_MB
- changez la quantité de CPUs:
vboxmanage modifyvm nom_vm --cpus n_cpu
- Les modifications sont-elles visible dans l'interface de VirtualBox ?
oui
- Est-ce que vboxmanage permet de réaliser plus, moins ou exactement les mêmes opérations que l'interface graphique ?
oui 

## ex4

- Démarrez maintenant ThirdVM et pendant qu'elle s'exécute, démarrez FourthVM. Que remarquez vous ?
avec vboxmanage, nous obtenons ces logs:

Waiting for VM "ThirdVM" to power on...
VM "ThirdVM" has been successfully started.
Waiting for VM "FourthVM" to power on...
VBoxManage: error: Locking of attached media failed. A possible reason is that one of the media is attached to a running VM
VBoxManage: error: Details: code VBOX_E_INVALID_OBJECT_STATE (0x80bb0007), component SessionMachine, interface IMachine

Visuellement parlant, le 4ème VM crash, le 3ème vm a marché

- Dans ThirdVM, ajoutez le fichier $HOME/tagada puis éteigner la VM.Démarrez ensuite FourthVM. Est-ce que le fichier tagada existe dans celle-ci ? Pourquoi ?

Le fichier existe car la 3ème VM et la 4ème VM partagent la même disque, donc si il y a modification dans une VM, l'autre VM va aussi percevoir les modifications

- Trouvez alors un moyen pour augmenter l’espace disque de FourthVM d’au moins 20GB. Décrivez
précisément les différentes étapes réalisées pour obtenir cet espace supplémentaire dans votre VM

vboxmanage modifymedium nom_vm --resize <megabytes>