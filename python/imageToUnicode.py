#!/usr/bin/python
# -*- coding: iso-8859-15 -*-

import PIL
from PIL import Image

def isBright(pixel):
    if pixel[0] + pixel[1] + pixel[2] > 384:
	return True
    else:
	return False

def imageToFile(image, fileName):
    file = open(fileName, "w")
    
    for y in xrange(0, image.size[1] - 1, 2):
	for x in xrange(0, image.size[0] - 1):
	    if isBright(image.getpixel((x,y))):
		if isBright(image.getpixel((x,y+1))):
		    file.write("█")
		else:
		    file.write("▀")
	    else:
		if isBright(image.getpixel((x,y+1))):
		    file.write("▄")
		else:
		    file.write(" ")
	file.write("\n")
    
    file.close()

firstOffset = (5, 8)
subsequentOffset = (60, 60)
spriteSize = (50, 40)

numWidth = 4
numHeight = 6

im = Image.open("alphys_by_hebrideanisle.png")
im = im.convert("RGB")

for x in xrange(0, numWidth):
    for y in xrange(0, numHeight):
	left = firstOffset[0] + x * subsequentOffset[0]
	upper = firstOffset[1] + y * subsequentOffset[1]
	right = left + spriteSize[0]
	lower = upper + spriteSize[1]
	box = (left, upper, right, lower) 
	imageToFile(im.crop(box), "alphys_" + str(x) + "_" + str(y))

