using System;
using System.Collections.Generic;
using System.Linq;

class MainClass
{
	static List<int> ReadNInts(int n)
	{
		return Console.ReadLine().Split(' ').Select(x => int.Parse(x)).Take(n).ToList();
	}

	public static void Main(string[] args)
	{
		int n = int.Parse(Console.ReadLine());

		List<int> passengers = ReadNInts(n);

		foreach(int p in passengers) {
			Console.WriteLine(p);
		}
	}
}
