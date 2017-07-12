from os import system
from sys import argv
from glob import glob

programs = [argv[1], ]

filenames_start = 2

if argv[2] in ['-a', '--against']:
	programs.append(argv[3])

	filenames_start += 2

for test_file in argv[filenames_start:]:
	print test_file, ": "

	for program in programs:
		if len(programs) > 1:
			print "\t", program

		system("%s < %s" % (program, test_file))

	print
