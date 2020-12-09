import java.util.*;
import java.io.*;

public class DayThree {
    public static int partOne() throws IOException {
        File input = new File("./input3.txt");
        Scanner sc = new Scanner(input);
        int countTrees = 0;
        char[][] maze = new char[400][50];
        int row = 0;
        int col = 0;
        while (sc.hasNextLine()) {
            String curr = sc.nextLine();
            col = curr.length();
            for (int i = 0; i < col; i++) {
                maze[row][i] = curr.charAt(i);
            }
            row++;
        }
        sc.close();
        countTrees = countTrees(maze, 3, 1, row, col);
        return countTrees;
    }

    public static long partTwo() throws IOException {
        File input = new File("./input3.txt");
        Scanner sc = new Scanner(input);
        int countTrees = 0;
        char[][] maze = new char[400][50];
        int row = 0;
        int col = 0;
        while (sc.hasNextLine()) {
            String curr = sc.nextLine();
            col = curr.length();
            for (int i = 0; i < col; i++) {
                maze[row][i] = curr.charAt(i);
            }
            row++;
        }
        sc.close();
        long firstScheme = (long) countTrees(maze, 1, 1, row, col);
        long secondScheme = (long) countTrees(maze, 3, 1, row, col);
        long thirdScheme = (long) countTrees(maze, 5, 1, row, col);
        long fourthScheme = (long) countTrees(maze, 7, 1, row, col);
        long fifthScheme = (long) countTrees(maze, 1, 2, row, col);
        return firstScheme * secondScheme * thirdScheme * fourthScheme * fifthScheme;
    }

    public static int countTrees(char[][] maze, int slopeX, int slopeY, int row, int col) {
        int i = slopeY;
        int xPos = 0;
        int countTrees = 0;
        while (i < row) {
            xPos = (xPos + slopeX) % col;
            if (maze[i][xPos] == '#') {
                countTrees++;
            }
            i += slopeY;
        }
        return countTrees;
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