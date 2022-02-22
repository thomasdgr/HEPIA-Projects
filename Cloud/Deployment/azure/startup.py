# Import the needed credential and management objects from the libraries.
from azure.identity import AzureCliCredential
from azure.mgmt.resource import ResourceManagementClient
from azure.mgmt.network import NetworkManagementClient
from azure.mgmt.compute import ComputeManagementClient

import os
import base64

print(f"Provisioning database... some operations might take a minute or two.")

# Acquire a credential object using CLI-based authentication.
credential = AzureCliCredential()

# Retrieve subscription ID from environment variable.
subscription_id = 'f0514094-5bb5-4925-9323-de8fc229bb63'

# dans le terminal : export AZURE_SUBSCRIPTION_ID=f0514094-5bb5-4925-9323-de8fc229bb63


# Step 1: Provision a resource group

# Obtain the management object for resources, using the credentials from the CLI login.
resource_client = ResourceManagementClient(credential, subscription_id)

# Constants we need in multiple places: the resource group name and the region
# in which we provision resources. You can change these values however you want.
RESOURCE_GROUP_NAME = "database_group_10101537"
LOCATION = "switzerlandnorth"

# Provision the resource group.
rg_result = resource_client.resource_groups.create_or_update(RESOURCE_GROUP_NAME,
    {
        "location": LOCATION
    }
)

# For details on the previous code, see Example: Provision a resource group
# at https://docs.microsoft.com/azure/developer/python/azure-sdk-example-resource-group


# Step 2: provision a virtual network

# A virtual machine requires a network interface client (NIC). A NIC requires
# a virtual network and subnet along with an IP address. Therefore we must provision
# these downstream components first, then provision the NIC, after which we
# can provision the VM.

# Network and IP address names
VNET_NAME = "DB-vnet"
SUBNET_NAME = "DB-subnet"
IP_NAME = "DB-ip"
IP_CONFIG_NAME = "DB-ip-config"
NIC_NAME = "DB-nic"

# Obtain the management object for networks
network_client = NetworkManagementClient(credential, subscription_id)

# Provision the virtual network and wait for completion
poller = network_client.virtual_networks.begin_create_or_update(RESOURCE_GROUP_NAME,
    VNET_NAME,
    {
        "location": LOCATION,
        "address_space": {
            "address_prefixes": ["10.0.0.0/16"]
        }
    }
)

vnet_result = poller.result()

# Step 3: Provision the subnet and wait for completion
poller = network_client.subnets.begin_create_or_update(RESOURCE_GROUP_NAME, 
    VNET_NAME, SUBNET_NAME,
    { "address_prefix": "10.0.0.0/24" }
)
subnet_result = poller.result()

# Step 4: Provision an IP address and wait for completion
poller = network_client.public_ip_addresses.begin_create_or_update(RESOURCE_GROUP_NAME,
    IP_NAME,
    {
        "location": LOCATION,
        "sku": { "name": "Standard" },
        "public_ip_allocation_method": "Static",
        "public_ip_address_version" : "IPV4"
    }
)

database_address = poller.result()

print(f"Provisioned public IP address {database_address.name} with address {database_address.ip_address}")

# Step 5: Provision the network interface client
poller = network_client.network_interfaces.begin_create_or_update(RESOURCE_GROUP_NAME,
    NIC_NAME, 
    {
        "location": LOCATION,
        "ip_configurations": [ {
            "name": IP_CONFIG_NAME,
            "subnet": { "id": subnet_result.id },
            "public_ip_address": {"id": database_address.id }
        }],
        "networkSecurityGroup": {
            "id": "/subscriptions/f0514094-5bb5-4925-9323-de8fc229bb63/resourceGroups/database_group_10101537/providers/Microsoft.Network/networkSecurityGroups/database-nsg"
        }
    }
)

nic_result = poller.result()

# Step 6: Provision the virtual machine

# Obtain the management object for virtual machines
compute_client = ComputeManagementClient(credential, subscription_id)

VM_NAME = "database"
USERNAME = "thomas"
PASSWORD = "MySuperPassword1234"

