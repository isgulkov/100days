
player_one = list(raw_input())
player_two = list(raw_input())

player_one.sort()
player_two.sort(key=lambda c: -ord(c))

result = ['?' for c in player_one]

player_one = player_one[:len(result) / 2 + len(result) % 2]
player_two = player_two[:len(result) / 2]

pos_left, pos_right = 0, len(result) - 1

for i in xrange(len(result)):
    if i % 2 == 0:
        this_player = player_one
    else:
        this_player = player_two

    if len(player_one) != 0 and len(player_two) != 0 and player_one[0] < player_two[0]:
        # If it is favourable to put current best letter in front, do so

        result[pos_left] = this_player.pop(0)

        pos_left += 1
    else:
        # Otherwise, put current worst letter at the back

        result[pos_right] = this_player.pop()

        pos_right -= 1

print ''.join(result)
