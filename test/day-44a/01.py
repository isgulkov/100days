from interactive_program import InteractiveProgram

from sys import argv, exit

head = 2

items = [
    (97, -2),
    (58, 4),
    (16, 1),
    (81, 0),
    (79, 3)
]

x = 80

answer = 81

p = InteractiveProgram(argv[1], display_messages=False)

p.send_line("%d %d %d" % (len(items), head + 1, x, ))

for i in xrange(2000):
    c, n = p.receive_line().split(' ')

    n = int(n)

    if c == '!':
        if n == answer:
            print "OK"
        else:
            print "NOT OK"

        exit(0)
    else:
        p.send_line("%d %d" % (items[n - 1][0], items[n - 1][1] + 1))
