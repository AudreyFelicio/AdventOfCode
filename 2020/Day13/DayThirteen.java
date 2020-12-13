import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class DayThirteen {
    public static BigInteger findInverse(BigInteger a, BigInteger modulo) {
        BigInteger originalModulo = modulo;
        BigInteger x = new BigInteger("1");
        BigInteger y = new BigInteger("0");
        while (a.compareTo(new BigInteger("1")) == 1) {
            BigInteger q = a.divide(modulo);
            BigInteger temp = modulo;
            modulo = a.mod(modulo);
            a = temp;
            temp = y;
            y = x.subtract(q.multiply(y));
            x = temp;
        }
        if (x.signum() == -1) {
            x.add(originalModulo);
        }

        return x;
    }

    public static int partOne() throws IOException {
        File input = new File("./input13.txt");
        Scanner sc = new Scanner(input);
        int earliest = Integer.parseInt(sc.nextLine());
        String[] inputs = sc.nextLine().split(",");
        sc.close();
        ArrayList<Integer> busTimestamps = new ArrayList<>();
        for (int i = 0; i < inputs.length; i++) {
            if (!inputs[i].equals("x")) {
                busTimestamps.add(Integer.parseInt(inputs[i]));
            }
        }
        int minWaitingTime = Integer.MAX_VALUE;
        int id = 0;
        for (int i = 0; i < busTimestamps.size(); i++) {
            int currId = busTimestamps.get(i);
            int currWaitingTime = currId - (earliest % currId);
            if (currWaitingTime < minWaitingTime) {
                minWaitingTime = currWaitingTime;
                id = currId;
            }
        }
        return minWaitingTime * id;
    }

    public static BigInteger partTwo() throws IOException {
        class Bus {
            BigInteger id;
            BigInteger extraMinutes;

            public Bus(BigInteger id, BigInteger extraMinutes) {
                this.id = id;
                this.extraMinutes = extraMinutes;
            }
        }
        File input = new File("./input13.txt");
        Scanner sc = new Scanner(input);
        sc.nextLine();
        String[] inputs = sc.nextLine().split(",");
        sc.close();
        ArrayList<Bus> buses = new ArrayList<>();
        for (int i = 0; i < inputs.length; i++) {
            if (!inputs[i].equals("x")) {
                buses.add(new Bus(new BigInteger(inputs[i]), new BigInteger("" + i)));
            }
        }
        BigInteger totalModulo = buses.get(0).id;
        BigInteger remainder = new BigInteger("0");
        for (int i = 1; i < buses.size(); i++) {
            BigInteger currModulo = buses.get(i).id;
            BigInteger currRemainder = buses.get(i).extraMinutes.multiply(new BigInteger("-1")).mod(currModulo);
            if (currRemainder.signum() == -1) {
                currRemainder.add(currModulo);
            }
            System.out.println(currModulo + " " + currRemainder);
            BigInteger prevTotalModulo = totalModulo;
            totalModulo = totalModulo.multiply(currModulo);
            BigInteger inverseOfCurrModulo = findInverse(currModulo, prevTotalModulo);
            BigInteger inverseOfPrevModulo = findInverse(prevTotalModulo, currModulo);
            remainder = prevTotalModulo.multiply(currRemainder).mod(totalModulo).multiply(inverseOfPrevModulo).mod(totalModulo).add(
                    currModulo.multiply(remainder).mod(totalModulo).multiply(inverseOfCurrModulo).mod(totalModulo)).mod(totalModulo);
            if (remainder.signum() == -1) {
                remainder.add(totalModulo);
            }
            System.out.println(remainder + " " + totalModulo);
        }
        return remainder.mod(totalModulo);
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
