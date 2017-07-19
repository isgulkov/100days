from sys import maxint

num_rows, num_cols = map(int, raw_input().split(' '))

playing_field_rows = []

for i in xrange(num_rows):
	playing_field_rows.append(map(int, raw_input().split(' ')))

moves = []

row_maxes = []

for row in playing_field_rows:
	row_maxes.append(max(row))

smallest_row_max = min(row_maxes)

for i in xrange(num_rows):
	surplus = row_maxes[i] - smallest_row_max

	for j in xrange(surplus):
		moves.append("row %d" % (i + 1, ))

	if surplus != 0:
		playing_field_rows[i] = map(lambda x: x - surplus, playing_field_rows[i])

def get_column(i_col, rows):
	return [rows[j][i_col] for j in xrange(num_rows)]

def map_column(f, i_col, rows):
	mapped_column = map(f, get_column(i_col, rows))

	for i in xrange(num_rows):
		rows[i][i_col] = mapped_column[i]

col_maxes = []

for column in [get_column(i, playing_field_rows) for i in xrange(num_cols)]:
	col_maxes.append(max(column))

smallest_col_max = min(col_maxes)

for i in xrange(num_cols):
	surplus = col_maxes[i] - smallest_col_max

	for j in xrange(surplus):
		moves.append("col %d" % (i + 1, ))

	if surplus != 0:
		map_column(lambda x: x - surplus, i, playing_field_rows)

for move in moves:
	print move
