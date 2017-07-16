using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;

class MainClass
{
	class Graph
	{
		int N;

		bool[,] AdjMatrix;

		public Graph(int n)
		{
			N = n;

			AdjMatrix = new bool[n, n];
		}

		public void AddEdge(int u, int v)
		{
			if(u == v) {
				throw new ArgumentException("yobu dal?");
			}

			AdjMatrix[u, v] = AdjMatrix[v, u] = true;
		}

		public override string ToString()
		{
			StringBuilder b = new StringBuilder();

			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					b.Append(AdjMatrix[i, j] ? 'Y' : 'N');
				}

				b.Append('\n');
			}

			return b.ToString();
		}
	}

	public static void Main(string[] args)
	{
		int k = int.Parse(Console.ReadLine());

		const int n =
			2 // nodes 0 and 1
			+ 10 * 7 // decimal node layers
			+ 7 + 6 + 5 + 4 + 3 + 2 + 1; // chains from layers to node 1

		Graph g = new Graph(n);

		List<int> freeNodes = Enumerable.Range(2, n - 2).ToList();

		List<List<int>> layers = new List<List<int>>();

		/**
		 * Create 7 layers of 10 nodes each, where for each i in [0; 6] there are 10^i paths between node 0 and each
		 * node in ith layer
		 */

		/**
		 * Assign nodes to layers
		 */
		for(int i = 0; i < 7; i++) {
			List<int> newLayer = new List<int>();

			for(int j = 0; j < 10; j++) {
				newLayer.Add(freeNodes[0]);
				freeNodes.RemoveAt(0);
			}

			layers.Add(newLayer);
		}

		/**
		 * Connect node 0 to the first layer
		 */
		foreach(int nodeId in layers[0]) {
			g.AddEdge(0, nodeId);
		}

		/**
		 * Fully interconnect each layer with the previous one
		 */
		for(int i = 1; i < 7; i++) {
			foreach(int nodePreviousLayer in layers[i - 1]) {
				foreach(int nodeThisLayer in layers[i]) {
					g.AddEdge(nodePreviousLayer, nodeThisLayer);
				}
			}
		}

		/**
		 * Create chains of appropriate length for connecting each layer to node 1. This is needed so that paths from
		 * nodes of each layer to node 1 are equally long
		 */
		List<int> chainEnds = new List<int>();

		for(int i = 0; i < 7; i++) {
			List<int> chain = new List<int>();

			for(int j = 0; j < 6 - i; j++) {
				chain.Add(freeNodes[0]);
				freeNodes.RemoveAt(0);
			}

			/**
			 * At the other end of each chain there's node 1
			 */
			chain.Add(1);

			/**
			 * Connect the chain
			 */
			for(int j = 1; j < chain.Count; j++) {
				g.AddEdge(chain[j - 1], chain[j]);
			}

			chainEnds.Add(chain[0]);
		}

		/**
		 * Connect the appropriate number of nodes of each layer to node 1 through their appropriate chains
		 */
		for(int currentLayer = 0; k != 0; k /= 10, currentLayer++) {
			int currentDecimalPlace = k % 10;

			for(int i = 0; i < currentDecimalPlace; i++) {
				g.AddEdge(layers[currentLayer][i], chainEnds[currentLayer]);
			}
		}

		Console.WriteLine(n);

		Console.WriteLine(g);
	}
}
