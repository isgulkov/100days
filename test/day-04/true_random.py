from random import choice, randint

alphabet = [chr(i) for i in xrange(ord('a'), ord('z') + 1)]

random_string = "".join([choice(alphabet) for i in xrange(10000)])

occurences = {}

for i in xrange(100):
	substring = ""

	while substring == "" or substring in occurences:
		start = randint(0, len(random_string) - 1)
		end = start + randint(1, min(len(random_string) - 1 - start, 5))

		substring = random_string[start:end]

	occurences[substring] = []

	for j in xrange(len(random_string)):
		if random_string[j:j + len(substring)] == substring:
			occurences[substring].append(j)

print len(occurences)

for substring in occurences:
	print substring, len(occurences[substring]), 

	for si in occurences[substring]:
		print si,

	print
