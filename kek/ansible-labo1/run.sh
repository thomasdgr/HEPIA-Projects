#!/bin/bash

sudo apt install sshpass -y
ansible-galaxy collection install ansible.posix

sed -i "s/ip1/$1/g" config/r1.config
sed -i "s/ip2/$2/g" config/h1.config
sed -i "s/ip3/$3/g" config/h2.config

ANSIBLE_HOST_KEY_CHECKING=False ansible-playbook -i config/r1.config r1.yml
ANSIBLE_HOST_KEY_CHECKING=False ansible-playbook -i config/h1.config h1.yml
ANSIBLE_HOST_KEY_CHECKING=False ansible-playbook -i config/h2.config h2.yml