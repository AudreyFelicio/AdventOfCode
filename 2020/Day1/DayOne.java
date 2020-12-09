import java.io.File;
import java.io.IOException;
import java.util.*;

class DayOne {
    public static final int TARGET = 2020;

    public static int partOne() throws IOException {
        File input = new File("./input1.txt");
        Scanner sc = new Scanner(input);
        Map<Integer, Integer> dict = new HashMap<>();
        while (sc.hasNextLine()) {
            int curr = sc.nextInt();
            Integer inDict = dict.get(TARGET - curr);
            if (inDict == null) {
                dict.put(curr, 1);
            } else {
                return curr * (TARGET - curr);
            }
        }
        sc.close();
        return 0;
    }

    public static int partTwo() throws IOException {
        File input = new File("./input1.txt");
        Scanner sc = new Scanner(input);
        Map<Integer, ArrayList<Integer>> dict = new HashMap<>();
        ArrayList<Integer> inputs = new ArrayList<>();
        int counter = 0;
        while (sc.hasNextLine()) {
            int curr = sc.nextInt();
            inputs.add(curr);
            ArrayList<Integer> indexes = dict.get(curr);
            if (indexes == null) {
                indexes = new ArrayList<>();
            }
            indexes.add(counter);
            dict.put(curr, indexes);
            counter++;
        }
        sc.close();
        for (int i = 0; i < counter; i++) {
            for (int j = i + 1; j < counter; j++) {
                int sum = inputs.get(i) + inputs.get(j);
                ArrayList<Integer> res = dict.get(TARGET - sum);
                if (res != null) {
                    for (int k : res) {
                        if (k != i && k != j) {
                            return inputs.get(i) * inputs.get(j) * (TARGET - sum);
                        }
                    }
                }
            }
        }
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