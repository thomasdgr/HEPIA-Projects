import boto3

try:
    
    ec2 = boto3.resource('ec2')


    # Création de l'instance de base de donnée
    instances = ec2.create_instances(
        ImageId="ami-02e136e904f3da870",
        MinCount=1,
        MaxCount=1,
        InstanceType="t2.micro",
        SecurityGroupIds=['sg-0182673cab0965df2',],
        KeyName='DorianAwsKey',
        UserData="""
        #cloud-config

        runcmd:
            - yum update -y 
            - curl -sL "https://rpm.nodesource.com/setup_14.x" | sudo bash -
            - sudo yum -y install nodejs 
            - wget https://githepia.hesge.ch/dorian.bernasco/cloud_deployment/-/archive/main/cloud_deployment-main.tar.gz
            - tar -xvzf cloud_deployment-main.tar.gz
            - cd cloud_deployment-main/src/db/
            - npm install
            - node server.js
        """
    )   

    # récupération de l'identifiant de l'instance de database
    instance_id = instances[0].id

    inst = ec2.Instance(id=instance_id)
    inst.wait_until_running()

    db_ip_address = ""

    # en fonction de l'id de l'instance récupérer
    # on récupère l'ip correspondante 
    instances = ec2.instances.filter(
        Filters=[{'Name': 'instance-state-name', 'Values': ['running']}])
    for instance in instances:
        if( instance_id == instance.id):
            print("db :" + instance.id, instance.instance_type,instance.public_ip_address)
            db_ip_address = instance.public_ip_address

    # Création de l'instance de backend
    instanceBackend = ec2.create_instances(
        ImageId="ami-02e136e904f3da870",
        MinCount=1,
        MaxCount=1,
        InstanceType="t2.micro",
        SecurityGroupIds=['sg-086b5f6cc9297689d',],
        KeyName='DorianAwsKey',
        UserData="""
        #cloud-config

        runcmd:
            - yum update -y 
            - curl -sL "https://rpm.nodesource.com/setup_14.x" | sudo bash -
            - sudo yum -y install nodejs 
            - wget https://githepia.hesge.ch/dorian.bernasco/cloud_deployment/-/archive/main/cloud_deployment-main.tar.gz
            - tar -xvzf cloud_deployment-main.tar.gz
            - cd cloud_deployment-main/src/backend/
            - sed -i '25s/.*/var dbLink = \"http:\/\/"""+ db_ip_address +""":8081\";/' server.js
            - npm install
            - node server.js
        """
    )   

    # récupération de l'identifiant de l'instance backend
    backend_id = instanceBackend[0].id

    inst = ec2.Instance(id=backend_id)
    inst.wait_until_running()

    backend_ip_address = ""

    # en fonction de l'id de l'instance récupérer
    # on récupèrel'ip correspondante 
    instances = ec2.instances.filter(
        Filters=[{'Name': 'instance-state-name', 'Values': ['running']}])
    for instance in instances:
        if( backend_id == instance.id):
            print("backend :" + instance.id, instance.instance_type,instance.public_ip_address)
            backend_ip_address = instance.public_ip_address

    instanceFront = ec2.create_instances(
        ImageId="ami-02e136e904f3da870",
        MinCount=1,
        MaxCount=1,
        InstanceType="t2.micro",
        SecurityGroupIds=['sg-06ed95945094ad094',],
        KeyName='DorianAwsKey',
        UserData="""
        #cloud-config

        runcmd:
            - yum update -y 
            - wget https://githepia.hesge.ch/dorian.bernasco/cloud_deployment/-/archive/main/cloud_deployment-main.tar.gz
            - tar -xvzf cloud_deployment-main.tar.gz
            - cd cloud_deployment-main/src/frontend/
            - sed -i '2s/.*/let address = \""""+ backend_ip_address +"""\";/'  classements/classements.js
            - python3 -m http.server
        """
    )
    front_id = instanceFront[0].id
    
    inst = ec2.Instance(id=front_id)
    inst.wait_until_running()

    # en fonction de l'id de l'instance récupérer
    # on récupèrel'ip correspondante 
    instances = ec2.instances.filter(
        Filters=[{'Name': 'instance-state-name', 'Values': ['running']}])
    for instance in instances:
        if( front_id == instance.id):
            print("frontend :" + instance.id, instance.instance_type,instance.public_ip_address)
            backend_ip_address = instance.public_ip_address


except Exception as e:
    print(e)
