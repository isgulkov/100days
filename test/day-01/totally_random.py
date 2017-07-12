from sys import argv
from random import randint

n = int(argv[1])

if len(argv) == 4:
	a, b = int(argv[2]), int(argv[3])
else:
	a, b = -(10 ** 9), 10 ** 9


print n

for i in xrange(n):
	print randint(a, b),
