
n = int(raw_input())

ps = map(int, raw_input().split(' '))

deviations = [0 for i in xrange(n)]

for i_p in xrange(n):
    for shift in xrange(n):
        deviations[shift] += abs(ps[i_p] - ((i_p + shift) % n + 1))

min_deviation, min_shift = deviations[0], 0

for i in xrange(n):
    if deviations[i] < min_deviation:
        min_deviation = deviations[i]
        min_shift = i

print min_deviation, min_shift
