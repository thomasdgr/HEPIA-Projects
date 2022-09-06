# Labo 2
## Description
Créer un playbook pour mettre en place un serveur nginx et une page web avec un template jinja

Permet de tester la connexion vers nos hosts
> ansible -m ping -i hosts all

Deploiement du playbook
> ansible-playbook ansible.yml -i hosts

Sur la machine debian, ressors la page web
> curl 127.0.0.1
