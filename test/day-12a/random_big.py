from sys import argv
from random import shuffle

n = int(argv[1])

print n

permutation = range(1, n + 1)

shuffle(permutation)

for x in permutation:
    print x, 

print
