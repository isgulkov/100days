
raw_input()

box_caps = map(int, raw_input().split(' '))

box_caps.sort()

num_stacks = 0

while len(box_caps) != 0:
	current_cap = box_caps.pop()

	i = len(box_caps) - 1

	while i >= 0:
		if box_caps[i] >= current_cap:
			i -= 1

			continue

		next_cap = box_caps[i]
		del box_caps[i]

		current_cap -= 1

		if next_cap < current_cap:
			current_cap = next_cap

		i -= 1

	num_stacks += 1

print num_stacks

