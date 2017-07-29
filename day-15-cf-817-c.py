
def sum_digits(n):
    result = 0

    while n != 0:
        result += n % 10
        n /= 10

    return result

n, s = map(int, raw_input().split(' '))

# As all suitable numbers form interval of form [k; +inf), find the smallest
# suitable number using binary serach

left, right = 0, n + 1

while left != right:
    mid = (left + right) / 2

    if mid - sum_digits(mid) >= s:
        right = mid
    else:
        left = mid + 1

print n + 1 - left
