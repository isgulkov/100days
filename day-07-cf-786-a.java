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

        int[] player_a_moves = readNInts(scanner.nextInt(), scanner);
        int[] player_b_moves = readNInts(scanner.nextInt(), scanner);

        GameSolver gameSolver = new GameSolver(n, player_a_moves, player_b_moves);

        for(GameSolver.Player player : new GameSolver.Player[] { GameSolver.Player.A, GameSolver.Player.B }) {
            for(int i = 1; i < n; i++) {
                GameSolver.GameOutcome outcome = gameSolver.getOutcome(i, player);

                if(outcome == player.getWinOutcome()) {
                    System.out.print("Win ");
                }
                else if(outcome == GameSolver.GameOutcome.Loop) {
                    System.out.print("Loop ");
                }
                else {
                    System.out.print("Lose ");
                }
            }

            System.out.println();
        }
    }
}

class GameSolver
{
    enum Player
    {
        A, B;

        GameOutcome getWinOutcome()
        {
            if(this == A) {
                return GameOutcome.WinA;
            }
            else {
                return GameOutcome.WinB;
            }
        }
    }

    enum GameOutcome
    {
        WinA, WinB, Loop
    }

    GameSolver(int n, int[] player_a_moves, int[] player_b_moves)
    {

    }

    GameOutcome getOutcome(int startLocation, Player startingPlayer)
    {
        return GameOutcome.WinA;
    }
}
