#!/bin/bash
rm rapport.*
docker run --rm -it -v $(pwd):/build --user $(id -u):$(id -g) chillias/md-template-pandoc make
make clean