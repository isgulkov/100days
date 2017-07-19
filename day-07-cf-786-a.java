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

        int[] movesPlayerA = readNInts(scanner.nextInt(), scanner);
        int[] movesPlayerB = readNInts(scanner.nextInt(), scanner);

        GameSolver gameSolver = new GameSolver(n, movesPlayerA, movesPlayerB);

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

    private int n;

    private GameOutcome[] cachedOutcomesA;
    private GameOutcome[] cachedOutcomesB;

    private int[] nonLosingOutcomesA;
    private int[] nonLosingOutcomesB;

    private int[] movesPlayerA;
    private int[] movesPlayerB;

    GameSolver(int n, int[] movesPlayerA, int[] movesPlayerB)
    {
        this.n = n;

        this.movesPlayerA = movesPlayerA;
        this.movesPlayerB = movesPlayerB;

        cachedOutcomesA = new GameOutcome[n];
        cachedOutcomesB = new GameOutcome[n];

        /*
         * If one player ends up in a situation where monster position is zero, the other player has won on the previous
         * turn
         */
        cachedOutcomesA[0] = GameOutcome.WinB;
        cachedOutcomesB[0] = GameOutcome.WinA;

        for(int i = 1; i < n; i++) {
            cachedOutcomesA[i] = GameOutcome.Loop;
            cachedOutcomesB[i] = GameOutcome.Loop;
        }

        for(int i = 0; i < n; i++) {
            nonLosingOutcomesA[i] = this.movesPlayerA.length;
            nonLosingOutcomesB[i] = this.movesPlayerB.length;
        }
    }

    GameOutcome getOutcome(int startLocation, Player startingPlayer)
    {
        return GameOutcome.WinA;
    }

    private GameOutcome getCachedOutcome(int position, Player player)
    {
        if(player == Player.A) {
            return cachedOutcomesA[position];
        }
        else {
            return cachedOutcomesB[position];
        }
    }

    private void setCachedOutcome(int position, Player player, GameOutcome outcome)
    {
        if(player == Player.A) {
            cachedOutcomesA[position] = outcome;
        }
        else {
            cachedOutcomesB[position] = outcome;
        }
    }

    private void decrementNonLosingOutcomes(int position, Player player)
    {
        if(player == Player.A) {
            nonLosingOutcomesA[position] -= 1;
        }
        else {
            nonLosingOutcomesB[position] -= 1;
        }
    }

    private boolean noNonLosingOutcomes(int position, Player player)
    {
        if(player == Player.A) {
            return nonLosingOutcomesA[position] == 0;
        }
        else {
            return nonLosingOutcomesB[position] == 0;
        }
    }

    private int[] getPlayerMoves(Player player)
    {
        if(player == Player.A) {
            return movesPlayerA;
        }
        else {
            return movesPlayerB;
        }
    }
}
