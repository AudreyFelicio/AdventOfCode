import java.util.*;
import java.io.*;

public class DayTwo {
    public static int partOne() throws IOException {
        File input = new File("./input2.txt");
        Scanner sc = new Scanner(input);
        int countValid = 0;
        while (sc.hasNextLine()) {
            String[] line = sc.nextLine().split(" ");
            String[] bounds = line[0].split("-");
            char target = line[1].charAt(0);
            int count = 0;
            int lowerBound = Integer.parseInt(bounds[0]);
            int upperBound = Integer.parseInt(bounds[1]);
            for (int i = 0; i < line[2].length(); i++) {
                if (line[2].charAt(i) == target) {
                    count++;
                }
            }
            if (count >= lowerBound && count <= upperBound) {
                countValid++;
            }
        }
        sc.close();
        return countValid;
    }

    public static int partTwo() throws IOException {
        File input = new File("./input2.txt");
        Scanner sc = new Scanner(input);
        int countValid = 0;
        while (sc.hasNextLine()) {
            String[] line = sc.nextLine().split(" ");
            String[] indexes = line[0].split("-");
            char target = line[1].charAt(0);
            int firstIndex = Integer.parseInt(indexes[0]) - 1;
            int secondIndex = Integer.parseInt(indexes[1]) - 1;
            boolean isFirstSame = target == line[2].charAt(firstIndex);
            boolean isSecondSame = target == line[2].charAt(secondIndex);
            if (isFirstSame ^ isSecondSame) {
                countValid++;
            }
        }
        sc.close();
        return countValid;
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