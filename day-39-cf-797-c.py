
s = raw_input()

a_stack = []

for c in reversed(s):
    a_stack.append(c)

b_stack = []
c_stack = []

while len(a_stack) != 0:
    # It is always the best to extract the minimum character from the "a" stack and put it in front of the string

    min_char = min(a_stack)

    # If some occurrences of the current `min_char` or better character accidentally got on top of the "b" stack while
    # the previous `min_char` was extracted, put them on top of the "c" stack not to bury them when extracting the
    # current `min_char`
    while len(b_stack) > 0 and b_stack[-1] <= min_char:
        c_stack.append(b_stack.pop())

    # Extract the `min_char`
    while a_stack[-1] != min_char:
        b_stack.append(a_stack.pop())

    # The actual legal transfer would be a -> b -> c
    c_stack.append(a_stack.pop())

# Dump all that's remaining on the "b" stack onto the "c" stack. Nothing else can be done at this point
while len(b_stack) != 0:
    c_stack.append(b_stack.pop())

print ''.join(c_stack)
