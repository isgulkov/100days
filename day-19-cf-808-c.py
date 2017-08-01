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

for volume in sorted(volume_to_amount.keys()):
    this_amount = max(prev_amount + 1, int(ceil(volume / 2.0)))

    volume_to_amount[volume] = this_amount
    total_amount -= this_amount * volume_to_count[volume]

    if total_amount < 0:
        break

    prev_amount = this_amount

if total_amount >= 0:
    print [volume_to_amount[v] for v in  volumes]
else:
    print -1
