
n, w = map(int, raw_input().split(' '))

volumes = map(int, raw_input().split(' '))
volumes = [(volumes[i], i, ) for i in xrange(n)]

volumes.sort()

print volumes
