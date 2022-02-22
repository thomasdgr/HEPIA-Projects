À exéctuer dans le répertoire en fonction du langage à déployer:

- deployment.py: Petit script tout simple pour déployer les instances avec aws:

1) pip3 install awscli --upgrade --user
2) aws configure (appuyer sur ENTER pour tous sauf la région: us-east-1)
3) pip install boto3
4) aller sur : https://awsacademy.instructure.com, lancer le Lab et cliquer sur AWS Details, cliquer sur le bouton "show" à coté de AWS CLI, copier et coller dans ~/.aws/credentials
(il faut refaire la manip' 4 à chaque fois )
5) python3 deployment.py
