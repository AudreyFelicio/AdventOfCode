import java.util.*;
import java.io.*;

public class DayEight {
    public static class Instruction {
        String name;
        int value;

        public Instruction(String name, int value) {
            this.name = name;
            this.value = value;
        }
    }

    public static int partOne() throws IOException {
        File input = new File("./input8.txt");
        Scanner sc = new Scanner(input);
        int accumulator = 0;
        ArrayList<Instruction> instructions = new ArrayList<>();
        while (sc.hasNextLine()) {
            String[] parse = sc.nextLine().trim().split(" ");
            instructions.add(new Instruction(parse[0], Integer.parseInt(parse[1])));
        }
        sc.close();
        boolean[] visited = new boolean[instructions.size()];
        int counter = 0;
        Arrays.fill(visited, false);
        while (!visited[counter]) {
            visited[counter] = true;
            Instruction curr = instructions.get(counter);
            if (curr.name.equals("nop")) {
                counter++;
            } else if (curr.name.equals("acc")) {
                accumulator += curr.value;
                counter++;
            } else {
                counter += curr.value;
            }
        }
        return accumulator;
    }

    public static int partTwo() throws IOException {
        File input = new File("./input8.txt");
        Scanner sc = new Scanner(input);
        int accumulator = 0;
        ArrayList<Instruction> instructions = new ArrayList<>();
        while (sc.hasNextLine()) {
            String[] parse = sc.nextLine().trim().split(" ");
            instructions.add(new Instruction(parse[0], Integer.parseInt(parse[1])));
        }
        sc.close();
        for (int i = 0; i < instructions.size(); i++) {
            int tempAcc = 0;
            Instruction curr = instructions.get(i);
            if (curr.name.equals("nop")) {
                curr.name = "jmp";
            } else if (curr.name.equals("jmp")) {
                curr.name = "nop";
            }
            boolean[] visited = new boolean[instructions.size()];
            int counter = 0;
            Arrays.fill(visited, false);
            while (counter < instructions.size() && counter >= 0 && !visited[counter]) {
                visited[counter] = true;
                Instruction curr2 = instructions.get(counter);
                if (curr2.name.equals("nop")) {
                    counter++;
                } else if (curr2.name.equals("acc")) {
                    tempAcc += curr2.value;
                    counter++;
                } else {
                    counter += curr2.value;
                }
            }
            if (curr.name.equals("nop")) {
                curr.name = "jmp";
            } else if (curr.name.equals("jmp")) {
                curr.name = "nop";
            }
            if (counter == instructions.size()) {
                accumulator = tempAcc;
                break;
            }
        }
        return accumulator;
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