# Provision the VM specifying only minimal arguments, which defaults to an Ubuntu 18.04 VM
# on a Standard DS1 v2 plan with a public IP address and a default virtual network/subnet.

poller = compute_client.virtual_machines.begin_create_or_update(RESOURCE_GROUP_NAME, VM_NAME,
    {
        "location": LOCATION,
        "properties": {
            "hardwareProfile": {
                "vmSize": "Standard_D1_v2"
            },
            "storageProfile": {
                "imageReference": {
                    "id": "/subscriptions/f0514094-5bb5-4925-9323-de8fc229bb63/resourceGroups/database_group_10101537/providers/Microsoft.Compute/galleries/database_gallery/images/database_image"
                },                           
                "osDisk": {
                    "caching": "ReadWrite",
                    "managedDisk": {
                        "storageAccountType": "Standard_LRS"
                    },
                    "name": "DB-disk",
                    "createOption": "FromImage"
                }
            },
            "osProfile": {
                "computer_name": VM_NAME,
                "admin_username": USERNAME,
                "admin_password": PASSWORD
            },
            "networkProfile": {
                "networkInterfaces": [
                {
                    "id": nic_result.id,
                    "properties": {
                        "primary": True
                    }
                }]
            },
            "userData": "I2Nsb3VkLWNvbmZpZwpydW5jbWQ6CiAgLSBjZCAvaG9tZS90aG9tYXMvZGIvIAogIC0gbm9kZSBzZXJ2ZXIuanMK"
        }
    }
)

vm_result = poller.result()

print(f"Provisioned virtual machine {vm_result.name}")

print(f"\nProvisioning backend... some operations might take a minute or two.")

# Acquire a credential object using CLI-based authentication.
credential = AzureCliCredential()

# Retrieve subscription ID from environment variable.
subscription_id = 'f0514094-5bb5-4925-9323-de8fc229bb63'

# dans le terminal : export AZURE_SUBSCRIPTION_ID=f0514094-5bb5-4925-9323-de8fc229bb63


# Step 1: Provision a resource group

# Obtain the management object for resources, using the credentials from the CLI login.
resource_client = ResourceManagementClient(credential, subscription_id)

# Constants we need in multiple places: the resource group name and the region
# in which we provision resources. You can change these values however you want.
RESOURCE_GROUP_NAME = "backend_group_10101532"
LOCATION = "switzerlandnorth"

# Provision the resource group.
rg_result = resource_client.resource_groups.create_or_update(RESOURCE_GROUP_NAME,
    {
        "location": LOCATION
    }
)


# For details on the previous code, see Example: Provision a resource group
# at https://docs.microsoft.com/azure/developer/python/azure-sdk-example-resource-group


# Step 2: provision a virtual network

# A virtual machine requires a network interface client (NIC). A NIC requires
# a virtual network and subnet along with an IP address. Therefore we must provision
# these downstream components first, then provision the NIC, after which we
# can provision the VM.

# Network and IP address names
VNET_NAME = "BACK-vnet"
SUBNET_NAME = "BACK-subnet"
IP_NAME = "BACK-ip"
IP_CONFIG_NAME = "BACK-ip-config"
NIC_NAME = "BACK-nic"

# Obtain the management object for networks
network_client = NetworkManagementClient(credential, subscription_id)

# Provision the virtual network and wait for completion
poller = network_client.virtual_networks.begin_create_or_update(RESOURCE_GROUP_NAME,
    VNET_NAME,
    {
        "location": LOCATION,
        "address_space": {
            "address_prefixes": ["10.0.0.0/16"]
        }
    }
)

vnet_result = poller.result()

# Step 3: Provision the subnet and wait for completion
poller = network_client.subnets.begin_create_or_update(RESOURCE_GROUP_NAME, 
    VNET_NAME, SUBNET_NAME,
    { "address_prefix": "10.0.0.0/24" }
)
subnet_result = poller.result()

# Step 4: Provision an IP address and wait for completion
poller = network_client.public_ip_addresses.begin_create_or_update(RESOURCE_GROUP_NAME,
    IP_NAME,
    {
        "location": LOCATION,
        "sku": { "name": "Standard" },
        "public_ip_allocation_method": "Static",
        "public_ip_address_version" : "IPV4"
    }
)

