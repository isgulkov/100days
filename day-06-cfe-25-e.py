
class DirectedGraph:
	def __init__(self, n):
		self._num_nodes = n
		self._adj_lists = [[] for i in xrange(n)]

	def add_edge(self, u, v):
		self._adj_lists[u].append(v)

num_nodes, num_edges = map(int, raw_input().split(' '))

g = DirectedGraph(num_nodes)

for i in xrange(num_edges):
	u, v = map(lambda x: int(x) - 1, raw_input().split(' '))

	g.add_edge(u, v)

print g._adj_lists
