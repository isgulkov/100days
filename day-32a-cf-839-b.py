from sys import exit

num_rows, num_groups = map(int, raw_input().split(' '))

groups = map(int, raw_input().split(' '))

num_quads, num_doubles = num_rows, 2 * num_rows

# Fully fill up first quads, then doubles, as many as possible

for i in xrange(num_groups):
    occupiable_quads = min(num_quads, groups[i] / 4)

    num_quads -= occupiable_quads
    groups[i] -= 4 * occupiable_quads

for i in xrange(num_groups):
    occupiable_doubles = min(num_doubles, groups[i] / 2)

    num_doubles -= occupiable_doubles
    groups[i] -= 2 * occupiable_doubles

# If there are groups of 4 and up left, problem is infeasible
# (not sure if this even possible under the assignment conditions, but doesn't hurt to check :>)

if len(filter(lambda x: x >= 4, groups)) != 0:
    print "NO"

    exit(0)

# Subproblem:
# distribute groups of 1, 2 and 3 people over leftover quads and doubles

# Distribute all groups of 3 over quads

for i in filter(lambda x: groups[x] == 3, xrange(num_groups)):
    if num_quads == 0:
        break

    groups[i] = 0
    num_quads -= 1

# If that couldn't be done, place two people of every group of 3 on a double

for i in filter(lambda x: groups[x] == 3, xrange(num_groups)):
    if num_doubles == 0:
        break

    groups[i] -= 2
    num_doubles -= 1

# If we coudn't distribute all groups of 3, the problem is infeasible

if len(filter(lambda x: x == 3, groups)) != 0:
    print "NO"

    exit(0)

# Subproblem:
# distribute groups of 1 and 2 over leftover quads and doubles

# Distribute pairs of 1 and 2 groups over quads, thus filling the quads up

for i, j in zip(
    filter(lambda i: groups[i] == 1, xrange(num_groups)),
    filter(lambda i: groups[i] == 2, xrange(num_groups))
    ):

    if num_quads == 0:
        break

    groups[i] = 0
    groups[j] = 0

    num_quads -= 1

if num_quads == 0:
    # Subproblem:
    # distribute groups of 1 and 2 over the remaining doubles

    for i in xrange(num_groups):
        if num_doubles == 0:
            break

        if groups[i] == 1 or groups[i] == 2:
            groups[i] = 0
            num_doubles -= 1
else:
    # There are quads left, but either groups of 1 or groups of 2 are gone (or both)

    if len(filter(lambda x: x == 2, groups)) != 0:
        # Subproblem:
        # distribute groups of 2 over the remaining quads and doubles

        for i in xrange(num_groups):
            if num_doubles == 0:
                break

            if groups[i] == 2:
                num_doubles -= 1
                groups[i] = 0

        # On every two quads, we can place three groups of 2:
        # [1 1 - 3]
        # [2 2 - 3]

        two_groups = filter(lambda i: groups[i] == 2, xrange(num_groups))

        for i, j, k in zip(
            two_groups[:len(two_groups) / 3],
            two_groups[len(two_groups) / 3:len(two_groups) / 3 * 2],
            two_groups[len(two_groups) / 3 * 2:]
            ):
            if num_quads < 2:
                break

            groups[i] = 0
            groups[j] = 0
            groups[k] = 0

            num_quads -= 2

        # At most two groups of 2 remain, which requires two quads, or less than two quads are available -- either way,
        # at this point we can only place one group of 2 per quad

        for i in xrange(num_groups):
            if num_quads == 0:
                break

            if groups[i] == 2:
                groups[i] = 0
                num_quads -= 1

    elif len(filter(lambda x: x == 1, groups)) != 0:
        # Subproblem:
        # distribute groups of 1 over the remaining quads and doubles

        for i in xrange(num_groups):
            if num_doubles == 0:
                break

            if groups[i] == 1:
                num_doubles -= 1
                groups[i] = 0

        one_groups = filter(lambda i: groups[i] == 1, xrange(num_groups))

        for i, j in zip(one_groups[:len(one_groups) / 2], one_groups[len(one_groups) / 2:]):
            if num_quads == 0:
                break

            groups[i] = 0
            groups[j] = 0

            num_quads -= 1

        if num_quads != 0:
            for i in xrange(num_groups):
                if groups[i] == 1:
                    groups[i] = 0
                    num_quads -= 1

                    break

# If anything has remained after the distribution, the problem is infeasible

if sum(groups) == 0:
    print "YES"
else:
    print "NO"
