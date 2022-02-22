#!/bin/bash
cd /home/kekusmax/home
sed -i '25s/.*/var dbLink = "http:\/\/34.70.59.67:8081";/' server.js
node server.js