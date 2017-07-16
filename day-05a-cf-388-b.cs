using System;
using System.Text;

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

		Console.WriteLine(n);

		Console.WriteLine(g);
	}
}
