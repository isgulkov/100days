using System;
using System.Collections.Generic;
using System.Linq;

class MainClass
{
	static int[] ReadNInts(int n)
	{
		return Array.ConvertAll(Console.ReadLine().Split(' '), x => int.Parse(x));
	}

	public static void Main(string[] args)
	{
		int n = int.Parse(Console.ReadLine());

		int[] passengerCities = ReadNInts(n);

		/**
		 * Determine the smallest intervals (borders inclusive) in which passengers of each city occur (from the first
		 * occurence of a passenger to the city to the last)
		 */
		int[] left_boundary = new int[5001];

		for(int i = passengerCities.Length - 1; i >= 0; i--) {
			left_boundary[passengerCities[i]] = i;
		}

		int[] right_boundary = new int[5001];

		for(int i = 0; i<passengerCities.Length; i++) {
			right_boundary[passengerCities[i]] = i;
		}

		/**
         * maxComfort[i] stores the answer for subproblem for indices [0; i)
		 */
		int[] maxComfort = new int[n + 1];

		for(int i = 0; i < n; i++) {
			maxComfort[i + 1] = maxComfort[i];

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

				bool validCarriage = true;

				foreach(int key in keys) {
					if(left_boundary[key] < j || i < right_boundary[key]) {
						validCarriage = false;
						break;
					}
				}

				if(!validCarriage) {
					continue;
				}

				int candidate_max = maxComfort[j] + subarrayComfort;

				if(candidate_max > maxComfort[i + 1]) {
					maxComfort[i + 1] = candidate_max;
				}
			}
		}

		Console.WriteLine(maxComfort[n]);
	}
}
