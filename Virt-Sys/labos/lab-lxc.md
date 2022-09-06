# lab lxc

## partie 1
	
créer un volume group:			  sudo vgcreate vg /dev/sdb /dev/sdc /dev/sdd
créer un logic group sur le volume:	  sudo lvcreate -n vol -l 100%VG vg
après on doit formater le volume logique: mkfs.ext4 /dev/vg/vol
on doit monter le volume logique:	  mount /dev/vg/vol /mnt/data
et faire un lien symbolique dans lxc:     ln -s /mnt/data/lxc /var/lib/lxc

## partie 2

afficher les templates disponibles:	  ls /usr/lxc/share/templates
créer un container privilègié:		  sudo lxc-create -t /usr/share/lxc/templates/lxc -ubuntu -n privileged-container -- -r impish -a amd64
temps mis pour créer le container: 4'34
créer le même container mais avec download: 
 - on doit exporter la clé:		  export DOWNLOAD_KEYSERVER="http://keyserver.ubuntu.com" (on doit être en sudo -s par contre)
 - (Distribution: "ubuntu")		  sudo lxc-create -n container_ex1 -t download -- --no-validate -r impish -a amd64
 - temps mis pour créer le container: 29s
 - c'est beaucoup plus court car le container est pré-construit et simplement téléchargé depuis le serveur lxc
créer un nouveau container en utilisant la même commande
 - c'est encore plus rapide car l'image que le template utilise est déjà téléchargée sur notre machine
lister les containers avec:		  lxc-ls --fancy
 - tous les containers sont stoppés et son non-privilègiés
pour la dernière question je sais pas comment voir le man de lxc-ls ne dit rien

## partie 3

pour se connecter au container:		   lxc-start container_ex1
					   lxc-attach container_ex1      -> permet de lancer un processus dans le container qui tourne
					OU lxc-console container_ex1     -> permet de lancer une console pour le container qui tourne
pour lancer le vimtutor:		   ./vimtutor (dans /usr/bin)
 - dans le container, le vimtutor appartient à root, son pid est 144
 - sur la machine hote, le vimtutor appartien à root, son pid est 966846

## partie 4

pour créer un container non-privilègié: voir slide 16 du cours sur lxc et faire un lxc-create

## partie 5

il faut éditer le fichier /var/lib/lxc/container_ex1/config pour ne pas limiter les ressources qu'au runtime
au runtime, il suffit d'utiliser la commande lxc-cgroup
