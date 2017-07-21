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

		for(int i = 0; i < n; i++) {
			right_boundary[passengerCities[i]] = i;
		}

		int[,] carriageComfort = new int[passengerCities.Length, passengerCities.Length];

		for(int i = 0; i < n; i++) {
			if(left_boundary[passengerCities[i]] < i) {
				continue;
			}

			HashSet<int> keys = new HashSet<int>();
			int currentComfort = 0;

			for(int j = i; j < n; j++) {
				int rightKey = passengerCities[j];

				if(j < right_boundary[rightKey]) {
					continue;
				}

				if(!keys.Contains(rightKey)) {
					keys.Add(rightKey);
					currentComfort ^= rightKey;
				}

				carriageComfort[i, j] = currentComfort;
			}
		}

		/**
         * maxComfort[i] stores the answer for subproblem for indices [0; i)
		 */
		int[] maxComfort = new int[n + 1];

		for(int i = 0; i < n; i++) {
			maxComfort[i + 1] = maxComfort[i];

			for(int j = i; j >= 0; j--) {
				int candidateMax = maxComfort[j] + carriageComfort[j, i];

				if(candidateMax > maxComfort[i + 1]) {
					maxComfort[i + 1] = candidateMax;
				}
			}
		}

		Console.WriteLine(maxComfort[n]);
	}
}
