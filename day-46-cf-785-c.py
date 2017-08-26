from math import ceil, sqrt

max_capacity, daily_increase = map(int, raw_input().split(' '))

if daily_increase > max_capacity:
    # Amount of grain can't be increase beyond capacity and the formula below break down with such numbers

    daily_increase = max_capacity

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
#   `max_capacity` - `daily_increase` - j * (j + 1) / 2 <= 0.
#
# Find smallest such j using binary search

l = 0
r = 10 ** 18

while r - l > 0:
    mid = l + (r - l) / 2

    # print l, mid, r

    day_start_amout = max_capacity - daily_increase - mid * (mid + 1) / 2

    if day_start_amout <= 0:
        r = mid
    elif day_start_amout > 0:
        l = mid + 1

result += l

# Also consider the case if sparrows will at some point empty the granary in one day without overpowering the
# `daily_increase`

result = min(max_capacity, result)

print result
