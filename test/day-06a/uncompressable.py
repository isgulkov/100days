from random import choice

alphabet = [chr(x) for x in xrange(ord('a'), ord('z') + 1)]

print "".join([choice(alphabet) for i in xrange(8000)])
