
n = int(raw_input())

xs = map(int, raw_input().split(' '))

fs = map(lambda (x, y): abs(x - y), zip(xs, xs[1:]))

max_sum = 0

for l in xrange(n):
	for r in xrange(l, n):
		current_sum = 0

		for i in xrange(l, r):
			if (i - l) % 2 == 0:
				current_sum += fs[i]
			else:
				current_sum -= fs[i]

		if current_sum > max_sum:
			max_sum = current_sum

print max_sum
