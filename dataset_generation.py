#! /usr/bin/env python3

from PIL import Image
import os

import interface

rootdir ='tests/cut'
rootdirf ='tests/false'

out = open('dataset.csv', 'w')

for subdir, dirs, files in os.walk(rootdir):
    for file in files:
        out.write(file)
        vect = interface.get_features(rootdir + '/' + file)
        for e in vect:
            out.write(";" + str(e).replace("[", "").replace("]", "").replace(", ", ";"))
        out.write(";1\n")

for subdir, dirs, files in os.walk(rootdirf):
    for file in files:
        out.write(file)
        vect = interface.get_features(rootdirf + '/' + file)
        for e in vect:
            out.write(";" + str(e).replace("[", "").replace("]", "").replace(", ", ";"))
        out.write(";0\n")

