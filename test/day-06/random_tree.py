from sys import argv
from random import randint

n = int(argv[1])

print n, n - 1

for i in xrange(1, n):
	print i + 1, randint(1, i)
