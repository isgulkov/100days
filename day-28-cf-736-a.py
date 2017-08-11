
# Returns the minimum number of players that need to be in the tournament for the champion to play at least `x` games
def players_for_champ_level(x):
    if x == 1:
        return 2
    elif x == 2:
        return 3
    else:
        # For the champion to get to the level `x` (play `x` games) he needs to be level `x` - 1 and there needs to be
        # another player of level `x` - 2
        return players_for_champ_level(x - 1) + players_for_champ_level(x - 2)

x = int(raw_input())

champ_level = 0

while players_for_champ_level(champ_level + 1) <= x:
    champ_level += 1

print champ_level
