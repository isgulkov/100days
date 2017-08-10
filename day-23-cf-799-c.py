
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

print coin_fountains
print gem_fountains
