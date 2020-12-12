import java.util.*;
import java.io.*;

public class DayTwelve {
    public static int partOne() throws IOException {
        File input = new File("./input12.txt");
        Scanner sc = new Scanner(input);
        double posX = 0;
        double posY = 0;
        int degrees = 0;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            char direction = line.charAt(0);
            int value = Integer.parseInt(line.substring(1));
            if (direction == 'N') {
                posY += value;
            } else if (direction == 'S') {
                posY -= value;
            } else if (direction == 'E') {
                posX += value;
            } else if (direction == 'W') {
                posX -= value;
            } else if (direction == 'L') {
                degrees += value;
            } else if (direction == 'R') {
                degrees -= value;
            } else {
                posX += value * Math.cos(Math.toRadians(degrees));
                posY += value * Math.sin(Math.toRadians(degrees));
            }
        }
        sc.close();
        return (int) Math.round(Math.abs(posX) + Math.abs(posY));
    }

    public static int partTwo() throws IOException {
        File input = new File("./input12.txt");
        Scanner sc = new Scanner(input);
        double waypointX = 10;
        double waypointY = 1;
        double posX = 0;
        double posY = 0;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            char direction = line.charAt(0);
            int value = Integer.parseInt(line.substring(1));
            if (direction == 'N') {
                waypointY += value;
            } else if (direction == 'S') {
                waypointY -= value;
            } else if (direction == 'E') {
                waypointX += value;
            } else if (direction == 'W') {
                waypointX -= value;
            } else if (direction == 'L') {
                if (value % 360 == 90) {
                    double temp = waypointX;
                    waypointX = -waypointY;
                    waypointY = temp;
                } else if (value % 360 == 180) {
                    waypointX = -waypointX;
                    waypointY = -waypointY;
                } else if (value % 360 == 270) {
                    double temp = waypointX;
                    waypointX = waypointY;
                    waypointY = -temp;
                }
            } else if (direction == 'R') {
                if (value % 360 == 90) {
                    double temp = waypointX;
                    waypointX = waypointY;
                    waypointY = -temp;
                } else if (value % 360 == 180) {
                    waypointX = -waypointX;
                    waypointY = -waypointY;
                } else if (value % 360 == 270) {
                    double temp = waypointX;
                    waypointX = -waypointY;
                    waypointY = temp;
                }
            } else {
                posX += value * waypointX;
                posY += value * waypointY;
            }
        }
        sc.close();
        return (int) Math.round(Math.abs(posX) + Math.abs(posY));
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
