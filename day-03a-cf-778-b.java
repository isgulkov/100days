import java.util.*;
import java.util.function.BinaryOperator;
import java.util.regex.*;

/**
 * Represents a bitwise function of Petya's answer
 */
class UnaryBitwiseFunction
{
    private int nBits;

    /**
     * Stores the value of ith bit of the variable if corresponding bit in Petya's answer is set
     */
    private boolean[] set;

    /**
     * Stores the value of ith bit of the variable if corresponding bit in Petya's answer is unset
     */
    private boolean[] unset;

    private UnaryBitwiseFunction(int nBits, boolean[] set, boolean[] unset)
    {
        this.nBits = nBits;
        this.set = set;
        this.unset = unset;
    }

    /**
     * @param s String of '1's and '0's
     * @return Corresponding constant function
     */
    static UnaryBitwiseFunction fromConstant(String s)
    {
        int nBits = s.length();

        boolean[] set = new boolean[nBits];
        boolean[] unset = new boolean[nBits];

        for(int i = 0; i < s.length(); i++) {
            set[i] = s.charAt(i) == '1';
            unset[i] = s.charAt(i) == '1';
        }

        return new UnaryBitwiseFunction(nBits, set, unset);
    }

    /**
     * @param nBits ★★☆☆☆
     * @return Identity function with the specified number of bits
     */
    static UnaryBitwiseFunction identity(int nBits)
    {
        boolean[] set = new boolean[nBits];
        boolean[] unset = new boolean[nBits];

        for(int i = 0; i < nBits; i++) {
            set[i] = true;
            unset[i] = false;
        }

        return new UnaryBitwiseFunction(nBits, set, unset);
    }

    private UnaryBitwiseFunction applyOperation(UnaryBitwiseFunction other, BinaryOperator<Boolean> op)
    {
        boolean[] set = new boolean[nBits];
        boolean[] unset = new boolean[nBits];

        for(int i = 0; i < nBits; i++) {
            set[i] = op.apply(this.set[i], other.set[i]);
            unset[i] = op.apply(this.unset[i], other.unset[i]);
        }

        return new UnaryBitwiseFunction(nBits, set, unset);
    }

    /**
     * @param other Another function
     * @return The result of bitwise "and" operation applied to the two functions
     */
    UnaryBitwiseFunction and(UnaryBitwiseFunction other)
    {
        return applyOperation(other, (x, y) -> x && y);
    }

    /**
     * @param other Another function
     * @return The result of bitwise "or" operation applied to the two functions
     */
    UnaryBitwiseFunction or(UnaryBitwiseFunction other)
    {
        return applyOperation(other, (x, y) -> x || y);
    }

    /**
     * @param other Another function
     * @return The result of bitwise "xor" operation applied to the two functions
     */
    UnaryBitwiseFunction xor(UnaryBitwiseFunction other)
    {
        return applyOperation(other, (x, y) -> x != y);
    }
}

class VariableSystem
{
    private static Pattern stmtPattern = Pattern.compile("([a-z]+) := (.+$)");
    private static Pattern exprPattern = Pattern.compile("(\\?|[a-z]+|[01]+) (AND|OR|XOR) (\\?|[a-z]+|[01]+)");

    private HashMap<String, UnaryBitwiseFunction> bitwiseFunctions = new HashMap<>();

    private int nBits;

    VariableSystem(int nBits)
    {
        this.nBits = nBits;
    }

    private UnaryBitwiseFunction parsePrimaryExpression(String primaryExpr)
    {
        if(primaryExpr.equals("?")) {
            return UnaryBitwiseFunction.identity(nBits);
        }
        else if(primaryExpr.matches("^[01]+$")) {
            return UnaryBitwiseFunction.fromConstant(primaryExpr);
        }
        else {
            return bitwiseFunctions.get(primaryExpr);
        }
    }

    private UnaryBitwiseFunction parseExpression(String expr)
    {
        Matcher m = exprPattern.matcher(expr);

        if(m.find()) {
            UnaryBitwiseFunction a = parsePrimaryExpression(m.group(1));
            UnaryBitwiseFunction b = parsePrimaryExpression(m.group(3));

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
        Matcher m = stmtPattern.matcher(stmt);

        if(!m.find()) {
            throw new IllegalArgumentException();
        }

        String varName = m.group(1);
        String expressionString = m.group(2);

        bitwiseFunctions.put(varName, parseExpression(expressionString));
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

        VariableSystem vs = new VariableSystem(m);

        for(int i = 0; i < n; i++) {
            vs.addStatement(stdin.nextLine());
        }
    }
}
