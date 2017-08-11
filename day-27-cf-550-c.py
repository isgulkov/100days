
# Returns number divisible by 8 consisting of three decimal digits that are a subsequence of `s`
def get_sub3_div8_number(s):
    for i in xrange(len(s) - 2):
        for j in xrange(i + 1, len(s) - 1):
            for k in xrange(j + 1, len(s)):
                x = int(s[i] + s[j] + s[k])

                if x % 8 == 0:
                    return x

    return None

# Returns number divisible by 8 consisting of two decimal digits that are a subsequence of `s`
def get_sub2_div8_number(s):
    for i in xrange(len(s) - 1):
        for j in xrange(i + 1, len(s)):
            x = int(s[i] + s[j])

            if x % 8 == 0:
                return x

    return None

s = raw_input()

# If there isn't a subsequence of `s` that is divisible by 8, there's no any longer such subsequence, as for any number
# [abc] divisible by 8 the number 1000x + [abc] is also divisible by 8
x = get_sub3_div8_number(s)

y = get_sub2_div8_number(s)

if x is not None:
    print "YES"
    print x
elif y is not None:
    print "YES"
    print y
elif '8' in s:
    print "YES"
    print 8
elif '0' in s:
    print "YES"
    print 0
else:
    print "NO"
