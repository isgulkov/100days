using System;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.Linq;

class MainClass
{
	static void ReadLine2Ints(out int a, out int b)
	{
		string line = Console.ReadLine();

		MatchCollection matches = Regex.Matches(line, @"\d+");

		a = int.Parse(matches[0].Value);
		b = int.Parse(matches[1].Value);
	}

	static void ReadLine3Ints(out int a, out int b, out int c)
	{
		string line = Console.ReadLine();

		MatchCollection matches = Regex.Matches(line, @"\d+");

		a = int.Parse(matches[0].Value);
		b = int.Parse(matches[1].Value);
		c = int.Parse(matches[2].Value);
	}

	static IEnumerable<int> ReadLineNInts()
	{
		string line = Console.ReadLine();

		MatchCollection matches = Regex.Matches(line, @"\d+");

		foreach(Match match in matches) {
			yield return int.Parse(match.Value);
		}
	}

	class Graph
	{
		int NumNodes;
		List<int>[] AdjLists;

		int[] NodeComponent;
		int NumComponents = 0;

		public Graph(int num_nodes)
		{
			NumNodes = num_nodes;

			AdjLists = new List<int>[NumNodes];

			for(int i = 0; i < num_nodes; i++) {
				AdjLists[i] = new List<int>(100);
			}

			NodeComponent = new int[NumNodes];
		}

		public void AddEdge(int a, int b)
		{
			AdjLists[a].Add(b);
			AdjLists[b].Add(a);
		}

		public int FindComponentSize(int u)
		{
			int componentNumber = ++NumComponents;

			return FindComponent(u, componentNumber);
		}

		public int GetNumEdgesInComponent(int u)
		{
			int result = 0;

			int componentNumber = NodeComponent[u];

			for(int i = 0; i < NumNodes; i++) {
				if(NodeComponent[i] != componentNumber) {
					continue;
				}

				result += AdjLists[i].Count;
			}

			result /= 2;

			return result;
		}

		int FindComponent(int u, int componentNumber)
		{
			NodeComponent[u] = componentNumber;

			int subtreeSize = 1;

			foreach(int v in AdjLists[u]) {
				if(NodeComponent[v] != 0) {
					continue;
				}

				subtreeSize += FindComponent(v, componentNumber);
			}

			return subtreeSize;
		}
	}

	public static void Main(string[] args)
	{
		int n, m, k;

		ReadLine3Ints(out n, out m, out k);

		List<int> capNodes = new List<int>();

		foreach(int x in ReadLineNInts()) {
			capNodes.Add(x - 1);
		}

		Graph g = new Graph(n);

		for(int i = 0; i < m; i++) {
			int a, b;

			ReadLine2Ints(out a, out b);

			g.AddEdge(a - 1, b - 1);
		}

		int result = 0;

		foreach(int capNode in capNodes) {
			int componentSize = g.FindComponentSize(capNode);

			/*
			 * Find the number of possible new edges inside the component: subtract the number of edges in the component
			 * from the number of edges in a fully connected graph of size `componentSize`
			 */
			result += componentSize * (componentSize - 1) / 2 - g.GetNumEdgesInComponent(capNode);
		}

		Console.WriteLine(result);
	}
}