backend_address = poller.result()

print(f"Provisioned public IP address {backend_address.name} with address {backend_address.ip_address}")

# Step 5: Provision the network interface client
poller = network_client.network_interfaces.begin_create_or_update(RESOURCE_GROUP_NAME,
    NIC_NAME, 
    {
        "location": LOCATION,
        "ip_configurations": [ {
            "name": IP_CONFIG_NAME,
            "subnet": { "id": subnet_result.id },
            "public_ip_address": {"id": backend_address.id }
        }],
        "networkSecurityGroup": {
            "id": "/subscriptions/f0514094-5bb5-4925-9323-de8fc229bb63/resourceGroups/backend_group_10101532/providers/Microsoft.Network/networkSecurityGroups/backend-nsg"
        }
    }
)

nic_result = poller.result()

# Step 6: Provision the virtual machine

# Obtain the management object for virtual machines
compute_client = ComputeManagementClient(credential, subscription_id)

VM_NAME = "backend"
USERNAME = "thomas"
PASSWORD = "MySuperPassword1234"

# Provision the VM specifying only minimal arguments, which defaults to an Ubuntu 18.04 VM
# on a Standard DS1 v2 plan with a public IP address and a default virtual network/subnet.

poller = compute_client.virtual_machines.begin_create_or_update(RESOURCE_GROUP_NAME, VM_NAME,
    {
        "location": LOCATION,
        "properties": {
            "hardwareProfile": {
                "vmSize": "Standard_D1_v2"
            },
            "storageProfile": {
                "imageReference": {
                    "id": "/subscriptions/f0514094-5bb5-4925-9323-de8fc229bb63/resourceGroups/backend_group_10101532/providers/Microsoft.Compute/galleries/backend_gallery/images/backend_image"
                },                           
                "osDisk": {
                    "caching": "ReadWrite",
                    "managedDisk": {
                        "storageAccountType": "Standard_LRS"
                    },
                    "name": "BACK-disk",
                    "createOption": "FromImage"
                }
            },
            "osProfile": {
                "computer_name": VM_NAME,
                "admin_username": USERNAME,
                "admin_password": PASSWORD
            },
            "networkProfile": {
                "networkInterfaces": [
                {
                    "id": nic_result.id,
                    "properties": {
                        "primary": True
                    }
                }]
            },
            "userData": str(base64.b64encode(bytes('#cloud-config\nruncmd:\n - cd /home/thomas/backend/\n - sed -i \'25s/.*/var dbLink = \"http:\/\/'+ str(database_address.ip_address) +':8081\";/\' server.js\n - node server.js', 'utf-8')))[2:-1]
        }                                                                      
    }
)

vm_result = poller.result()

print(f"Provisioned virtual machine {vm_result.name}")

print(f"\nProvisioning frontend... some operations might take a minute or two.")

# Acquire a credential object using CLI-based authentication.
credential = AzureCliCredential()

# Retrieve subscription ID from environment variable.
subscription_id = 'f0514094-5bb5-4925-9323-de8fc229bb63'

# Step 1: Provision a resource group

# Obtain the management object for resources, using the credentials from the CLI login.
resource_client = ResourceManagementClient(credential, subscription_id)

# Constants we need in multiple places: the resource group name and the region
# in which we provision resources. You can change these values however you want.
RESOURCE_GROUP_NAME = "frontend_group_10101527"
LOCATION = "switzerlandnorth"

# Provision the resource group.
rg_result = resource_client.resource_groups.create_or_update(RESOURCE_GROUP_NAME,
    {
        "location": LOCATION
    }
)

# For details on the previous code, see Example: Provision a resource group
# at https://docs.microsoft.com/azure/developer/python/azure-sdk-example-resource-group


# Step 2: provision a virtual network

# A virtual machine requires a network interface client (NIC). A NIC requires
# a virtual network and subnet along with an IP address. Therefore we must provision
# these downstream components first, then provision the NIC, after which we
# can provision the VM.

