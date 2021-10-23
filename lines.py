import glob
import sys
argv = sys.argv
files = glob.glob(str(argv[1]) + '\\**\\*.h', recursive=True)
lines_h = 0
files_h = 0
lines_cpp = 0
files_cpp = 0
lines_hpp = 0
files_hpp = 0

def count(filename):
	lines = 0
	for line in open(filename):
		lines += 1
	return lines


for file in files:
	lines_h += count(file)
	files_h += 1
	
files = glob.glob(str(argv[1]) + '\\**\\*.cpp', recursive=True)
for file in files:
	lines_cpp += count(file)
	files_cpp += 1
	
files = glob.glob(str(argv[1]) + '\\**\\*.hpp', recursive=True)
for file in files:
	lines_hpp += count(file)
	files_hpp += 1
	
files = files_h + files_cpp + files_hpp
lines = lines_h + lines_cpp + lines_hpp
	
print ("files *.h: " + str(files_h))
print ("flies *.cpp: " + str(files_cpp))
print ("files *.hpp: " + str(files_hpp))
print ("files: " + str(files))
print ("lines *.h: " + str(lines_h))
print ("lines *.cpp: " + str(lines_cpp))
print ("lines *.hpp: " + str(lines_hpp))
print ("lines: " + str(lines))