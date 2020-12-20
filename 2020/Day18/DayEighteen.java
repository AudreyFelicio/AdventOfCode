import java.util.*;
import java.io.*;

public class DayEighteen {
    public static String parenthesizePrimitive(String primitive) {
        StringBuilder result = new StringBuilder();
        String[] parse = primitive.trim().split(" ");
        boolean[] isPlus = new boolean[parse.length];
        for (int i = 0; i < isPlus.length; i++) {
            if (parse[i].equals("+")) {
                isPlus[i] = true;
            }
        }
        int iterator = 1;
        while (iterator < isPlus.length) {
            if (isPlus[iterator]) {
                int forwardChecking = iterator + 2;
                while (forwardChecking < isPlus.length && isPlus[forwardChecking]) {
                    forwardChecking += 2;
                }
                StringBuilder curr = new StringBuilder();
                curr.append("(");
                for (int i = iterator - 1; i <= forwardChecking - 1; i++) {
                    curr.append(parse[i] + " ");
                }
                int end = curr.length();
                curr.replace(end - 1, end, ")");
                result.append(curr);
                iterator = forwardChecking;
            } else {
                if (iterator - 2 >= 1 && isPlus[iterator - 2]) {
                    result.append(" * ");
                } else {
                    result.append(parse[iterator - 1] + " * ");
                }
                if (iterator + 2 >= isPlus.length) {
                    result.append(parse[iterator + 1]);
                }
                iterator += 2;
            }
        }
        return result.toString();
    }

    public static long partOne() throws IOException {
        File input = new File("./input18.txt");
        Scanner sc = new Scanner(input);
        long totalRes = 0;
        while (sc.hasNextLine()) {
            String line = "(" + sc.nextLine() + ")";
            Stack<String> stack = new Stack<>();
            int slider = 0;
            while (slider != line.length()) {
                if (line.charAt(slider) == '(') {
                    stack.push("(");
                    slider++;
                } else if ((int) (line.charAt(slider) - '0') >= 0 && (int) (line.charAt(slider) - '0') <= 9) {
                    int forward = slider;
                    StringBuilder acc = new StringBuilder();
                    while (line.charAt(forward) != ' ' && line.charAt(forward) != ')') {
                        acc.append(line.charAt(forward));
                        forward++;
                    }
                    stack.push(acc.toString());
                    slider = forward;
                } else if (line.charAt(slider) == ')') {
                    String top = stack.pop();
                    Stack<String> reverse = new Stack<>();
                    while (!top.equals("(")) {
                        reverse.push(top);
                        top = stack.pop();
                    }
                    long tempEval = 0;
                    while (!reverse.isEmpty()) {
                        String leftmost = reverse.pop();
                        if (leftmost.equals("+")) {
                            String next = reverse.pop();
                            tempEval += Long.parseLong(next);
                        } else if (leftmost.equals("*")) {
                            String next = reverse.pop();
                            tempEval *= Long.parseLong(next);
                        } else {
                            tempEval = Long.parseLong(leftmost);
                        }
                    }
                    stack.push("" + tempEval);
                    slider++;
                } else if (line.charAt(slider) == '+') {
                    stack.push("+");
                    slider++;
                } else if (line.charAt(slider) == '*') {
                    stack.push("*");
                    slider++;
                } else {
                    slider++;
                }
            }
            totalRes += Long.parseLong(stack.pop());
        }
        sc.close();
        return totalRes;
    }

    public static long partTwo() throws IOException {
        File input = new File("./input18.txt");
        Scanner sc = new Scanner(input);
        long totalRes = 0;
        while (sc.hasNextLine()) {
            String line = "(" + sc.nextLine() + ")";
            Stack<String> stack = new Stack<>();
            int slider = 0;
            while (slider != line.length()) {
                if (line.charAt(slider) == '(') {
                    stack.push("(");
                    slider++;
                } else if ((int) (line.charAt(slider) - '0') >= 0 && (int) (line.charAt(slider) - '0') <= 9) {
                    int forward = slider;
                    StringBuilder acc = new StringBuilder();
                    while (line.charAt(forward) != ' ' && line.charAt(forward) != ')') {
                        acc.append(line.charAt(forward));
                        forward++;
                    }
                    stack.push(acc.toString());
                    slider = forward;
                } else if (line.charAt(slider) == ')') {
                    String top = stack.pop();
                    StringBuilder primitive = new StringBuilder("");
                    while (!top.equals("(")) {
                        primitive.insert(0, " " + top);
                        top = stack.pop();
                    }
                    primitive.replace(0, 1, "");
                    String augmentParentheses = "(" + parenthesizePrimitive(primitive.toString()) + ")";
                    int iterator = 0;
                    Stack<String> innerEval = new Stack<>();
                    while (iterator != augmentParentheses.length()) {
                        if (augmentParentheses.charAt(iterator) == '(') {
                            innerEval.push("(");
                            iterator++;
                        } else if ((int) (augmentParentheses.charAt(iterator) - '0') >= 0 && (int) (augmentParentheses.charAt(iterator) - '0') <= 9) {
                            int forward = iterator;
                            StringBuilder acc = new StringBuilder();
                            while (augmentParentheses.charAt(forward) != ' ' && augmentParentheses.charAt(forward) != ')') {
                                acc.append(augmentParentheses.charAt(forward));
                                forward++;
                            }
                            innerEval.push(acc.toString());
                            iterator = forward;
                        } else if (augmentParentheses.charAt(iterator) == '+') {
                            innerEval.push("+");
                            iterator++;
                        } else if (augmentParentheses.charAt(iterator) == '*') {
                            innerEval.push("*");
                            iterator++;
                        } else if (augmentParentheses.charAt(iterator) == ')') {
                            String innerTop = innerEval.pop();
                            Stack<String> reverse = new Stack<>();
                            while (!innerTop.equals("(")) {
                                reverse.push(innerTop);
                                innerTop = innerEval.pop();
                            }
                            long tempEval = 0;
                            while (!reverse.isEmpty()) {
                                String leftmost = reverse.pop();
                                if (leftmost.equals("+")) {
                                    String next = reverse.pop();
                                    tempEval += Long.parseLong(next);
                                } else if (leftmost.equals("*")) {
                                    String next = reverse.pop();
                                    tempEval *= Long.parseLong(next);
                                } else {
                                    tempEval = Long.parseLong(leftmost);
                                }
                            }
                            innerEval.push("" + tempEval);
                            iterator++;
                        } else {
                            iterator++;
                        }
                    }
                    stack.push(innerEval.pop());
                    slider++;
                } else if (line.charAt(slider) == '+') {
                    stack.push("+");
                    slider++;
                } else if (line.charAt(slider) == '*') {
                    stack.push("*");
                    slider++;
                } else {
                    slider++;
                }
            }
            totalRes += Long.parseLong(stack.pop());
        }
        sc.close();
        return totalRes;
    }

    public static void main(String[] args) {
        try {
            System.out.println(partOne());
            System.out.println(partTwo());
        } catch (IOException err) {
            System.out.println(err);
        }
    }
}
