from random import choice

alphabet = ['a'] * 25 + ['b']

print "".join([choice(alphabet) for i in xrange(8000)])
