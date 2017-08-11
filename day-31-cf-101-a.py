
s = raw_input()

max_dropped_symbols = int(raw_input())

symbol_freq = {chr(i): 0 for i in xrange(ord('a'), ord('z'))}

for c in s:
    symbol_freq[c] += 1

symbol_freqs = [(symbol_freq[c], c, ) for c in symbol_freq if symbol_freq[c] != 0]

symbol_freqs.sort()

for s in symbol_freqs:
    print s
