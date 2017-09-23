
n, num_requests, _ = map(int, raw_input().split(' '))

initial_values = map(int, raw_input().split(' '))

requests = []

for _ in xrange(num_requests):
    t, l, r = map(int, raw_input().split(' '))

    requests.append((t == 1 and 'right_shift' or 'reverse', l - 1, r - 1, ))

positions = [int(x) - 1 for x in raw_input().split(' ')]

# Instead of performing the sequence of requests on the array elements, play the sequence back in reverse order on
# the postitions of interest. The resulting positions will be the positions in the initial array from which the elements
# at positions of interest would have originated after the sequence would've been applied.
#
# This is possible because both subarray reverse and subarray shift are bijective operations.

for request_type, l, r in reversed(requests):
    if request_type == 'reverse':
        for i, p in enumerate(positions):
            # The inverse of reverse is just reverse
            if l <= p <= r:
                positions[i] = l + r - p
    elif request_type == 'right_shift':
        for i, p in enumerate(positions):
            # Perform left shift -- the inverse of right shift
            if p == l:
                positions[i] = r
            elif l < p <= r:
                positions[i] -= 1

print ' '.join(str(initial_values[p]) for p in positions)
