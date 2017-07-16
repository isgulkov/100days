
raw_input()

box_caps = map(int, raw_input().split(' '))

box_caps.sort()

num_stacks = 0

while len(box_caps) != 0:
	current_cap = box_caps.pop()

	while current_cap > 0:
		next_cap = box_caps.pop()

		current_cap -= 1

		if next_cap < current_cap:
			current_cap = next_cap

	num_stacks += 1

print num_stacks