# Network and IP address names
VNET_NAME = "FRONT-vnet"
SUBNET_NAME = "FRONT-subnet"
IP_NAME = "FRONT-ip"
IP_CONFIG_NAME = "FRONT-ip-config"
NIC_NAME = "FRONT-nic"

# Obtain the management object for networks
network_client = NetworkManagementClient(credential, subscription_id)

# Provision the virtual network and wait for completion
poller = network_client.virtual_networks.begin_create_or_update(RESOURCE_GROUP_NAME,
    VNET_NAME,
    {
        "location": LOCATION,
        "address_space": {
            "address_prefixes": ["10.0.0.0/16"]
        }
    }
)

vnet_result = poller.result()

# Step 3: Provision the subnet and wait for completion
poller = network_client.subnets.begin_create_or_update(RESOURCE_GROUP_NAME, 
    VNET_NAME, SUBNET_NAME,
    { "address_prefix": "10.0.0.0/24" }
)
subnet_result = poller.result()

# Step 4: Provision an IP address and wait for completion
poller = network_client.public_ip_addresses.begin_create_or_update(RESOURCE_GROUP_NAME,
    IP_NAME,
    {
        "location": LOCATION,
        "sku": { "name": "Standard" },
        "public_ip_allocation_method": "Static",
        "public_ip_address_version" : "IPV4"
    }
)

frontend_address = poller.result()

print(f"Provisioned public IP address {frontend_address.name} with address {frontend_address.ip_address}")

# Step 5: Provision the network interface client
poller = network_client.network_interfaces.begin_create_or_update(RESOURCE_GROUP_NAME,
    NIC_NAME, 
    {
        "location": LOCATION,
        "ip_configurations": [ {
            "name": IP_CONFIG_NAME,
            "subnet": { "id": subnet_result.id },
            "public_ip_address": {"id": frontend_address.id }
        }],
        "networkSecurityGroup": {
            "id": "/subscriptions/f0514094-5bb5-4925-9323-de8fc229bb63/resourceGroups/frontend_group_10101527/providers/Microsoft.Network/networkSecurityGroups/frontend-nsg"
        }
    }
)

nic_result = poller.result()

# Step 6: Provision the virtual machine

# Obtain the management object for virtual machines
compute_client = ComputeManagementClient(credential, subscription_id)

VM_NAME = "frontend"
USERNAME = "thomas"
PASSWORD = "MySuperPassword1234"

# Provision the VM specifying only minimal arguments, which defaults to an Ubuntu 18.04 VM
# on a Standard DS1 v2 plan with a public IP address and a default virtual network/subnet.

poller = compute_client.virtual_machines.begin_create_or_update(RESOURCE_GROUP_NAME, VM_NAME,
    {
        "location": LOCATION,
        "properties": {
            "hardwareProfile": {
                "vmSize": "Standard_D1_v2"
            },
            "storageProfile": {
                "imageReference": {
                    "id": "/subscriptions/f0514094-5bb5-4925-9323-de8fc229bb63/resourceGroups/frontend_group_10101527/providers/Microsoft.Compute/galleries/frontend_gallery/images/frontend_image"
                },                           
                "osDisk": {
                    "caching": "ReadWrite",
                    "managedDisk": {
                        "storageAccountType": "Standard_LRS"
                    },
                    "name": "FRONT-db",
                    "createOption": "FromImage"
                }
            },
            "osProfile": {
                "computer_name": VM_NAME,
                "admin_username": USERNAME,
                "admin_password": PASSWORD
            },
            "networkProfile": {
                "networkInterfaces": [
                {
                    "id": nic_result.id,
                    "properties": {
                        "primary": True
                    }
                }]
            },
            "userData": str(base64.b64encode(bytes('#cloud-config\nruncmd:\n - cd /home/thomas/frontend/\n - sed -i \'2s/.*/let address = \"' + str(backend_address.ip_address) + '\";/\'  classements/classements.js\n - python3 -m http.server', 'utf-8')))[2:-1]
        }
    }
)

vm_result = poller.result()

print(f"Provisioned virtual machine {vm_result.name}")