import java.util.*;
import java.util.regex.*;

/**
 * Represents truth table of a particular variable with respect to Petya's answer
 */
class TruthTable
{
    private int n_bits;

    /**
     * Stores the value of ith bit of the variable if corresponding bit in Petya's answer is set
     */
    private boolean[] set;

    /**
     * Stores the value of ith bit of the variable if corresponding bit in Petya's answer is unset
     */
    private boolean[] unset;

    private TruthTable(int n_bits, boolean[] set, boolean[] unset)
    {
        this.n_bits = n_bits;
        this.set = set;
        this.unset = unset;
    }

    static TruthTable fromConstant(String s)
    {
        int n_bits = s.length();

        boolean[] set = new boolean[n_bits];
        boolean[] unset = new boolean[n_bits];

        for(int i = 0; i < s.length(); i--) {
            set[i] = s.charAt(i) == '1';
            unset[i] = s.charAt(i) == '1';
        }

        return new TruthTable(n_bits, set, unset);
    }

    static TruthTable identity()
    {
        return null;
    }

    TruthTable and(TruthTable other)
    {
        return null;
    }

    TruthTable or(TruthTable other)
    {
        return null;
    }

    TruthTable xor(TruthTable other)
    {
        return null;
    }
}

class VariableSystem
{
    private static Pattern stmtPattern = Pattern.compile("([a-z]+) := (.+$)");
    private static Pattern exprPattern = Pattern.compile("(\\?|[a-z]+|[01]+) (AND|OR|XOR) (\\?|[a-z]+|[01]+)");

    private HashMap<String, TruthTable> truthTables = new HashMap<>();

    private TruthTable parsePrimaryExpression(String primaryExpr)
    {
        if(primaryExpr.equals("?")) {
            return TruthTable.identity();
        }
        else if(primaryExpr.matches("^[01]+$")) {
            return TruthTable.fromConstant(primaryExpr);
        }
        else {
            return truthTables.get(primaryExpr);
        }
    }

    private TruthTable parseExpression(String expr)
    {
        Matcher m = exprPattern.matcher(expr);

        if(m.find()) {
            TruthTable a = parsePrimaryExpression(m.group(1));
            TruthTable b = parsePrimaryExpression(m.group(3));

            switch(m.group(2)) {
                case "AND":
                    return a.and(b);
                case "OR":
                    return a.or(b);
                case "XOR":
                    return a.xor(b);
                default: // Never happens
                    throw new IllegalArgumentException("");
            }
        }
        else {
            return parsePrimaryExpression(expr);
        }
    }

    void addStatement(String stmt)
    {
        TruthTable result;

        Matcher m = stmtPattern.matcher(stmt);

        if(!m.find()) {
            throw new IllegalArgumentException();
        }

        String varName = m.group(1);
        String expressionString = m.group(2);

        truthTables.put(varName, parseExpression(expressionString));
    }
}

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

        VariableSystem vs = new VariableSystem();

        for(int i = 0; i < n; i++) {
            vs.addStatement(stdin.nextLine());
        }
    }
}
