
n, num_requests, _ = map(int, raw_input().split(' '))

initial_values = map(int, raw_input().split(' '))

requests = []

for _ in xrange(num_requests):
    t, l, r = map(int, raw_input().split(' '))

    requests.append((t == 1 and 'shift' or 'reverse', l - 1, r - 1, ))

positions = [int(x) - 1 for x in raw_input().split(' ')]

for request in reversed(requests):
    print request
