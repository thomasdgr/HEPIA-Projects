"""
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
"""

import os
import yaml
import boto3
import os

def create_instance(node_nb):
    return ec2.create_instances(
            ImageId="ami-02e136e904f3da870",
            MinCount=1,
            MaxCount=1,
            InstanceType="t2.micro",
            SecurityGroupIds=['sg-04751f7ce57d306f5',],
            KeyName='quentin_lenovo',
            UserData="""
            #cloud-config

            runcmd:
                - yum update -y
                - sudo yum -y install golang
            """
        )

def read_yaml(node_number):
    with open("../server_infos/neighbour-" + str(node_number) + ".yaml", "r") as yaml_stream:
        try:
            return yaml.safe_load(yaml_stream)
        except:
            print("Failed to load YAML file")

try:

    ec2 = boto3.resource('ec2')

    ips = []
    yamls = []

    for i in range(0,6):
        # Création de l'instance de base de donnée
        instances = create_instance(i)
        # récupération de l'identifiant de l'instance de database
        instance_id = instances[0].id

        inst = ec2.Instance(id=instance_id)
        inst.wait_until_running()
        ip_address = ""
        # en fonction de l'id de l'instance récupérer
        # on récupère l'ip correspondante
        instances = ec2.instances.filter(
            Filters=[{'Name': 'instance-state-name', 'Values': ['running']}])
        for instance in instances:
            if( instance_id == instance.id):
                print("Server " + str(i + 1) + ": " + instance.public_ip_address)
                ip_address = instance.public_ip_address

        ips.append(ip_address)
        yamls.append(read_yaml(i + 1))

    new_yamls = []

    for i in yamls:
        i['address'] =  str(ips[i['id'] - 1 ])
        new_neighbours = []
        for tmp in i['neighbours']:
            tmp['address'] =  str(ips[tmp['id'] - 1 ])
            new_neighbours.append(tmp)
        i['neighbours'] = new_neighbours
        new_yamls.append(i)

    for i in range(1,7):
        with open("../server_infos/neighbour-" + str(i) + ".yaml", "w") as fp:
            try:
                yaml.dump(new_yamls[i-1], fp)
            except:
                print("Failed to write YAML file")

    for ip in ips:
       os.system( "scp -o StrictHostKeyChecking=no -i ~/.ssh/quentin_lenovo.pem -r ../server_infos/ ../../golang/ ec2-user@" + ip + ":/home/ec2-user")

except Exception as e:
    print(e)
