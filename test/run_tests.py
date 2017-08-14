from os import system
from sys import argv
from glob import glob

commands = [argv[1], ]

filenames_start = 2

if argv[2] in ['-a', '--against']:
	commands.append(argv[3])

	filenames_start += 2

for i in xrange(len(commands)):
    if commands[i][-3:] == '.py':
        commands[i] = "python " + commands[i]

for test_file in argv[filenames_start:]:
	print test_file, ": "

	for program in commands:
		if len(commands) > 1:
			print "\t", program

		system("%s < %s" % (program, test_file))

	print
