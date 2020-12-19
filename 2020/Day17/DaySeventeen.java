import java.util.*;
import java.io.*;

public class DaySeventeen {
    public static int countNeighbours(ArrayList<char[][]> grid, int x, int y, int z) {
        char[][] before = grid.get(z - 1);
        char[][] current = grid.get(z);
        char[][] after = grid.get(z + 1);
        int count = 0;
        for (int i = -1; i <= 1; i += 2) {
            if (before[x + i][y] == '#') {
                count++;
            }
            if (current[x + i][y] == '#') {
                count++;
            }
            if (after[x + i][y] == '#') {
                count++;
            }
            if (before[x][y + i] == '#') {
                count++;
            }
            if (current[x][y + i] == '#') {
                count++;
            }
            if (after[x][y + i] == '#') {
                count++;
            }
            for (int j = -1; j <= 1; j += 2) {
                if (before[x + i][y + j] == '#') {
                    count++;
                }
                if (current[x + i][y + j] == '#') {
                    count++;
                }
                if (after[x + i][y + j] == '#') {
                    count++;
                }
            }
        }
        if (before[x][y] == '#') {
            count++;
        }
        if (after[x][y] == '#') {
            count++;
        }
        return count;
    }

    public static int countNeighboursHyper(ArrayList<ArrayList<char[][]>> grid, int x, int y, int z, int w) {
        int count = 0;
        ArrayList<char[][]> before = grid.get(w - 1);
        ArrayList<char[][]> current = grid.get(w);
        ArrayList<char[][]> after = grid.get(w + 1);
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
                    if (before.get(z + i)[x + j][y + k] == '#') {
                        count++;
                    }
                    if (current.get(z + i)[x + j][y + k] == '#') {
                        count++;
                    }
                    if (after.get(z + i)[x + j][y + k] == '#') {
                        count++;
                    }
                }
            }
        }
        if (current.get(z)[x][y] == '#') {
            count--;
        }
        return count;
    }

    public static int partOne() throws IOException {
        File input = new File("./input17.txt");
        Scanner sc = new Scanner(input);
        ArrayList<char[][]> grid = new ArrayList<>();
        for (int i = 0; i < 21; i++) {
            char[][] emptyDimension = new char[500][500];
            for (char[] row : emptyDimension) {
                Arrays.fill(row, '.');
            }
            grid.add(emptyDimension);
        }
        char[][] xyDimension = new char[500][500];
        int activeXLow = 230;
        int activeXHigh = 240;
        int activeYLow = 230;
        int activeYHigh = 240;
        int activeZLow = 10;
        int activeZHigh = 10;
        int zOffset = 10;
        int startRow = 230;
        int startCol = 230;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            for (int i = 0; i < line.length(); i++) {
                xyDimension[startRow][startCol + i] = line.charAt(i);
            }
            startRow++;
        }
        sc.close();
        grid.set(zOffset, xyDimension);
        int cycles = 0;
        while (cycles != 6) {
            ArrayList<char[][]> copyGrid = new ArrayList<>();
            for (int i = 0; i < grid.size(); i++) {
                char[][] curr = grid.get(i);
                char[][] copy = new char[500][500];
                for (int j = 0; j < 500; j++) {
                    for (int k = 0; k < 500; k++) {
                        copy[j][k] = curr[j][k];
                    }
                }
                copyGrid.add(copy);
            }
            for (int i = activeZLow - 1; i <= activeZHigh + 1; i++) {
                char[][] currPlane = copyGrid.get(i);
                for (int j = activeXLow - 1; j <= activeXHigh + 1; j++) {
                    for (int k = activeYLow - 1; k <= activeYHigh; k++) {
                        int neighbours = countNeighbours(grid, j, k, i);
                        if (currPlane[j][k] == '#') {
                            if (!(neighbours == 2 || neighbours == 3)) {
                                currPlane[j][k] = '.';
                            }
                        } else {
                            if (neighbours == 3) {
                                currPlane[j][k] = '#';
                            }
                        }
                    }
                }
            }
            grid = copyGrid;
            activeZLow--;
            activeZHigh++;
            activeXLow--;
            activeXHigh++;
            activeYLow--;
            activeYHigh++;
            cycles++;
        }
        int totalActive = 0;
        for (int i = activeZLow; i <= activeZHigh; i++) {
            char[][] currPlane = grid.get(i);
            for (int j = activeXLow; j <= activeXHigh; j++) {
                for (int k = activeYLow; k <= activeYHigh; k++) {
                    if (currPlane[j][k] == '#') {
                        totalActive++;
                    }
                }
            }
        }
        return totalActive;
    }

    public static int partTwo() throws IOException {
        File input = new File("./input17.txt");
        Scanner sc = new Scanner(input);
        ArrayList<ArrayList<char[][]>> grid = new ArrayList<>();
        for (int j = 0; j < 21; j++) {
            ArrayList<char[][]> miniGrid = new ArrayList<>();
            for (int i = 0; i < 21; i++) {
                char[][] emptyDimension = new char[500][500];
                for (char[] row : emptyDimension) {
                    Arrays.fill(row, '.');
                }
                miniGrid.add(emptyDimension);
            }
            grid.add(miniGrid);
        }
        char[][] xyDimension = new char[500][500];
        int activeXLow = 230;
        int activeXHigh = 240;
        int activeYLow = 230;
        int activeYHigh = 240;
        int activeZLow = 10;
        int activeZHigh = 10;
        int activeWLow = 10;
        int activeWHigh = 10;
        int zOffset = 10;
        int wOffset = 10;
        int startRow = 230;
        int startCol = 230;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            for (int i = 0; i < line.length(); i++) {
                xyDimension[startRow][startCol + i] = line.charAt(i);
            }
            startRow++;
        }
        sc.close();
        grid.get(wOffset).set(zOffset, xyDimension);
        int cycles = 0;
        while (cycles != 6) {
            ArrayList<ArrayList<char[][]>> copyGrid = new ArrayList<>();
            for (int i = 0; i < grid.size(); i++) {
                ArrayList<char[][]> copyInnerGrid = new ArrayList<>();
                for (int j = 0; j < 21; j++) {
                    char[][] original = grid.get(i).get(j);
                    char[][] planeCopy = new char[500][500];
                    for (int k = 0; k < 500; k++) {
                        for (int l = 0; l < 500; l++) {
                            planeCopy[k][l] = original[k][l];
                        }
                    }
                    copyInnerGrid.add(planeCopy);
                }
                copyGrid.add(copyInnerGrid);
            }
            for (int i = activeWLow - 1; i <= activeWHigh + 1; i++) {
                ArrayList<char[][]> currInnerGrid = copyGrid.get(i);
                for (int j = activeZLow - 1; j <= activeZHigh + 1; j++) {
                    char[][] currPlane = currInnerGrid.get(j);
                    for (int k = activeXLow - 1; k <= activeXHigh + 1; k++) {
                        for (int l = activeYLow - 1; l <= activeYHigh + 1; l++) {
                            int neighbours = countNeighboursHyper(grid, k, l, j, i);
                            if (currPlane[k][l] == '#') {
                                if (!(neighbours == 2 || neighbours == 3)) {
                                    currPlane[k][l] = '.';
                                }
                            } else {
                                if (neighbours == 3) {
                                    currPlane[k][l] = '#';
                                }
                            }
                        }
                    }
                }
            }
            grid = copyGrid;
            activeWLow--;
            activeWHigh++;
            activeZLow--;
            activeZHigh++;
            activeXLow--;
            activeXHigh++;
            activeYLow--;
            activeYHigh++;
            cycles++;
        }
        int totalActive = 0;
        for (int i = activeWLow - 1; i <= activeWHigh + 1; i++) {
            ArrayList<char[][]> currInnerGrid = grid.get(i);
            for (int j = activeZLow - 1; j <= activeZHigh + 1; j++) {
                char[][] currPlane = currInnerGrid.get(j);
                for (int k = activeXLow - 1; k <= activeXHigh + 1; k++) {
                    for (int l = activeYLow - 1; l <= activeYHigh + 1; l++) {
                        if (currPlane[k][l] == '#') {
                            totalActive++;
                        }
                    }
                }
            }
        }
        return totalActive;
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

