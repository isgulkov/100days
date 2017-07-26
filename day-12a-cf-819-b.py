from sys import maxint


class OfflineSegment:
    def __init__(self, length):
        self.length = length

        self._values = [0 for i in xrange(length)]
        self._deltas = [0 for i in xrange(length)]

    '''
    Add members of arithmetic progression with initial term -`first` and difference -1 to indices [l; r)
    '''
    def subtract_increasing(self, l, r, first):
        if l < self.length:
            self._values[l] += -first
            self._deltas[l] += 1

        if r < self.length:
            self._values[r] -= r - l - first
            self._deltas[r] -= 1

    '''
    Add members of arithmetic progression with initial term `first` and difference -1 to indices [l; r)
    '''
    def add_decreasing(self, l, r, first):
        if l < self.length:
            self._values[l] += first
            self._deltas[l] += -1

        if r < self.length:
            self._values[r] -= -(r - l) + first
            self._deltas[r] -= -1

    def _restore(self):
        deltas_interp = self._deltas[:]

        for i in xrange(1, self.length):
            deltas_interp[i] += deltas_interp[i - 1]

        restored_values = self._values[:]

        for i in xrange(1, self.length):
            restored_values[i] += deltas_interp[i - 1]

        for i in xrange(1, self.length):
            restored_values[i] += restored_values[i - 1]

        return restored_values

    '''
    Return segment's minimum value and the value's index
    '''
    def get_minimum(self):
        restored_values = self._restore()

        min_value, min_index = maxint, None

        for i in xrange(n):
            if restored_values[i] < min_value:
                min_value = restored_values[i]
                min_index = i

        return min_value, min_index


# pidr = OfflineSegment(10)

# pidr.subtract_increasing(2, 5, -2)

n = int(raw_input())

deviations = OfflineSegment(n)

ps = map(int, raw_input().split(' '))

for i in xrange(n):
    # Add abs(ps[i] - ((i + shift) % n + 1)) to each deviations[shift] with absolutes and modulos opened up

    if ps[i] >= i + 1:
        deviations.add_decreasing(0, ps[i] - i, ps[i] - (i + 1))

        deviations.subtract_increasing(ps[i] - i, n - i, ps[i] - (i + ps[i] - i + 1))

        deviations.add_decreasing(n - i, n, ps[i] - (i + n - i - n + 1))
    else:
        deviations.subtract_increasing(0, n - i, ps[i] - (i + 1))

        deviations.add_decreasing(n - i, n - i + ps[i], ps[i] - (i + n - i - n + 1))

        deviations.subtract_increasing(n - i + ps[i], n, ps[i] - (i + n - i + ps[i] - n + 1))

min_deviation, min_shift = deviations.get_minimum()

print min_deviation, min_shift
