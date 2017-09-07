
a, b, c, total = map(int, raw_input().split(' '))

result = 0

for a_increase in xrange(0, total + 1):
    for b_increase in xrange(0, total - a_increase + 1):
        for c_increase in xrange(0, total - a_increase - b_increase + 1):
            new_a, new_b, new_c = a + a_increase, b + b_increase, c + c_increase

            new_a, new_b, new_c = sorted((new_a, new_b, new_c, ))

            if new_c < new_a + new_b:
                result += 1

print result
