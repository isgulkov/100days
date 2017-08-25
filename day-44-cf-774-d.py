from sys import exit

n_items, l, r = map(int, raw_input().split(' '))

xs = map(int, raw_input().split(' '))

ys = map(int, raw_input().split(' '))

l, r = l - 1, r - 1

# Check if cubes outside [l; r] are untouched

for i in xrange(0, l):
    if xs[i] != ys[i]:
        print "LIE"

        exit(0)

for i in xrange(r + 1, len(xs)):
    if xs[i] != ys[i]:
        print "LIE"

        exit(0)

# Check if the cubes in [l; r] only differ in order

xs_lr = xs[l:r + 1]
ys_lr = ys[l:r + 1]

xs_lr.sort()
ys_lr.sort()

for i in xrange(r - l + 1):
    if xs_lr[i] != ys_lr[i]:
        print "LIE"

        exit(0)

print "TRUTH"

