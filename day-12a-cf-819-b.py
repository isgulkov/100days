
class OfflineSegment:
    def __init__(self, length):
        self.length = length

        self.values = [0 for i in xrange(length)]

    '''
    Add members of arithmetic progression with initial term -`first` and difference -1 to indices [l; r)
    '''
    def subtract_increasing(self, l, r, first):
        for i in xrange(l, r):
            self.values[i] -= first - (i - l)

    '''
    Add members of arithmetic progression with initial term `first` and difference -1 to indices [l; r)
    '''
    def add_decreasing(self, l, r, first):
        for i in xrange(l, r):
            self.values[i] += first - (i - l)

    '''
    Return segment's minimum value and the value's index
    '''
    def get_minimum(self):
        min_value, min_shift = self.values[0], 0

        for i in xrange(n):
            if self.values[i] < min_value:
                min_value = self.values[i]
                min_shift = i

        return min_value, min_shift


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
