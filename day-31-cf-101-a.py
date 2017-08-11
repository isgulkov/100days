
s = raw_input()

max_dropped_symbols = int(raw_input())

symbol_freq = {chr(i): 0 for i in xrange(ord('a'), ord('z'))}

for c in s:
    symbol_freq[c] += 1

print symbol_freq
