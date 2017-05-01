#! /usr/bin/env python3

from PIL import Image
import os

import interface

rootdir ='tests/cut'

for subdir, dirs, files in os.walk(rootdir):
    for file in files:
        print(file)
