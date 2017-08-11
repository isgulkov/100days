
n, k = map(int, raw_input().split(' '))

effective = [w == "YES" for w in raw_input().split(' ')]

names = range(k - 1)

for i in xrange(k - 1, n):
    names.append(i)

print names
