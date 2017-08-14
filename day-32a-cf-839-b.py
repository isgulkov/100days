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

# If there are groups of 4 and up left, seating is infeasible
# (not sure if this even possible, but doesn't hurt to check :>)

if len(filter(lambda x: x >= 4, groups)) != 0:
    print "NO"

    exit(0)

# Subproblem:
# distribute groups of 0, 1, 2 and 3 people over lefover quads and doubles


