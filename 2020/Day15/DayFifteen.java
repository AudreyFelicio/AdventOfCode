import java.util.*;
import java.io.*;

public class DayFifteen {
    public static class Number {
        int recent;
        int prev;

        public Number(int recent) {
            this.recent = recent;
            this.prev = -1;
        }

        public Number(int recent, int prev) {
            this.recent = recent;
            this.prev = prev;
        }
    
        public boolean checkSpokenAtLeastTwoTimes() {
            return this.prev != -1;
        }

        public int getDiff() {
            return this.recent - this.prev;
        }
    }

    public static int partOne(int limit) throws IOException {
        File input = new File("./input15.txt");
        Scanner sc = new Scanner(input);
        Map<Integer, Number> data = new HashMap<>();
        String[] numbers = sc.nextLine().trim().split(",");
        int turn = 1;
        int lastSpoken = -1;
        for (int i = 0; i < numbers.length; i++) {
            lastSpoken = Integer.parseInt(numbers[i]);
            data.put(lastSpoken, new Number(turn));
            turn++;
        }
        while (turn != limit + 1) {
            Number lastSpokenData = data.get(lastSpoken);
            if (lastSpokenData.checkSpokenAtLeastTwoTimes()) {
                int currentSpoken = lastSpokenData.getDiff();
                if (data.get(currentSpoken) == null) {
                    data.put(currentSpoken, new Number(turn));
                } else {
                    data.put(currentSpoken, new Number(turn, data.get(currentSpoken).recent));
                }
                lastSpoken = currentSpoken;
            } else {
                data.put(0, new Number(turn, data.get(0).recent));
                lastSpoken = 0;
            }
            turn++;
        }
        sc.close();
        return lastSpoken;
    }

    public static int partTwo() throws IOException {
        return partOne(30000000);
    }

    public static void main(String[] args) {
        try {
            System.out.println(partOne(2020));
            System.out.println(partTwo());
        } catch (IOException err) {
            System.out.println(err);
        }
    }
}
