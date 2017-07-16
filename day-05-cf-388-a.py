from sys import maxint

raw_input()

box_caps = map(int, raw_input().split(' '))

box_caps.sort(key=lambda x: -x)

stacks = []

while len(box_caps) != 0:
	current_cap = box_caps.pop()

	# Select for the current element a stack that it can hold with the lowest surplus capacity
	selected_stack = None
	min_surplus = maxint

	for stack in stacks:
		current_surplus = current_cap - len(stack)

		if current_surplus >= 0 and current_surplus < min_surplus:
			min_surplus = current_surplus
			selected_stack = stack

	if selected_stack is not None:
		selected_stack.append(current_cap)
	else:
		# If no stack found that the current element can hold, create a new stack with the element at the top
		stacks.append([current_cap])

print len(stacks)
