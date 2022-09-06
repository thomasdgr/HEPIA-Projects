- 1a: 
environ 10min
- 1b: 
environ 47s
l'exécution est plus rapide qu'au point précédent car on utilise la virtualisation de type 2

ainsi "avec -enable-kvm" type de technique de virtualisation 2:
on utilise l'host OS contenant le VMM module pour démarrer notre vm
"sans -enable-kvm" type de technique de virtualisation 1:
la vmm utilise directement les ressources du hardware et supporte tous les exécutions des VMs.

- 1c:
non

- 1d:
l'image qcow2 est alloué dynamiquement, alors que l'espace alloué par raw est fixe
qcow2 alloue 200kb au moment de la création, et raw alloue 500Mb
le disk2.raw est vide

- 1e:
Quel est la différence entre les arguments -hdx (où x représente le numéro de disque a,b,etc.) et -drive ?

On peut spécifier plus d'options, notamment, spécifier le format du disk utilisé pour raw : "qemu-system-x86_64 -drive file=file,index=0,media=disk,format=raw"

Comment peut-on écrire exactement l'équivalent de -hdb avec la syntaxe -drive ?

"Instead of -hda, -hdb, -hdc, -hdd, you can use:
qemu-system-x86_64 -drive file=file,index=0,media=disk
qemu-system-x86_64 -drive file=file,index=1,media=disk
qemu-system-x86_64 -drive file=file,index=2,media=disk
qemu-system-x86_64 -drive file=file,index=3,media=disk"

Sur l'hyperviseur (hôte), comparez les types des disques disk1 et disk2 (fichiers) utilisés dans l'OS guest? (commande file)

résultat du commande file:
disk1.qcow: QEMU QCOW2 Image (v3), 42949672960 bytes
disk2.raw:  DOS/MBR boot sector

Voyez-vous une interface réseau ? A votre avis, de quel type d'interface s'agit-t-il : emulée ou paravirtualisée ?
Oui, il y a une interface émulé réseau 

Finalement, parvenez vous à réaliser un copier/coller de texte entre la VM et votre machine hôte ?
non

commands:
time qemu-system-x86_64 -cdrom xubuntu-20.04.3-desktop-amd64.iso -m 4096 -smp cpus=1 -enable-kvm -drive file=disk1.qcow2,index=0,media=disk -drive file=disk2.raw,index=1,media=disk,format=raw

# ex3
- 3a: on ne peut pas exéctuer directement hepiadoom avec QEMU.
- 3b: qemu-img convert hepiadoom.ova output.qcow2 -O qcow2 -o cluster_size=2M
- 3c: 1m30s
le périphérique contenant le sys de fichiers monté à la racine du sys:
/dev/sda1 
- 3d: time qemu-system-x86_64 -m 4096 -smp cpus=2 -enable-kvm -drive file=hepiadoom.qcow2,index=0,media=disk,if=virtio 

le temps pris est 1m20s

le périphérique s'agit de /dev/vda1

le mot clé virtio donne:
virtio_blk virtio0 : [vda] 1048670000 512-byte logical blocks (537 Gb/ 500Gb)

Que voyez-vous également comme contrôleur de stockage si vous listez les périphériques PCI avec la commande lspci ?
SCSI Storage controller: Red Hat, Inc. Virtio block device

Que remarquez-vous si vous cherchez le mot-clé virtio ?
il n'y a pas
Aussi, que remarquez-vous si vous listez les périphériques PCI avec la commande lspci ?
il n'y a pas le SCSI Storage controller: Red Hat, Inc Virtio block device

# ex4

- 4a:
Quelle est le nom de la carte graphique installée ? Pensez-vous qu’il s’agit d’une carte graphique émulée ou paravirtualisée ?
Le nom de la carte graphique installé est "VGA compatible controller: Device 1234:1111", je pense qu'il s'agit une carte graphique paravirtualisée

- 4b:
le nom de la carte graphique est "VGA compatible controller : Red Hat, inc. virtio GPU"
je pense qu'il s'agit une carte graphique émulée

oui, il s'agit du module virtio_gpu, ce module est utilsée par les modules:
- ttm
- drm_kms_helper
- drm

