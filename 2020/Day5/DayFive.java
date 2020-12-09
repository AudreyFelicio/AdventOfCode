import java.util.*;
import java.io.*;

public class DayFive {
    public static int partOne() throws IOException {
        File input = new File("./input5.txt");
        Scanner sc = new Scanner(input);
        int highestId = 0;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            int currRow = 0;
            int currCol = 0;
            for (int i = 0; i < 7; i++) {
                char curr = line.charAt(i);
                if (curr == 'B') {
                    currRow += Math.pow(2, 6 - i);
                }
            }
            for (int i = 7; i < 10; i++) {
                char curr = line.charAt(i);
                if (curr == 'R') {
                    currCol += Math.pow(2, 9 - i);
                }
            }
            highestId = Math.max(highestId, currRow * 8 + currCol);
        }
        sc.close();
        return highestId;
    }

    public static int partTwo() throws IOException {
        File input = new File("./input5.txt");
        Scanner sc = new Scanner(input);
        int[] Ids = new int[1024];
        Arrays.fill(Ids, 0);
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            int currRow = 0;
            int currCol = 0;
            for (int i = 0; i < 7; i++) {
                char curr = line.charAt(i);
                if (curr == 'B') {
                    currRow += Math.pow(2, 6 - i);
                }
            }
            for (int i = 7; i < 10; i++) {
                char curr = line.charAt(i);
                if (curr == 'R') {
                    currCol += Math.pow(2, 9 - i);
                }
            }
            Ids[currRow * 8 + currCol] = 1;
        }
        sc.close();
        for (int i = 9; i < 1023; i++) {
            if (Ids[i] == 0 && Ids[i - 1] == 1 && Ids[i + 1] == 1) {
                return i;
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