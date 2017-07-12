
n = int(raw_input())

xs = map(int, raw_input().split(' '))

fs = map(lambda (x, y): abs(x - y), zip(xs, xs[1:]))

fs_start_even = [fs[i] * (-1) ** i for i in xrange(n - 1)]
fs_start_odd = [fs[i] * (-1) ** (i + 1) for i in xrange(n - 1)]

'''
Returns the maximum sum of a subarray of the `fs` array that starts at an odd or
even index depending on value the `shift` paramenter
'''
def max_sum(fs, shift):
	if shift not in [0, 1]:
		raise Exception("yebanulsya?")

	min_sifted_sum = 0
	max_shifted_sum = 0

	current_sum = 0

	for i in xrange(n - 1):
		current_sum += fs[i]

		# If current sum is the new minimum and the current subarray ends at an
		# index that is NOT of the specified `shift`, which means that the
		# subrray after it will start at an index of the specified `shift`
		if i % 2 != shift and current_sum < min_sifted_sum:
			min_sifted_sum = current_sum

		max_shifted_sum = max(max_shifted_sum, current_sum - min_sifted_sum)

	return max_shifted_sum

max_even_starting_sum = max_sum(fs_start_even, shift=0)
max_odd_starting_sum = max_sum(fs_start_odd, shift=1)

print max(max_even_starting_sum, max_odd_starting_sum)
