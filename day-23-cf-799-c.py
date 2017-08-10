
def best_pair_score(fountains, max_cost):
    best_score = 0

    for i in xrange(len(fountains)):
        for j in xrange(i + 1, len(fountains)):
            a = fountains[i]
            b = fountains[j]

            if a[1] + b[1] <= max_cost and a[0] + b[0] > best_score:
                best_score = a[0] + b[0]

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
