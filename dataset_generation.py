#! /usr/bin/env python3

from PIL import Image
import os

import interface

rootdir ='tests/cut'

out = open('dataset.csv', 'w')
out.write('name\n')
for subdir, dirs, files in os.walk(rootdir):
    for file in files:
        out.write(file + '\n')
