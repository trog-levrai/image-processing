# distutils: language = c++
# distutils: sources = src/haar.cc

from libcpp.string cimport string
from libcpp.vector cimport vector
from cython.operator cimport dereference as deref
from PIL import Image

cdef extern from "src/haar.hh":
    cdef cppclass Haar:
        Haar() except +
        Haar(vector[unsigned char]& img, size_t width, size_t height) except +
        void genIntegral()

def processImage(path):
    cdef Haar haar
    im = Image.open(path)
    data = []
    for i in list(im.getdata()):
        for j in i:
            data.append(j)
    haar = Haar(data, im.width, im.height)
    haar.genIntegral()
    im.show()
