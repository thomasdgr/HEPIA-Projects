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
        SecurityGroupIds=['sg-0720a6e4bb5211030',],
        KeyName='trung',
        UserData="""
        #cloud-config

        runcmd:
            - pip3 install pyyaml
            - pip3 install numpy
        """
    )   


def read_yaml(node_number):
    with open("./shortest_path_sysdistr/ressources/server"+ str(node_number) +"/neighbour-" + str(node_number) + ".yaml", "r") as yaml_stream:
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
                print("Node nb" + str(i + 1) + ": " + instance.id, instance.public_ip_address)
                ip_address = instance.public_ip_address

        ips.append(ip_address)
        yamls.append(read_yaml(i + 1))

    new_yamls = []

    for i in yamls:
        i['address'] =  ips[i['id'] - 1 ]
        new_neighbours = []
        for tmp in i['neighbours']:
            tmp['address'] =  ips[tmp['id'] - 1 ]
            new_neighbours.append(tmp)
        i['neighbours'] = new_neighbours
        new_yamls.append(i)

    print(new_yamls)
    
    for i in range(1,7):
        with open("./shortest_path_sysdistr/ressources/server"+ str(i) +"/neighbour-" + str(i) + ".yaml", "w") as fp:
            try:
                yaml.dump(new_yamls[i-1], fp)
            except:
                print("Failed to write YAML file")

    count = 1
    for ip in ips:
       os.system( "scp -o StrictHostKeyChecking=no -i ~/.ssh/trung.pem -r ./shortest_path_sysdistr/src/ ./shortest_path_sysdistr/ressources/server"+ str(count)+ " ec2-user@" + ip + ":")
       count+=1
    
    for ip in ips:
        print("ssh -o StrictHostKeyChecking=no -i ~/.ssh/trung.pem ec2-user@" + ip)


except Exception as e:
    print(e)
