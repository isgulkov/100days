
n = int(raw_input())

xs = map(int, raw_input().split(' '))

fs = map(lambda (x, y): abs(x - y), zip(xs, xs[1:]))
