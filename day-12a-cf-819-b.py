
n = int(raw_input())

ps = map(int, raw_input().split(' '))

deviations = [0 for i in xrange(n)]

for i in xrange(n):
    # Add abs(ps[i] - ((i + shift) % n + 1)) to each deviations[shift] with absolutes opened up

    if ps[i] >= i + 1:
        for shift in xrange(0, ps[i] - i):
            deviations[shift] += ps[i] - ((i + shift) % n + 1)

        for shift in xrange(ps[i] - i, n - i):
            deviations[shift] -= ps[i] - ((i + shift) % n + 1)

        for shift in xrange(n - i, n):
            deviations[shift] += ps[i] - ((i + shift) % n + 1)
    else:
        for shift in xrange(0, n - i):
            deviations[shift] -= ps[i] - ((i + shift) % n + 1)

        for shift in xrange(n - i, n - i + ps[i]):
            deviations[shift] += ps[i] - ((i + shift) % n + 1)

        for shift in xrange(n - i + ps[i], n):
            deviations[shift] -= ps[i] - ((i + shift) % n + 1)

min_deviation, min_shift = deviations[0], 0

for i in xrange(n):
    if deviations[i] < min_deviation:
        min_deviation = deviations[i]
        min_shift = i

print min_deviation, min_shift
