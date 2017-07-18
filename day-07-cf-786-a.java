import java.util.Scanner;

class Day07
{
    private static int[] readNInts(int n, Scanner scanner)
    {
        int[] result = new int[n];

        for(int i = 0; i < n; i++) {
            result[i] = scanner.nextInt();
        }

        return result;
    }

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();

        int[] xs_player_a = readNInts(scanner.nextInt(), scanner);
        int[] xs_player_b = readNInts(scanner.nextInt(), scanner);

        System.out.println(n);

        for(int x : xs_player_a) {
            System.out.printf("%d ", x);
        }

        System.out.println();

        for(int x : xs_player_b) {
            System.out.printf("%d ", x);
        }

        System.out.println();
    }
}
