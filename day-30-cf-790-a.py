
# Injective function from non-negative integers to capitalized 10-character alphabetical strings
def get_name(x):
    cs = map(ord, 'Aaaaaaaaaa')

    i = 1

    while x != 0:
        cs[-i] += x % 26

        i += 1
        x /= 26

    return ''.join(map(chr, cs))

n, k = map(int, raw_input().split(' '))

effective = [w == "YES" for w in raw_input().split(' ')]

names = range(k - 1)

for i in xrange(n - k + 1):
    if effective[i]:
        # Generate a new name if the current squad must be effective
        names.append(k + i)
    else:
        # Use an old name otherwise
        names.append(names[i])

print ' '.join(map(get_name, names))
