
s = raw_input()

max_dropped_chars = int(raw_input())

symbol_freq = {chr(i): 0 for i in xrange(ord('a'), ord('z') + 1)}

for c in s:
    symbol_freq[c] += 1

symbol_freqs = [(symbol_freq[c], c, ) for c in symbol_freq if symbol_freq[c] != 0]

symbol_freqs.sort()

# Drop as many charactes as we're allowed to, starting with the least frequest symbols

num_dropped_chars = 0
dropped_symbols = set()

for freq, c in symbol_freqs:
    if num_dropped_chars + freq > max_dropped_chars:
        break

    num_dropped_chars += freq
    dropped_symbols.add(c)

print len(symbol_freqs) - len(dropped_symbols)

print ''.join([c for c in s if c not in dropped_symbols])
