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

		Dictionary<int, Tuple<int, int>> cityIntervals = DetermineCityIntervals(passengerCities);

		foreach(int k in cityIntervals.Keys) {
			Console.WriteLine($"{k}: {cityIntervals[k]}");
		}
	}

	static Dictionary<int, Tuple<int, int>> DetermineCityIntervals(List<int> passengerCities)
	{
		/**
		 * Determine the smallest intervals (borders inclusive) in which passengers of each city lay (from the first
		 * occurence of a passenger to the city to the last)
		 *
		 * By formulation, if a passenger from a city is included, all passengers from this city should be included and
		 * in the same non-overlapping interval, thus including a city means including at least its corresponding
		 * interval
		 */
		Dictionary<int, Tuple<int, int>> cityIntervals = new Dictionary<int, Tuple<int, int>>();

		for(int i = 0; i < passengerCities.Count; i++) {
			int city = passengerCities[i];

			if(!cityIntervals.ContainsKey(city)) {
				/**
				 * If a passenger to a new city is encountered, start a new interval of this city at the current point
				 */
				cityIntervals[city] = new Tuple<int, int>(i, i);
			}
			else {
				/**
				 * If a passenger to a known city is encountered, expand the boundaries of that city's interval up to
				 * the current point
				 */
				Tuple<int, int> oldBoundaries = cityIntervals[city];

				cityIntervals[city] = new Tuple<int, int>(oldBoundaries.Item1, i);
			}
		}

		return cityIntervals;
	}
}
