
class GameSolver:
    def __init__(self, playing_field_rows, num_rows, num_cols):
        self.playing_field_rows = playing_field_rows
        self.num_rows = num_rows
        self.num_cols = num_cols

        self._solvable = True
        self._moves = []

        self._remove_row_surpluses()
        self._remove_column_surpluses()
        self._level_field()

    def _is_solvable(self):
        return self._solvable

    is_solvable = property(_is_solvable)

    def _get_moves(self):
        if self._solvable:
            return self._moves
        else:
            raise Exception("yobnulsia?")

    moves = property(_get_moves)

    def _remove_row_surpluses(self):
        """
        Removes surplus max values from rows that have them, recording the moves that lead to this situation
        """

        row_maxes = []

        for row in self.playing_field_rows:
            row_maxes.append(max(row))

        smallest_row_max = min(row_maxes)

        for i_row in xrange(self.num_rows):
            surplus = row_maxes[i_row] - smallest_row_max

            for j in xrange(surplus):
                self._moves.append("row %d" % (i_row + 1, ))

            if surplus != 0:
                self.playing_field_rows[i_row] = map(lambda x: x - surplus, self.playing_field_rows[i_row])

    def _get_column(self, i_col):
        return [self.playing_field_rows[j][i_col] for j in xrange(num_rows)]

    def _map_column(self, f, i_col):
        mapped_column = map(f, self._get_column(i_col))

        for i in xrange(self.num_rows):
            self.playing_field_rows[i][i_col] = mapped_column[i]

    def _remove_column_surpluses(self):
        """
        Removes surplus max values from columns that have them, recording the moves that lead to this situation
        """

        col_maxes = []

        for column in [self._get_column(i) for i in xrange(self.num_cols)]:
            col_maxes.append(max(column))

        smallest_col_max = min(col_maxes)

        for i_col in xrange(self.num_cols):
            surplus = col_maxes[i_col] - smallest_col_max

            for j in xrange(surplus):
                self._moves.append("col %d" % (i_col + 1, ))

            if surplus != 0:
                self._map_column(lambda x: x - surplus, i_col)

    def _level_field(self):
        """
        Checks that the playing field is level after the max value surpluses are removed. If so, records the minimum
        number of moves that could lead to this situation
        """

        common_value = self.playing_field_rows[0][0]

        if common_value < 0:
            self._solvable = False
            return

        for i_row in xrange(self.num_rows):
            for i_col in xrange(self.num_cols):
                current_cell = self.playing_field_rows[i_row][i_col]

                if current_cell != common_value:
                    self._solvable = False
                    return

        if self.num_rows <= self.num_cols:
            for i_row in xrange(self.num_rows):
                for j in xrange(common_value):
                    self._moves.append("row %d" % (i_row + 1, ))
        else:
            for i_col in xrange(self.num_cols):
                for j in xrange(common_value):
                    self._moves.append("col %d" % (i_col + 1, ))


if __name__ == '__main__':
    num_rows, num_cols = map(int, raw_input().split(' '))

    playing_field_rows = []

    for i in xrange(num_rows):
        playing_field_rows.append(map(int, raw_input().split(' ')))

    solver = GameSolver(playing_field_rows, num_rows, num_cols)

    if solver.is_solvable:
        print len(solver.moves)

        for move in solver.moves:
            print move
    else:
        print -1
