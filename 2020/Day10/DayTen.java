import java.util.*;
import java.io.*;

public class DayTen {
    public static int partOne() throws IOException {
        File input = new File("./input10.txt");
        Scanner sc = new Scanner(input);
        ArrayList<Integer> adapters = new ArrayList<>();
        while (sc.hasNextLine()) {
            adapters.add(Integer.parseInt(sc.nextLine().trim()));
        }
        sc.close();
        adapters.add(0);
        Collections.sort(adapters);
        adapters.add(adapters.get(adapters.size() - 1) + 3);
        int oneJolt = 0;
        int threeJolt = 0;
        for (int i = 0; i < adapters.size() - 1; i++) {
            int diff = adapters.get(i + 1) - adapters.get(i);
            if (diff == 3) {
                threeJolt++;
            }
            if (diff == 1) {
                oneJolt++;
            }
        }
        return oneJolt * threeJolt;
    }

    public static long partTwo() throws IOException {
        File input = new File("./input10.txt");
        Scanner sc = new Scanner(input);
        ArrayList<Integer> adapters = new ArrayList<>();
        while (sc.hasNextLine()) {
            adapters.add(Integer.parseInt(sc.nextLine().trim()));
        }
        sc.close();
        adapters.add(0);
        Collections.sort(adapters);
        adapters.add(adapters.get(adapters.size() - 1) + 3);
        long[] dp = new long[adapters.get(adapters.size() - 1) + 1];
        Arrays.fill(dp, 0);
        dp[0] = 1;
        for (int i = 0; i < adapters.size(); i++) {
            int curr = adapters.get(i);
            for (int j = 1; j <= 3; j++) {
                if (curr - j >= 0) {
                    dp[curr] += dp[curr - j];
                }
            }
        }
        return dp[dp.length - 1];
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
