
def sum_digits(n):
    result = 0

    while n != 0:
        result += n % 10
        n /= 10

    return result

n, s = map(int, raw_input().split(' '))

result = 0

for i in xrange(1, n + 1):
    if i - sum_digits(i) >= s:
        result += 1

print result
