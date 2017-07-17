import heapq
from bisect import bisect_left


class DirectedGraph:
    def __init__(self, n):
        self._num_nodes = n
        self._outdegree = [0 for i in xrange(n)]
        self._reversed_adj_lists = [[] for i in xrange(n)]

    def add_edge(self, u, v):
        self._outdegree[u] += 1
        self._reversed_adj_lists[v].append(u)

    def get_topological_labels(self):
        labels = [None for i in xrange(self._num_nodes)]

        zero_outdegree_nodes = [u for u in xrange(self._num_nodes) if self._outdegree[u] == 0]

        next_label = self._num_nodes

        # On each iteration, select a node with zero outdegree with the highest index (the latter is done to ensure
        # lexicographically minimal label permutation)
        while len(zero_outdegree_nodes) != 0:
            u = zero_outdegree_nodes.pop()

            labels[u] = next_label

            next_label -= 1

            for v in self._reversed_adj_lists[u]:
                self._outdegree[v] -= 1

                # If the node is a new zero-outdegree node, insert it into the array maintaining the sorted order. In
                # practice this `bisect_left`/`insert()` solution works faster than both `Queue.PriorityQueue` and
                # `heapq`
                if self._outdegree[v] == 0:
                    insertion_point = bisect_left(zero_outdegree_nodes, v)

                    zero_outdegree_nodes.insert(insertion_point, v)

        return labels


num_nodes, num_edges = map(int, raw_input().split(' '))

g = DirectedGraph(num_nodes)

for i in xrange(num_edges):
    u, v = map(lambda x: int(x) - 1, raw_input().split(' '))

    g.add_edge(u, v)

for label in g.get_topological_labels():
    print label,

print
