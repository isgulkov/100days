from sys import maxint, exit

num_rows, num_cols = map(int, raw_input().split(' '))

playing_field_rows = []

for i in xrange(num_rows):
	playing_field_rows.append(map(int, raw_input().split(' ')))

moves = []

# Remove surplises from rows

row_maxes = []

for row in playing_field_rows:
	row_maxes.append(max(row))

smallest_row_max = min(row_maxes)

for i_row in xrange(num_rows):
	surplus = row_maxes[i_row] - smallest_row_max

	for j in xrange(surplus):
		moves.append("row %d" % (i_row + 1, ))

	if surplus != 0:
		playing_field_rows[i_row] = map(lambda x: x - surplus, playing_field_rows[i_row])

# Remove surpluses from columns

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

for i_col in xrange(num_cols):
	surplus = col_maxes[i_col] - smallest_col_max

	for j in xrange(surplus):
		moves.append("col %d" % (i_col + 1, ))

	if surplus != 0:
		map_column(lambda x: x - surplus, i_col, playing_field_rows)

# At this point all cells must have the same and non-negative value

common_value = playing_field_rows[0][0]

if common_value < 0:
	print -1
	exit(0)

for i_row in xrange(num_rows):
	for i_col in xrange(num_cols):
		current_cell = playing_field_rows[i_row][i_col]

		if current_cell != common_value:
			print -1
			exit(0)

for i_row in xrange(num_rows):
	for j in xrange(common_value):
		moves.append("row %d" % (i_row, ))

print len(moves)

for move in moves:
	print move
