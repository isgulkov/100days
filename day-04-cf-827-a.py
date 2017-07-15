

n = int(raw_input())

substrings = []
substring_occurences = {}

s_length = 0

for i in xrange(n):
	line = raw_input().split(' ')

	current_substring = line[0]
	current_occurences = map(int, line[2:])

	candidate_length = len(current_substring) + current_occurences[-1] - 1

	if candidate_length > s_length:
		s_length = candidate_length

	substrings.append(current_substring)
	substring_occurences[line[0]] = current_occurences

print substrings
print substring_occurences
print s_length
