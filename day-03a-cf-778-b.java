import java.util.*;
import java.util.function.BinaryOperator;
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

        VariableSystem vs = new VariableSystem(m);

        for(int i = 0; i < n; i++) {
            vs.addStatement(stdin.nextLine());
        }

        VariableSystem.MinMax minMax = vs.getMinMaxArguments();

        System.out.println(minMax.getMin());
        System.out.println(minMax.getMax());
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
