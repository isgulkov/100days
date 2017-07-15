

n = int(raw_input())

substrings = []
substring_occurences = {}

for i in xrange(n):
	line = raw_input().split(' ')

	substrings.append(line[0])
	substring_occurences[line[0]] = map(int, line[2:])

print substrings
print substring_occurences
