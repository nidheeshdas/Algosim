#!/bin/bash

if [ ! -d $HOME/Algosim ]; then
	mkdir $HOME/Algosim
	cp -R /usr/share/algosim/algos/ $HOME/Algosim
fi
