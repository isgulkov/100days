
a, b, c, total_increase = map(int, raw_input().split(' '))

num_invalid_triples = 0

for a, b, c in ((a, b, c), (b, a, c), (c, a, b)):
    for a_increase in xrange(total_increase + 1):
        bc_max_increase = min(total_increase - a_increase, a + a_increase - (b + c))

        for bc_increase in xrange(0, bc_max_increase + 1):
            num_invalid_triples += (bc_increase + 1)

# The total number of all possible triples of sum less than or equal `total_increase` equals the number of ways to
# divide a sequence of `total_increase` elements into four parts, which is:
#   C(`total_increase` + 3, 3) = (`total_increase` + 3)! / (3! * `total_uncrease`!) =
num_all_triples = (total_increase + 1) * (total_increase + 2) * (total_increase + 3) / 6

print num_all_triples - num_invalid_triples
