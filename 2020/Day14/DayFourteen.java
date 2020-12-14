import java.util.*;
import java.io.*;

public class DayFourteen {
    public static char[] convertToBinary(long x) {
        int counter = 0;
        char[] res = new char[36];
        while (counter != 36) {
            res[35 - counter] = (char) ((x % 2) + '0');
            x /= 2;
            counter++;
        }
        return res;
    }

    public static long convertToDecimal(char[] maskedValues) {
        long multiplier = 1;
        long res = 0;
        for (int i = maskedValues.length - 1; i >= 0; i--) {
            res += multiplier * (maskedValues[i] - '0');
            multiplier *= 2;
        }
        return res;
    }

    public static ArrayList<Long> generateAllAddress(char[] maskedValues) {
        ArrayList<Long> addresses = new ArrayList<>();
        addresses.add(0L);
        long multiplier = 1;
        for (int i = maskedValues.length - 1; i >= 0; i--) {
            int currAddressSize = addresses.size();
            for (int j = 0; j < currAddressSize; j++) {
                long currAddressValue = addresses.get(j);
                if (maskedValues[i] == 'X') {
                    addresses.add(currAddressValue + multiplier);
                } else {
                    addresses.set(j, currAddressValue + multiplier * (maskedValues[i] - '0'));
                }
            }
            multiplier *= 2;
        }
        return addresses;
    }

    public static long partOne() throws IOException {
        File input = new File("./input14.txt");
        Scanner sc = new Scanner(input);
        Map<Long, Long> mem = new HashMap<>();
        char[] currMask = new char[36];
        while (sc.hasNextLine()) {
            String[] inputs = sc.nextLine().trim().split("=");
            if (inputs[0].trim().equals("mask")) {
                currMask = inputs[1].trim().toCharArray();
            } else {
                long index = Long.parseLong(inputs[0].trim().substring(4, inputs[0].trim().length() - 1));
                char[] currValue = convertToBinary(Long.parseLong(inputs[1].trim()));
                char[] maskedValues = new char[36];
                for (int i = 0; i < 36; i++) {
                    if (currMask[i] == 'X') {
                        maskedValues[i] = currValue[i];
                    } else {
                        maskedValues[i] = currMask[i];
                    }
                }
                mem.put(index, convertToDecimal(maskedValues));
            }
        }
        sc.close();
        long sum = 0;
        for (long index : mem.keySet()) {
            sum += mem.get(index);
        }
        return sum;
    }

    public static long partTwo() throws IOException {
        File input = new File("./input14.txt");
        Scanner sc = new Scanner(input);
        Map<Long, Long> mem = new HashMap<>();
        char[] currMask = new char[36];
        while (sc.hasNextLine()) {
            String[] inputs = sc.nextLine().trim().split("=");
            if (inputs[0].trim().equals("mask")) {
                currMask = inputs[1].trim().toCharArray();
            } else {
                long index = Long.parseLong(inputs[0].trim().substring(4, inputs[0].trim().length() - 1));
                long currValue = Long.parseLong(inputs[1].trim());
                char[] indexInBinary = convertToBinary(index);
                char[] maskedValues = new char[36];
                for (int i = 0; i < 36; i++) {
                    if (currMask[i] == '0') {
                        maskedValues[i] = indexInBinary[i];
                    } else {
                        maskedValues[i] = currMask[i]; 
                    }
                }
                ArrayList<Long> addresses = generateAllAddress(maskedValues);
                for (int i = 0; i < addresses.size(); i++) {
                    mem.put(addresses.get(i), currValue);
                }
            }
        }
        sc.close();
        long sum = 0;
        for (long index : mem.keySet()) {
            sum += mem.get(index);
        }
        return sum;
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
