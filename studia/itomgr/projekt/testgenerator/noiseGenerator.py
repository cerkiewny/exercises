import os
import glob 
from PIL import Image
import numpy
import scipy
import scipy.misc
import scipy.ndimage

class noiseGen():
    def __init__(self, filename):
        self.filename = filename
        imag = Image.open(filename)
        width, height = imag.size
        imagea = Image.new("CMYK", (width + 40, height + 40), "WHITE")
        imagea.paste(imag, (20,20,20 + width, 20 + height))
        scipy.misc.imsave(filename, imagea)

    def genNoise(self):
        imagea = (scipy.misc.imread(self.filename)).astype(float)
        blurredImage = scipy.ndimage.gaussian_filter(imagea, sigma=2)
        poissonNoise = numpy.random.poisson(700,imagea.shape).astype(float)
        noisyImage = blurredImage + poissonNoise
        newfilename = self.filename.replace("bare_","noised_")
        scipy.misc.imsave(newfilename, noisyImage)

path = '../SAMPLE_IMAGES'

for filename in os.listdir(path):
    if "bare_" in filename:
        print(filename)
        ng = noiseGen(os.path.join(path ,filename))
        ng.genNoise()
    
