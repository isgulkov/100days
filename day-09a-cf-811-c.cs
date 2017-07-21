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
		 * Determine the smallest intervals (borders inclusive) in which passengers of each city occur (from the first
		 * occurence of a passenger to the city to the last)
		 */
		Dictionary<int, Tuple<int, int>> cityIntervals = GetOccurenceIntervals(passengerCities);

		CarriageValidityChecker checker = new CarriageValidityChecker(passengerCities, cityIntervals);

		/**
         * maxComfort[i] stores the answer for subproblem for indices [0; i)
		 */
		int[] maxComfort = Enumerable.Repeat(0, n + 1).ToArray();

		for(int i = 0; i < n; i++) {
			HashSet<int> keys = new HashSet<int>();
			int subarrayComfort = 0;

			for(int j = i; j >= 0; j--) {
				/**
				 * If [j; i] is a valid carriage, try to update the answer for [0; i] with existing sum of best set of
				 * carriages on [0; j) with it extended by the [j; i] carriage
				 */

				if(!keys.Contains(passengerCities[j])) {
					subarrayComfort ^= passengerCities[j];

					keys.Add(passengerCities[j]);
				}

				if(checker.IsValidCarriage(j, i, keys)) {
					int candidate_max = maxComfort[j] + subarrayComfort;

					if(candidate_max > maxComfort[i + 1]) {
						maxComfort[i + 1] = candidate_max;
					}
				}
			}

			/**
			 * If the best answer without using the `i`th passenger is better than with it, use the the former instead
			 */
			if(maxComfort[i + 1] < maxComfort[i]) {
				maxComfort[i + 1] = maxComfort[i];
			}
		}

		Console.WriteLine(maxComfort[n]);
	}

	class CarriageValidityChecker
	{
		List<int> Passengers;
		Dictionary<int, Tuple<int, int>> Intervals;

		public CarriageValidityChecker(List<int> passengers, Dictionary<int, Tuple<int, int>> intervals)
		{
			Passengers = passengers;
			Intervals = intervals;
		}

		/// <returns><c>true</c>, if all occurences of every key that occurs in [start; end] are contained in that
		/// interval, <c>false</c> otherwise</returns>
		/// <param name="start">Start</param>
		/// <param name="end">End</param>
		/// <param name="keys">Set of keys contained in [start; end]</param>
		public bool IsValidCarriage(int start, int end, HashSet<int> keys)
		{
			foreach(int key in keys) {
				Tuple<int, int> interval = Intervals[key];

				if(interval.Item1 < start || interval.Item2 > end) {
					return false;
				}
			}

			return true;
		}
	}

	/// <summary>
	/// Returns a dictionary that for each unique value in <paramref name="values"/> contains the pair of the index of
	/// its first occurence in the list and its last occurence (its occurence interval)
	///
	/// Complexity: O(n)
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
