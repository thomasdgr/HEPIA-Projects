#!/usr/bin/env bash
# To use an OpenStack cloud you need to authenticate against the Identity
# service named keystone, which returns a **Token** and **Service Catalog**.
# The catalog contains the endpoints for all services the user/tenant has
# access to - such as Compute, Image Service, Identity, Object Storage, Block
# Storage, and Networking (code-named nova, glance, keystone, swift,
# cinder, and neutron).
#
# *NOTE*: Using the 3 *Identity API* does not necessarily mean any other
# OpenStack API is version 3. For example, your cloud provider may implement
# Image API v1.1, Block Storage API v2, and Compute API v2.0. OS_AUTH_URL is
# only for the Identity API served through keystone.
export OS_AUTH_URL=https://keystone.cloud.switch.ch:5000/v3
export OS_IDENTITY_API_VERSION=3
# With the addition of Keystone we have standardized on the term **project**
# as the entity that owns the resources.
#export OS_PROJECT_ID=a17ee8a4dc45498789462463a0e73a07
export OS_PROJECT_NAME="groupe_a"
export OS_USER_DOMAIN_NAME="Default"
if [ -z "$OS_USER_DOMAIN_NAME" ]; then unset OS_USER_DOMAIN_NAME; fi
export OS_PROJECT_DOMAIN_ID="default"
if [ -z "$OS_PROJECT_DOMAIN_ID" ]; then unset OS_PROJECT_DOMAIN_ID; fi
# unset v2.0 items in case set
unset OS_TENANT_ID
unset OS_TENANT_NAME
# In addition to the owning entity (tenant), OpenStack stores the entity
# performing the action as the **user**.
export OS_USERNAME="gustavo.pertuzati@etu.hesge.ch"
#
# SWITCHengines API Credentials:
# https://help.switch.ch/engines/faq/how-to-create-api-credentials/
#
echo "Enter your SWITCHengines API credentials for project $OS_PROJECT_NAME as user $OS_USERNAME: "
read -sr API_KEY_INPUT
export OS_PASSWORD="a3c39d5b872141ec3ea5331782ec460e"
# If your configuration has multiple regions, we set that information here.
export OS_REGION_NAME="ZH"
# Don't leave a blank variable, unset it if it was empty
if [ -z "$OS_REGION_NAME" ]; then unset OS_REGION_NAME; fi
