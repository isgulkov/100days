
s = raw_input()

a_stack = []

for c in reversed(s):
    a_stack.append(c)

b_stack = []
c_stack = []

while len(a_stack) != 0:
    current_min = min(a_stack)

    while len(b_stack) > 0 and b_stack[-1] == current_min:
        c_stack.append(b_stack.pop())

    while a_stack[-1] != current_min:
        b_stack.append(a_stack.pop())

    c_stack.append(a_stack.pop())

while len(b_stack) != 0:
    c_stack.append(b_stack.pop())

print ''.join(c_stack)
