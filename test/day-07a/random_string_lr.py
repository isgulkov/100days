from sys import argv
from random import choice

print "".join([choice(('l', 'r', )) for i in xrange(int(argv[1]))])
