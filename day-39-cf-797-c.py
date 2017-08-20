
s = raw_input()

a_stack = []

a_stack_occurrences = {chr(c): 0 for c in xrange(ord('a'), ord('z') + 1)}

for c in reversed(s):
    a_stack.append(c)

    # Maintain the number of times each symbol occurs in the "a" stack (for faster minimum extraction)
    a_stack_occurrences[c] += 1

b_stack = []
c_stack = []

while len(a_stack) != 0:
    # It is always the best to extract the minimum character from the "a" stack and put it in front of the string

    min_char = filter(lambda k: a_stack_occurrences[k] != 0, a_stack_occurrences.keys())[0]

    # If some occurrences of the current `min_char` or better character accidentally got on top of the "b" stack while
    # the previous `min_char` was extracted, put them on top of the "c" stack not to bury them when extracting the
    # current `min_char`
    while len(b_stack) > 0 and b_stack[-1] <= min_char:
        c_stack.append(b_stack.pop())

    # Extract the `min_char`
    while a_stack[-1] != min_char:
        top = a_stack.pop()

        b_stack.append(top)

        a_stack_occurrences[top] -= 1

    # The actual legal transfer would be a -> b -> c
    top = a_stack.pop()

    c_stack.append(top)

    a_stack_occurrences[top] -= 1

# Dump all that's remaining on the "b" stack onto the "c" stack. Nothing else can be done at this point
while len(b_stack) != 0:
    c_stack.append(b_stack.pop())

print ''.join(c_stack)
