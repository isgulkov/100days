import heapq


class DirectedGraph:
    def __init__(self, n):
        self._num_nodes = n
        self._adj_lists = [[] for i in xrange(n)]
        self._reversed_adj_lists = [[] for i in xrange(n)]

    def add_edge(self, u, v):
        self._adj_lists[u].append(v)
        self._reversed_adj_lists[v].append(u)

    def get_topological_labels(self):
        labels = [None for i in xrange(self._num_nodes)]

        outflow_rate = [len(self._adj_lists[u]) for u in xrange(self._num_nodes)]

        zero_outflow_nodes = [-u for u in xrange(self._num_nodes) if outflow_rate[u] == 0]

        heapq.heapify(zero_outflow_nodes)

        next_label = self._num_nodes

        while len(zero_outflow_nodes) != 0:
            u = -heapq.heappop(zero_outflow_nodes)

            labels[u] = next_label

            next_label -= 1

            for v in self._reversed_adj_lists[u]:
                outflow_rate[v] -= 1

                if outflow_rate[v] == 0:
                    heapq.heappush(zero_outflow_nodes, -v)

        return labels


num_nodes, num_edges = map(int, raw_input().split(' '))

g = DirectedGraph(num_nodes)

for i in xrange(num_edges):
    u, v = map(lambda x: int(x) - 1, raw_input().split(' '))

    g.add_edge(u, v)

for label in g.get_topological_labels():
    print label,

print
