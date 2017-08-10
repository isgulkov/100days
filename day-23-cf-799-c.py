from bisect import bisect_right

def best_pair_score(fountains, max_cost):
    fountains.sort(key=lambda f: f[1])

    fountain_costs = map(lambda f: f[1], fountains)

    # For each index in `fountains` store the best score of a fountain of this fountain's cost or smaller
    best_score_under = []

    current_best = 0

    for f in fountains:
        if f[0] > current_best:
            current_best = f[0]

        best_score_under.append(current_best)

    best_score = 0

    for i in xrange(len(fountains) - 1, 0, -1):
        j = bisect_right(fountain_costs, max_cost - fountains[i][1], hi=i)

        # `bisect_right` returns an index to the right of any occurences of the target value
        j -= 1

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

print max(
    best_pair_score(affordable_coin_fountains, coins),
    best_pair_score(affordable_gem_fountains, gems),
    best_two_currencies_score
    )
