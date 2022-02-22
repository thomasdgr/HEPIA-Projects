#!/bin/bash
cd /home/kekusmax/frontend/frontend/classements
sed -i '2s/.*/let address = "130.211.201.255";/' classements.js
cd ..
python3 -m http.server