#!/usr/bin/python
# -*- coding: iso-8859-15 -*-

import os
import PIL
from PIL import Image

def isBright(pixel):
    if pixel[0] + pixel[1] + pixel[2] > 384:
	return True
    else:
	return False

def imageToFile(image, fileName, folderName):
    #bounding box adjustments
    box = image.getbbox()
    box = (box[0], box[1], box[2], box[3]+1)
    image = image.crop(box)
    
    directory = os.getcwd() + "/" + folderName
    if not os.path.exists(directory):
	os.makedirs(directory)
    
    file = open(directory + "/" + fileName, "w")
    
    for y in xrange(0, image.size[1] - 1, 2):
	for x in xrange(0, image.size[0]):
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
    
# Defines variables that will change between each sprite sheet
class sheetCharacter:
    def __init__(self, path, initialOffset, offset, spriteSize, numWidth, numHeight):
	# String
	# Path to the sprite sheet image
	self.path = path
	# Int 2-tuple
	# Number of pixels before sprites begin (which may or may not be different to the space between them)
	self.initialOffset = initialOffset
	# Int 2-tuple
	# Number of pixels between sprites
	self.offset = offset
	# Int 2-tuple
	# Size of a single sprite
	self.spriteSize = spriteSize
	# Int
	# How many columns of sprites are in the sheet
	self.numWidth = numWidth
	# Int list
	# How many sprites are in each column; this seems to vary in SR sheets, so the list length should be the same as numWidth
	self.numHeight = numHeight
	
#				File name		Initial offset	Offset	Sprite Size	Columns	Column heights
Alphys = sheetCharacter(	"alphys.png", 		(2,2), 		(2,2), 	(56,47), 	13, 	[1, 1, 2, 1, 3, 1, 8, 5, 1, 1, 3, 1, 2])
AlphysSmall = sheetCharacter(	"alphys_small.png", 	(5,248), 	(5,7), 	(40,32), 	18, 	[2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1])
Asgore = sheetCharacter(	"asgore.png", 		(11,11),	(12,14),(48,49), 	8, 	[2, 2, 2, 2, 2, 2, 1, 1])
Asriel = sheetCharacter(	"asriel.png", 		(8,8), 		(3,13),	(26,27), 	10, 	[2, 2, 2, 2, 2, 2, 2, 2, 2, 1])
Papyrus = sheetCharacter(	"papyrus.png", 		(3,19),		(3,18),	(33,50), 	6, 	[4, 4, 3, 3, 3, 2])
Sans = sheetCharacter(		"sans.png", 		(3,3),		(3,3),	(42,44), 	7, 	[1, 1, 1, 1, 1, 1, 1])
Toriel = sheetCharacter(	"toriel.png", 		(0,0),		(0,0),	(36,38), 	16, 	[6, 1, 1, 1, 2, 1, 2, 1, 3, 1, 1, 1, 2, 1, 4, 7])
Undyne = sheetCharacter(	"undyne.png", 		(5,5),		(5,5),	(45,38), 	8, 	[4, 3, 3, 3, 3, 3, 3, 3])

characters = [Alphys, AlphysSmall, Asgore, Asriel, Papyrus, Sans, Toriel, Undyne]

for char in characters:
    im = Image.open(char.path)
    im = im.convert("RGB")
    
    fileName = char.path.split(".")[0]
    iterations = 0
    
    for x in xrange(0, char.numWidth):
	for y in xrange(0, char.numHeight[x]):
	    left = char.initialOffset[0] + x * (char.offset[0] + char.spriteSize[0])
	    upper = char.initialOffset[1] + y * (char.offset[1] + char.spriteSize[1])
	    right = left + char.spriteSize[0]
	    lower = upper + char.spriteSize[1]
	    box = (left, upper, right, lower)
	    imageToFile(im.crop(box), fileName + "." + str(iterations).zfill(3) + ".txt", fileName)
	    iterations += 1

