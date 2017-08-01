
n, m = map(int, raw_input().split(' '))

min_interval_length = float("+inf")

for i in xrange(m):
    a, b = map(int, raw_input().split(' '))

    interval_length = b - a + 1

    if interval_length < min_interval_length:
        min_interval_length = interval_length

# The resulting score will be less than or equal to the length of the minimum interval
#
# Make the score exactly that: print an array of numbers numbers 0, 1, ... , (min_interval_length - 1). Then each of
# these numbers will appear at least one in the smallest interval as well as all larger ones

print min_interval_length

x = 0

for i in xrange(n):
    print x,

    x = (x + 1) % min_interval_length

print
