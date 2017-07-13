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

		a = int.Parse(matches[0].Groups[0].Value);
		b = int.Parse(matches[1].Groups[0].Value);
	}

	static void ReadLine3Ints(out int a, out int b, out int c)
	{
		string line = Console.ReadLine();

		MatchCollection matches = Regex.Matches(line, @"\d+");

		a = int.Parse(matches[0].Groups[0].Value);
		b = int.Parse(matches[1].Groups[0].Value);
		c = int.Parse(matches[2].Groups[0].Value);
	}

	static IEnumerable<int> ReadLineNInts()
	{
		string line = Console.ReadLine();

		MatchCollection matches = Regex.Matches(line, @"\d+");

		foreach(Match match in matches) {

			yield return int.Parse(match.Groups[0].Value);
		}
	}

	class Graph
	{
		int NumNodes;
		List<int>[] AdjLists;

		public Graph(int num_nodes)
		{
			NumNodes = num_nodes;

			AdjLists = new List<int>[NumNodes];

			for(int i = 0; i < num_nodes; i++) {
				AdjLists[i] = new List<int>(100);
			}
		}

		public void AddEdge(int a, int b)
		{
			AdjLists[a].Add(b);
			AdjLists[b].Add(a);
		}
	}

	public static void Main(string[] args)
	{
		int n, m, k;

		ReadLine3Ints(out n, out m, out k);

		List<int> CapNodes = new List<int>();

		foreach(int x in ReadLineNInts()) {
			CapNodes.Add(x);
		}

		Graph g = new Graph(n);

		for(int i = 0; i < m; i++) {
			int a, b;

			ReadLine2Ints(out a, out b);

			g.AddEdge(a, b);
		}
	}
}
