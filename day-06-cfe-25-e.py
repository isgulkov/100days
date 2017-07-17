from Queue import PriorityQueue

class DirectedGraph:
	def __init__(self, n):
		self._num_nodes = n
		self._adj_lists = [[] for i in xrange(n)]

	def add_edge(self, u, v):
		self._adj_lists[u].append(v)

	def get_topological_labels(self):
		reversed_adj_lists = [[] for i in xrange(self._num_nodes)]

		for u in xrange(self._num_nodes):
			for v in self._adj_lists[u]:
				reversed_adj_lists[v].append(u)

		labels = [None for i in xrange(self._num_nodes)]

		outflow_rate = [len(self._adj_lists[i]) for i in xrange(self._num_nodes)]

		zero_outflow_nodes = PriorityQueue()

		for u in filter(lambda u: outflow_rate[u] == 0, xrange(self._num_nodes)):
			zero_outflow_nodes.put((-u, u, ))

		next_label = self._num_nodes

		while not zero_outflow_nodes.empty():
			u = zero_outflow_nodes.get()[1]

			labels[u] = next_label

			next_label -= 1

			for v in reversed_adj_lists[u]:
				outflow_rate[v] -= 1

				if outflow_rate[v] == 0:
					zero_outflow_nodes.put((-v, v, ))

		return labels


num_nodes, num_edges = map(int, raw_input().split(' '))

g = DirectedGraph(num_nodes)

for i in xrange(num_edges):
	u, v = map(lambda x: int(x) - 1, raw_input().split(' '))

	g.add_edge(u, v)

for label in g.get_topological_labels():
	print label,

print
