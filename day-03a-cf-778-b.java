import java.util.IllegalFormatException;
import java.util.Scanner;
import java.util.regex.*;

class Day03a
{
    private static Scanner stdin = new Scanner(System.in);

    private static int[] read2Ints()
    {
        Pattern p = Pattern.compile("(\\d+) (\\d+)");
        Matcher matcher = p.matcher(stdin.nextLine());

        if(!matcher.find()) {
            throw new IllegalArgumentException();
        }

        int a = Integer.parseInt(matcher.group(1));
        int b = Integer.parseInt(matcher.group(2));

        return new int[] { a, b };
    }

    public static void main(String[] args)
    {
        int n, m;

        {
            int[] ab = read2Ints();
            n = ab[0];
            m = ab[1];
        }

        System.out.println(n);
        System.out.println(m);
    }
}
