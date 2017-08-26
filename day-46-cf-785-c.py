from math import ceil, sqrt

max_capacity, daily_increase = map(int, raw_input().split(' '))

# Number of days after which sparrows will start to overcome the daily increase
result = daily_increase

# Number of days after which sparrows will empty the granary when they steal more grain than `daily_increase`
#
# After day `daily_increase` the amount of grain available at the end of day will decrease by amounts starting from 1
# and on day `daily_increase` + j > `daily_increase` it will be:
#   `max_capacity` - sum(1, j),
# where sum(a, b) is the sum of integers from a to b inclusive.
#
# So, for the granary to be emptied on a day `daily_increase` + j, we need it to contain less grain than
# `daily_increase` + j:
#   `max_capacity` - sum(1, j - 1) <= `daily_increase` + j, or
#   `max_capacity` - `daily_increase` - sum(1, j) <= 0.
# Solving that for j, we get the formula below.

result += int(ceil(0.5 * (sqrt(1 - 8 * daily_increase + 8 * max_capacity) - 1.0)))

print min(max_capacity, result)
