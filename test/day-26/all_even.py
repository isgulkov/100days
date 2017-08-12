from sys import argv
from random import randint

n = int(argv[1])

print n

for i in xrange(n):
    print 2 * randint(1, 10000000), 

