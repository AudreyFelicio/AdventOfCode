import java.util.*;
import java.io.*;

public class DaySix {
    public static int partOne() throws IOException {
        File input = new File("./input6.txt");
        Scanner sc = new Scanner(input);
        String line = "";
        int count = 0;
        while (sc.hasNextLine()) {
            Map<Character, Boolean> dict = new HashMap<>();
            while (sc.hasNextLine() && !(line = sc.nextLine()).equals("")) {
                for (int i = 0; i < line.length(); i++) {
                    if (dict.get(line.charAt(i)) == null) {
                        dict.put(line.charAt(i), true);
                    }
                }
            }
            count += dict.keySet().size();
        }
        return count;
    }

    public static int partTwo() throws IOException {
        File input = new File("./input6.txt");
        Scanner sc = new Scanner(input);
        String line = "";
        int count = 0;
        while (sc.hasNextLine()) {
            Map<Character, Integer> dict = new HashMap<>();
            int people = 0;
            while (sc.hasNextLine() && !(line = sc.nextLine()).equals("")) {
                for (int i = 0; i < line.length(); i++) {
                    if (dict.get(line.charAt(i)) == null) {
                        dict.put(line.charAt(i), 1);
                    } else {
                        dict.put(line.charAt(i), dict.get(line.charAt(i)) + 1);
                    }
                }
                people++;
            }
            for (char c : dict.keySet()) {
                if (dict.get(c) == people) {
                    count++;
                }
            }
        }
        return count;
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