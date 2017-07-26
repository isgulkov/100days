
n = int(raw_input())

ps = map(int, raw_input().split(' '))

deviations = [0 for i in xrange(n)]

for i in xrange(n):
    for j in xrange(n):
        deviations[i] += abs(ps[(j - i) % n] - (j + 1))

min_deviation, min_shift = deviations[0], 0

for i in xrange(n):
    if deviations[i] < min_deviation:
        min_deviation = deviations[i]
        min_shift = i

print min_deviation, min_shift
