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

# Distribute all groups of 3 first over quads, then over doubles (because a quad is less useful than two doubles)

for i in filter(lambda x: groups[x] == 3, xrange(num_groups)):
    if quads == 0:
        break

    groups[i] = 0
    quads -= 1

for i in filter(lambda x: groups[x] == 3, xrange(num_groups)):
    if doubles == 0:
        break

    groups[i] = 0
    doubles -= 2

# If we coudn't distribute all groups of 3, the problem is infeasible

if len(filter(lambda x: x == 3, groups)) != 0:
    print "NO"

    exit(0)

# Subproblem:
# distribute groups of 1 and 2 over leftover quads and doubles

# Distribute pairs of 1 and 2 groups over quads, thus filling the quads up

for i, j in zip(
    filter(lambda x: groups[x] == 1, xrange(num_groups)),
    filter(lambda x: groups[x] == 2, xrange(num_groups))
    ):

    if quads == 0:
        break

    groups[i] = 0
    groups[j] = 0

