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

	public static void Main(string[] args)
	{
		int n, m, k;

		ReadLine3Ints(out n, out m, out k);

		Console.WriteLine($" {n} {m} {k}");

		foreach(int x in ReadLineNInts()) {
			Console.Write($" {x} ");
		}

		Console.WriteLine();

		for(int i = 0; i < m; i++) {
			int a, b;

			ReadLine2Ints(out a, out b);

			Console.WriteLine($" {a} {b}");
		}
	}
}
