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
		int[] leftBoundary = new int[5001];

		for(int i = passengerCities.Length - 1; i >= 0; i--) {
			leftBoundary[passengerCities[i]] = i;
		}

		int[] rightBoundary = new int[5001];

		for(int i = 0; i < passengerCities.Length; i++) {
			rightBoundary[passengerCities[i]] = i;
		}

		/**
         * maxComfort[i] stores the answer for subproblem for indices [0; i)
		 */
		int[] maxComfort = new int[n + 1];

		for(int i = 0; i < n; i++) {
			maxComfort[i + 1] = maxComfort[i];

			HashSet<int> subarrayCities = new HashSet<int>();

			int minLeft = int.MaxValue, maxRight = int.MinValue;
			int subarrayComfort = 0;

			for(int j = i; j >= 0; j--) {
				/**
				 * If [j; i] is a valid carriage, try to update the answer for [0; i] with existing sum of best set of
				 * carriages on [0; j) with it extended by the [j; i] carriage
				 */
				int currentCity = passengerCities[j];

				if(!subarrayCities.Contains(currentCity)) {
					subarrayCities.Add(currentCity);
					subarrayComfort ^= currentCity;

					/**
					 * Extend the boundaries the current subarray must contain to be a valid carriage
					 */
					if(leftBoundary[currentCity] < minLeft) {
						minLeft = leftBoundary[currentCity];
					}

					if(rightBoundary[currentCity] > maxRight) {
						maxRight = rightBoundary[currentCity];
					}
				}

				if(minLeft < j || i < maxRight) {
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
