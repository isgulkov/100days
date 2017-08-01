from math import ceil
from sys import exit

class Cup:
    def __init__(self, index, volume):
        self.volume = volume
        self.index = index

        self.amount = 0

    def _get_min_amount(self):
        return int(ceil(self.volume / 2.0))

    min_amount = property(_get_min_amount)

    def fill_up_to_minimum(self):
        self.amount += self.min_amount

    def _get_surplus(self):
        return self.volume - self.amount

    def add(self, x):
        self.amount += x

    surplus = property(_get_surplus)

n, total_amount = map(int, raw_input().split(' '))

volumes = map(int, raw_input().split(' '))

cups = [Cup(i, volumes[i]) for i in xrange(n)]

# Fill every cup to its minimum amount.
#
# This satisfies the conditions because
#   volume_i < volume_j => amount_i = ceil(volume_i / 2.0) <= ceil(volume_j / 2.0) = amount_j

for cup in cups:
    total_amount -= cup.min_amount

    cup.fill_up_to_minimum()

if total_amount < 0:
    print -1
    exit(0)

# Distribute any leftovers over the cups by filling them up in order in order of descending volumes
#
# This maintains volume_i < volume_j => amount_i <= amount_j because for every such i, j we add a >= 0 to amout_j

cups.sort(key=lambda cup: -cup.volume)

for cup in cups:
    if total_amount == 0:
        break

    addition = min(total_amount, cup.surplus)

    cup.add(addition)
    total_amount -= addition

cups.sort(key=lambda cup: cup.index)

for cup in cups:
    print cup.amount,

print
