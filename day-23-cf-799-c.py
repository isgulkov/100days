from bisect import bisect_right

# Find the cumulutive score (tuple item 0) of a pair of elements from `fountains` with the largest such score, for which
# the cumulative cost (tuple item 1) is less than or equal to `max_cost`
def best_pair_score(fountains, max_cost):
    fountains.sort(key=lambda f: f[1])

    fountain_costs = map(lambda f: f[1], fountains)

    # For each index in `fountains` store the largest score of a fountain of this fountain's cost or smaller
    best_score_under = []

    current_best = 0

    for f in fountains:
        if f[0] > current_best:
            current_best = f[0]

        best_score_under.append(current_best)

    best_score = 0

    for i in xrange(len(fountains) - 1, 0, -1):
        # Find the most expensive fountain we can buy together with this fountain

        j = bisect_right(fountain_costs, max_cost - fountains[i][1], hi=i) - 1

        if i > j >= 0:
            best_score = max(best_score, fountains[i][0] + best_score_under[j])

    return best_score

num_fountains, coins, gems = map(int, raw_input().split(' '))

coin_fountains = []
gem_fountains = []

for i in xrange(num_fountains):
    prettiness, cost, currency = raw_input().split(' ')

    fountain = (int(prettiness), int(cost), )

    if currency == 'C':
        coin_fountains.append(fountain)
    elif currency == 'D':
        gem_fountains.append(fountain)

affordable_coin_fountains = filter(lambda f: f[1] <= coins, coin_fountains)
affordable_gem_fountains = filter(lambda f: f[1] <= gems, gem_fountains)

if len(affordable_coin_fountains) == 0 or len(affordable_gem_fountains) == 0:
    best_two_currencies_score = 0
else:
    best_two_currencies_score = max(affordable_coin_fountains)[0] + max(affordable_gem_fountains)[0]

# Take max of best scores for several cases:
print max(
    best_pair_score(affordable_coin_fountains, coins), # Buy both fountains for coins
    best_pair_score(affordable_gem_fountains, gems), # Buy both fountains for gems
    best_two_currencies_score # Buy one fountain for coins, the other for gems
    )
