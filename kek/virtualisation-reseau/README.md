# virtualisation-reseau


## le cours
 - `https://hepia.infolibre.ch/Virtualisation-Reseaux/`

## le tp1
 - `https://docs.openvswitch.org/en/latest/tutorials/faucet/`

## les tp2 et tp3
 - `https://hepia.infolibre.ch/Virtualisation-Reseaux/Ansible-Hands-on-Introduction.pdf`

ssh-copy-id -i ~/.ssh/id_rsa.pub iti@gns3.hepiapp.ch -p 15002
Dans le fichier /etc/ansible/hosts
h1 ansible_host=gns3.hepiapp.ch ansible_port=15002 ansible_user=iti
Executer la commande :
ansible h1 -m ping 
