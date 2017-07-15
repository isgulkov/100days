

def insert_substring(target, arrow, start_index):
	for i in xrange(len(arrow)):
		target[start_index + i] = arrow[i]

n = int(raw_input())

substring_occurences = []

s_length = 0

for i in xrange(n):
	line = raw_input().split(' ')

	substring = line[0]
	occurences = map(int, line[2:])

	for occurence in occurences:
		# Make string indices zero-based
		substring_occurences.append((occurence - 1, substring, ))

	candidate_length = len(substring) + occurences[-1] - 1

	if candidate_length > s_length:
		s_length = candidate_length

s = ["a"] * s_length

substring_occurences.sort(key=lambda x: x[0])

last_unprocessed_symbol = 0

for start_index, substring in substring_occurences:
	if start_index + len(substring) - 1 < last_unprocessed_symbol:
		continue

	insert_substring(s, substring, start_index)

	last_unprocessed_symbol = start_index + len(substring)

	if last_unprocessed_symbol >= s_length:
		break

print "".join(s)
