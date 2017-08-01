from math import ceil

n, total_amount = map(int, raw_input().split(' '))

volumes = map(int, raw_input().split(' '))

volume_to_amount = {}
volume_to_count = {}

for volume in volumes:
    volume_to_amount[volume] = 0

    if volume in volume_to_count:
        volume_to_count[volume] += 1
    else:
        volume_to_count[volume] = 1

prev_amount = 0

# Assign minimum possible amout to cups of every volume

for volume in sorted(volume_to_amount.keys()):
    this_amount = max(
        prev_amount + 1,
        int(ceil(volume / 2.0))
        )

    volume_to_amount[volume] = this_amount
    total_amount -= this_amount * volume_to_count[volume]

    if total_amount < 0:
        break

    prev_amount = this_amount

# Try to distribute any leftovers over the cups

cup_amounts = [(volume_to_amount[volumes[i]], i, ) for i in xrange(n)]

cup_amounts.sort(key=lambda x: volumes[x[1]])

prev_amount = float("+inf")

for i in reversed(range(n)):
    if total_amount == 0:
        break

    amount, index = cup_amounts[i]

    # If this cup's volume is less that that of the previous one, this cup's amount must also be less
    if i != n - 1:
        next_cup_index = cup_amounts[i + 1][1]

        if volumes[index] < volumes[next_cup_index]:
            prev_amount -= 1

    addition = max(0,
        min(
            total_amount,
            volumes[index] - amount,
            prev_amount
            )
        )

    cup_amounts[i] = (amount + addition, index, )

    total_amount -= addition

    prev_amount = amount + addition

cup_amounts.sort(key=lambda x: x[1])

if total_amount == 0:
    for amount, _ in cup_amounts:
        print amount,

    print
else:
    print -1
