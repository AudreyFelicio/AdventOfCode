import java.util.*;
import java.io.*;

public class DayEleven {
    public static int countOccupiedNeighbours(char[][] map, int i, int j, int row, int col) {
        int count = 0;
        for (int k = -1; k <= 1; k += 2) {
            if (i + k >= 0 && i + k < row) {
                if (map[i + k][j] == '#') {
                    count++;
                }
            }
            if (j + k >= 0 && j + k < col) {
                if (map[i][j + k] == '#') {
                    count++;
                }
            }
            for (int l = -1; l <= 1; l += 2) {
                if (i + k >= 0 && i + k < row && j + l >= 0 && j + l < col) {
                    if (map[i + k][j + l] == '#') {
                        count++;
                    } 
                }
            }
        }
        return count;
    }

    public static int seeNeighbours(char[][] map, int i, int j, int row, int col) {
        int count = 0;
        for (int k = -1; k <= 1; k += 2) {
            int tempI = i;
            int tempJ = j;
            while (tempI + k >= 0 && tempI + k < row) {
                char curr = map[tempI + k][tempJ];
                if (curr == 'L') {
                    break;
                } else if (curr == '#') {
                    count++;
                    break;
                }
                tempI += k;
            }
            tempI = i;
            while (tempJ + k >= 0 && tempJ + k < col) {
                char curr = map[tempI][tempJ + k];
                if (curr == 'L') {
                    break;
                } else if (curr == '#') {
                    count++;
                    break;
                }
                tempJ += k;
            }
            tempJ = j;
            for (int l = -1; l <= 1; l += 2) {
                tempI = i;
                tempJ = j;
                while (tempI + k >= 0 && tempI + k < row && tempJ + l >= 0 && tempJ + l < col) {
                    char curr = map[tempI + k][tempJ + l];
                    if (curr == 'L') {
                        break;
                    } else if (curr == '#') {
                        count++;
                        break;
                    }
                    tempI += k;
                    tempJ += l;
                }
            }
        }
        return count;
    }

    public static int partOne() throws IOException {
        File input = new File("./input11.txt");
        Scanner sc = new Scanner(input);
        int row = 0;
        int col = 0;
        char[][] map = new char[100][];
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            char[] characters = line.toCharArray();
            map[row] = characters;
            col = characters.length;
            row++;
        }
        sc.close();
        boolean change = true;
        while (change) {
            change = false;
            boolean[][] whichChanged = new boolean[row][col];
            for (boolean[] bool : whichChanged) {
                Arrays.fill(bool, false);
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    char curr = map[i][j];
                    int occupiedNeighbours = countOccupiedNeighbours(map, i, j, row, col);
                    if (curr == 'L') {
                        if (occupiedNeighbours == 0) {
                            whichChanged[i][j] = true;
                        }
                    } else if (curr == '#') {
                        if (occupiedNeighbours >= 4) {
                            whichChanged[i][j] = true;
                        }
                    } else {
                        continue;
                    }
                }
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (whichChanged[i][j]) {
                        change = true;
                        if (map[i][j] == 'L') {
                            map[i][j] = '#';
                        } else if (map[i][j] == '#') {
                            map[i][j] = 'L';
                        }
                    }
                }
            }
        }
        int countAns = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (map[i][j] == '#') {
                    countAns++;
                }
            }
        }
        return countAns;
    }

    public static long partTwo() throws IOException {
        File input = new File("./input11.txt");
        Scanner sc = new Scanner(input);
        int row = 0;
        int col = 0;
        char[][] map = new char[100][];
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            char[] characters = line.toCharArray();
            map[row] = characters;
            col = characters.length;
            row++;
        }
        sc.close();
        boolean change = true;
        while (change) {
            change = false;
            boolean[][] whichChanged = new boolean[row][col];
            for (boolean[] bool : whichChanged) {
                Arrays.fill(bool, false);
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    char curr = map[i][j];
                    int occupiedNeighbours = seeNeighbours(map, i, j, row, col);
                    if (curr == 'L') {
                        if (occupiedNeighbours == 0) {
                            whichChanged[i][j] = true;
                        }
                    } else if (curr == '#') {
                        if (occupiedNeighbours >= 5) {
                            whichChanged[i][j] = true;
                        }
                    } else {
                        continue;
                    }
                }
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (whichChanged[i][j]) {
                        change = true;
                        if (map[i][j] == 'L') {
                            map[i][j] = '#';
                        } else if (map[i][j] == '#') {
                            map[i][j] = 'L';
                        }
                    }
                }
            }
        }
        int countAns = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (map[i][j] == '#') {
                    countAns++;
                }
            }
        }
        return countAns;   
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
