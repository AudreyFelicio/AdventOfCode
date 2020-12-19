import java.util.*;
import java.util.stream.Collectors;
import java.io.*;

public class DaySixteen {
    public static class Rule {
        String name;
        int firstMin;
        int firstMax;
        int secondMin;
        int secondMax;
        boolean hasBeenAssigned;
        int which;
        boolean[] illegal;

        public Rule(String name, int firstMin, int firstMax, int secondMin, int secondMax) {
            this.name = name;
            this.firstMin = firstMin;
            this.firstMax = firstMax;
            this.secondMin = secondMin;
            this.secondMax = secondMax;
            this.hasBeenAssigned = false;
            this.which = -1;
            this.illegal = new boolean[20];
            Arrays.fill(this.illegal, false);
        }

        public boolean checkValid(int x) {
            return (x >= firstMin && x <= firstMax) || (x >= secondMin && x <= secondMax);
        }

        public void assign(int x) {
            which = x;
            hasBeenAssigned = true;
        }

        public boolean isAssigned() {
            return hasBeenAssigned;
        }

        public void reset() {
            which = -1;
            hasBeenAssigned = false;
        }
    }

    public static boolean checkIfCanAssign(Rule rule, int assign, ArrayList<int[]> validTickets) {
        for (int i = 0; i < validTickets.size(); i++) {
            int[] curr = validTickets.get(i);
            if (!rule.checkValid(curr[assign])) {
                return false;
            }
        }
        // return !rule.illegal[assign];
        return true;
    }

    public static void backtrackSearch(Set<Rule> rules, Rule[] assignments, ArrayList<int[]> validTickets, Rule prevAssigned, int prevIndex) {
        int totalTicketNumbers = validTickets.get(0).length;
        // for (int i = 0; i < assignments.length; i++) {
        //     if (assignments[i] != null) {
        //         System.out.print(assignments[i].name + " ");
        //     }
        // }
        // System.out.println();
        if (rules.size() == 0) {
            System.out.println("here");
            return;
        }
        Rule notAssigned = null;
        Rule currentAssigned = null;
        int index = -1;
        for (Rule rule : rules) {
            if (!rule.isAssigned()) {
                notAssigned = rule;
                break;
            }
        }
        // System.out.println(notAssigned.name);
        for (int i = 0; i < totalTicketNumbers; i++) {
            if (assignments[i] == null && checkIfCanAssign(notAssigned, i, validTickets)) {
                assignments[i] = notAssigned;
                notAssigned.assign(i);
                rules.remove(notAssigned);
                index = i;
                currentAssigned = notAssigned;
            }
            if (index != -1 && currentAssigned != null) {
                // System.out.println(rules.size() + " " + currentAssigned.name + " " + index);
                backtrackSearch(rules, assignments, validTickets, currentAssigned, index);
            }
        }
        if (index == -1) {
            assignments[prevIndex] = null;
            prevAssigned.reset();
            // prevAssigned.illegal[prevIndex] = true;
            rules.add(prevAssigned);
            return;
        }
        return;
    }

    public static int partOne() throws IOException {
        File input = new File("./input16.txt");
        Scanner sc = new Scanner(input);
        String line = "start";
        ArrayList<Rule> rules = new ArrayList<>();
        while (sc.hasNextLine() && !(line = sc.nextLine()).equals("")) {
            String[] inputs = line.split(": ");
            String[] limits = inputs[1].trim().split(" or ");
            String[][] parsedLimits = Arrays.stream(limits).map(s -> s.trim().split("-")).collect(Collectors.toList()).toArray(new String[0][]);
            int firstMin = Integer.parseInt(parsedLimits[0][0]);
            int firstMax = Integer.parseInt(parsedLimits[0][1]);
            int secondMin = Integer.parseInt(parsedLimits[1][0]);
            int secondMax = Integer.parseInt(parsedLimits[1][1]);
            rules.add(new Rule(inputs[0].trim(), firstMin, firstMax, secondMin, secondMax));
        }
        line = sc.nextLine();
        int[] myTicket = Arrays.stream(sc.nextLine().trim().split(","))
            .mapToInt(s -> Integer.parseInt(s))
            .toArray();
        line = sc.nextLine();
        line = sc.nextLine();
        int errorRate = 0;
        while (sc.hasNextLine() && !(line = sc.nextLine()).equals("")) {
            int[] nearbyTicket = Arrays.stream(line.trim().split(","))
                .mapToInt(s -> Integer.parseInt(s))
                .toArray();
            for (int i : nearbyTicket) {
                boolean isInvalid = true;
                for (Rule rule : rules) {
                    if (rule.checkValid(i)) {
                        isInvalid = false;
                        break;
                    }
                }
                if (isInvalid) {
                    errorRate += i;
                }
            }
        }
        sc.close();
        return errorRate;
    }

    public static int partTwo() throws IOException {
        File input = new File("./input16.txt");
        Scanner sc = new Scanner(input);
        String line = "start";
        Set<Rule> rules = new HashSet<>();
        while (sc.hasNextLine() && !(line = sc.nextLine()).equals("")) {
            String[] inputs = line.split(": ");
            String[] limits = inputs[1].trim().split(" or ");
            String[][] parsedLimits = Arrays.stream(limits).map(s -> s.trim().split("-")).collect(Collectors.toList()).toArray(new String[0][]);
            int firstMin = Integer.parseInt(parsedLimits[0][0]);
            int firstMax = Integer.parseInt(parsedLimits[0][1]);
            int secondMin = Integer.parseInt(parsedLimits[1][0]);
            int secondMax = Integer.parseInt(parsedLimits[1][1]);
            rules.add(new Rule(inputs[0].trim(), firstMin, firstMax, secondMin, secondMax));
        }
        line = sc.nextLine();
        int[] myTicket = Arrays.stream(sc.nextLine().trim().split(","))
            .mapToInt(s -> Integer.parseInt(s))
            .toArray();
        line = sc.nextLine();
        line = sc.nextLine();
        ArrayList<int[]> validTickets = new ArrayList<>();
        while (sc.hasNextLine() && !(line = sc.nextLine()).equals("")) {
            int[] nearbyTicket = Arrays.stream(line.trim().split(","))
                .mapToInt(s -> Integer.parseInt(s))
                .toArray();
            boolean isTicketInvalid = false;
            for (int i : nearbyTicket) {
                boolean isInvalid = true;
                for (Rule rule : rules) {
                    if (rule.checkValid(i)) {
                        isInvalid = false;
                        break;
                    }
                }
                if (isInvalid) {
                    isTicketInvalid = true;
                    break;
                }
            }
            if (!isTicketInvalid) {
                validTickets.add(nearbyTicket);
            }
        }
        sc.close();
        Rule[] assignments = new Rule[rules.size()];
        Arrays.fill(assignments, null);
        backtrackSearch(rules, assignments, validTickets, null, -1);
        // for (Rule rule : assignments) {
        //     System.out.print(rule.name + " ");
        // }
        return 0;
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

