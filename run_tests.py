from os import system
from sys import argv
from glob import glob

for test_file in argv[2:]:
	print test_file, ": "

	system("%s < %s" % (argv[1], test_file))

	print
