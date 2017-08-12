from sys import argv
from random import randint

x = int(argv[1])
n = int(argv[2])

print n

for i in xrange(n):
    print x * randint(1, 10 ** 9 / x - 1), 

