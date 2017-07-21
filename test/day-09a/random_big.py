from random import randint
from sys import argv

n = int(argv[1])

print n

for i in xrange(n):
    print randint(1, 5000),

print

