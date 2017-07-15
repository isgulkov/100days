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
     * Stores values of bits of the function if the corresponding bit in Petya's answer is set
     */
    private boolean[] set;

    /**
     * Stores values of bits of the function if the corresponding bit in Petya's answer is unset
     */
    private boolean[] unset;

    private UnaryBitwiseFunction(int nBits, boolean[] set, boolean[] unset)
    {
        this.nBits = nBits;
        this.set = set;
        this.unset = unset;
    }

    /**
     * @param i Bit position (MSB-based)
     * @return Value of the ith bit if the corresponding bit of the argument is set
     */
    boolean set(int i)
    {
        return set[i];
    }

    /**
     * @param i Bit position (MSB-based)
     * @return Value of the ith bit if the corresponding bit of the argument is unset
     */
    boolean unset(int i)
    {
        return unset[i];
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

    @Override
    public String toString()
    {
        String result = "";

        for(boolean b : unset) {
            result += b ? "1" : "0";
        }

        result += "/";

        for(boolean b : set) {
            result += b ? "1" : "0";
        }

        return result;
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

    @Override
    public String toString()
    {
        String result = "";

        for(String var : bitwiseFunctions.keySet()) {
            result += var + bitwiseFunctions.get(var).toString() + "\n";
        }

        return result;
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

    /**
     * @return Values of arguments that give correspondingly the minimum and the maximum value of the sum of all
     * functions
     */
    MinMax getMinMaxArguments()
    {
        StringBuilder min = new StringBuilder(),
                max = new StringBuilder();

        for(int i = 0; i < nBits; i++) {
            int onesIfSet = 0, onesIfUnset = 0;

            for(UnaryBitwiseFunction function : bitwiseFunctions.values()) {
                if(function.set(i)) {
                    onesIfSet += 1;
                }

                if(function.unset(i)) {
                    onesIfUnset += 1;
                }
            }

            if(onesIfSet > onesIfUnset) {
                max.append("1");
                min.append("0");
            }
            else if(onesIfSet < onesIfUnset) {
                max.append("0");
                min.append("1");
            }
            else {
                max.append("0");
                min.append("0");
            }
        }

        return new MinMax(min.toString(), max.toString());
    }

    /**
     * Java equivalent of fucking Pair<String, String>
     */
    class MinMax
    {
        private String min;
        private String max;

        MinMax(String min, String max)
        {
            this.min = min;
            this.max = max;
        }

        String getMin()
        {
            return min;
        }

        String getMax()
        {
            return max;
        }
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

        VariableSystem.MinMax minMax = vs.getMinMaxArguments();

        System.out.println(minMax.getMin());
        System.out.println(minMax.getMax());
    }
}
