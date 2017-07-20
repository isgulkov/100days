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

		List<int> passengerCities = ReadNInts(n);

		/**
		 * Determine the smallest intervals (borders inclusive) in which passengers of each city lay (from the first
		 * occurence of a passenger to the city to the last)
		 *
		 * By formulation, if a passenger from a city is included, all passengers from this city should be included and
		 * in the same non-overlapping inter, thus including a city means including at least its corresponding
		 * interval
		 */
		Dictionary<int, Tuple<int, int>> cityIntervals = GetOccurenceIntervals(passengerCities);

		foreach(int k in cityIntervals.Keys) {
			Console.WriteLine($"{k}: {cityIntervals[k]}");
		}
	}

	/// <summary>
	/// Returns a dictionary that for each unique value in <paramref name="values"/> contains the pair of the index of
	/// its first occurence in the list and its last occurence (its occurence interval)
	/// </summary>
	/// <returns>Dictionary of values' occurence interval boundaries</returns>
	/// <param name="values">Values for which the occurence intervals are to be determined.</param>
	static Dictionary<int, Tuple<int, int>> GetOccurenceIntervals(List<int> values)
	{
		Dictionary<int, Tuple<int, int>> occurenceIntervals = new Dictionary<int, Tuple<int, int>>();

		for(int i = 0; i < values.Count; i++) {
			int city = values[i];

			if(!occurenceIntervals.ContainsKey(city)) {
				/**
				 * If a new value is encountered, start a new occurence interval for this value at the current index
				 */
				occurenceIntervals[city] = new Tuple<int, int>(i, i);
			}
			else {
				/**
				 * If a known value is encountered, expand the boundaries of its occurence interval up to the current
				 * point
				 */
				Tuple<int, int> oldBoundaries = occurenceIntervals[city];

				occurenceIntervals[city] = new Tuple<int, int>(oldBoundaries.Item1, i);
			}
		}

		return occurenceIntervals;
	}
}
