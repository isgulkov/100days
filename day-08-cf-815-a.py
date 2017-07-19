from sys import maxint

n, m = map(int, raw_input().split(' '))

playing_field_rows = []

for i in xrange(n):
	playing_field_rows.append(map(int, raw_input().split(' ')))

moves = []

row_maxes = []

for row in playing_field_rows:
	row_maxes.append(max(row))

smallest_row_max = min(row_maxes)

for i in xrange(len(playing_field_rows)):
	surplus = row_maxes[i] - smallest_row_max

	for j in xrange(surplus):
		moves.append("row %d" % (i + 1, ))

	if surplus != 0:
		playing_field_rows[i] = map(lambda x: x - surplus, playing_field_rows[i])

for move in moves:
	print move
