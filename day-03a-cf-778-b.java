import java.util.*;
import java.util.function.BinaryOperator;
import java.util.regex.*;

class Day03a
{
    private static Scanner stdin = new Scanner(System.in);

    public static void main(String[] args)
    {
        int n = Integer.parseInt(stdin.next());
        int m = Integer.parseInt(stdin.next());

        stdin.nextLine();

        VariableSystem vs = new VariableSystem(m);

        for(int i = 0; i < n; i++) {
            String varName = stdin.next();
            stdin.next();
            String expression = stdin.nextLine();

            vs.addStatement(varName, expression);
        }

        VariableSystem.MinMax minMax = vs.getMinMaxArguments();

        System.out.println(minMax.getMin());
        System.out.println(minMax.getMax());
    }
}

class VariableSystem
{
    private static Pattern exprPattern = Pattern.compile(" (\\?|[a-z]+|[01]+) (AND|OR|XOR) (\\?|[a-z]+|[01]+)");

    private int nBits;

    /**
     * Each boolean[] represents the truth table of a bitwise boolean function with respect to Petya's answer.
     * Bits [0; nBits) correspond to the value of the function when the corresponding bits of the argument are set, bits
     * [nBits; 2 * nBits) represent the same, but when bits of the argument are unset
     */
    private HashMap<String, boolean[]> bitwiseFunctions = new HashMap<>();

    VariableSystem(int nBits)
    {
        this.nBits = nBits;
    }

    /**
     * @return Bitwise truth table of identity function
     */
    private boolean[] identity()
    {
        boolean[] identity = new boolean[nBits * 2];

        for(int i = 0; i < nBits; i++) {
            identity[i] = true;
            identity[nBits + i] = false;
        }

        return identity;
    }

    /**
     * @return Bitwise truth table of constant function
     */
    private boolean[] constant(String s)
    {
        assert s.length() == nBits;

        boolean[] constant = new boolean[nBits * 2];

        for(int i = 0; i < nBits; i++) {
            constant[i] = constant[nBits + i] = s.charAt(i) == '1';
        }

        return constant;
    }

    private boolean[] parsePrimaryExpression(String primaryExpr)
    {
        if(primaryExpr.equals("?")) {
            return identity();
        }
        else if(primaryExpr.matches("^[01]+$")) {
            return constant(primaryExpr);
        }
        else {
            return bitwiseFunctions.get(primaryExpr);
        }
    }

    /**
     * @param one Truth table of one function
     * @param another Truth table of another function
     * @param op A binary boolean operation
     * @return The result of application of the operation to the two functions
     */
    private boolean[] applyOperation(boolean[] one, boolean[] another, BinaryOperator<Boolean> op)
    {
        boolean[] operationResult = new boolean[nBits * 2];

        for(int i = 0; i < nBits; i++) {
            operationResult[i] = op.apply(one[i], another[i]);
            operationResult[nBits + i] = op.apply(one[nBits + i], another[nBits + i]);
        }

        return operationResult;
    }

    private boolean[] parseExpression(String expr)
    {
        Matcher m = exprPattern.matcher(expr);

        if(m.find()) {
            boolean[] a = parsePrimaryExpression(m.group(1));
            boolean[] b = parsePrimaryExpression(m.group(3));

            switch(m.group(2)) {
                case "AND":
                    return applyOperation(a, b, (x, y) -> x && y);
                case "OR":
                    return applyOperation(a, b, (x, y) -> x || y);
                case "XOR":
                    return applyOperation(a, b, (x, y) -> x != y);
                default: // Never happens
                    throw new IllegalArgumentException("");
            }
        }
        else {
            return parsePrimaryExpression(expr.substring(1));
        }
    }

    void addStatement(String varName, String expression)
    {
        bitwiseFunctions.put(varName, parseExpression(expression));
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

            for(boolean[] function : bitwiseFunctions.values()) {
                if(function[i]) {
                    onesIfSet += 1;
                }

                if(function[nBits + i]) {
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
