import java.util.*;
import java.io.*;

public class DayNine {
    public static long partOne() throws IOException {
        File input = new File("./input9.txt");
        Scanner sc = new Scanner(input);
        ArrayList<Long> inputs = new ArrayList<>();
        while (sc.hasNextLine()) {
            inputs.add(Long.parseLong(sc.nextLine().trim()));
        }
        sc.close();
        for (int i = 25; i < inputs.size(); i++) {
            Map<Long, Long> dict = new HashMap<>();
            long curr = inputs.get(i);
            boolean valid = false;
            for (int j = i - 25; j < i; j++) {
                Long res = dict.get(curr - inputs.get(j));
                if (res == null) {
                    dict.put(inputs.get(j), 1L);
                } else {
                    valid = true;
                    break;
                }
            }
            if (!valid) {
                return curr;
            }
        }
        return 0L;
    }

    public static long partTwo() throws IOException {
        File input = new File("./input9.txt");
        Scanner sc = new Scanner(input);
        ArrayList<Long> inputs = new ArrayList<>();
        while (sc.hasNextLine()) {
            inputs.add(Long.parseLong(sc.nextLine().trim()));
        }
        sc.close();
        long invalid = partOne();
        ArrayList<Long> beforeInvalid = new ArrayList<>();
        for (int i = 0; i < inputs.size(); i++) {
            if (inputs.get(i) != invalid) {
                beforeInvalid.add(inputs.get(i));
            } else {
                break;
            }
        }
        int numOfBefore = beforeInvalid.size();
        long[] prefixSum = new long[numOfBefore];

        // precompute
        long acc = 0;
        for (int i = 0; i < numOfBefore; i++) {
            acc += beforeInvalid.get(i);
            prefixSum[i] = acc;
        }

        // endpoints (i, j) = prefixSum[j] - prefixSum[i - 1]
        int endpointOne = 0;
        int endpointTwo = 0;
        for (int i = 0; i < numOfBefore; i++) {
            for (int j = i + 1; j < numOfBefore; j++) {
                long contiguousSum = 0L;
                if (i == 0) {
                    contiguousSum = prefixSum[j];
                } else {
                    contiguousSum = prefixSum[j] - prefixSum[i - 1];
                }
                if (contiguousSum == invalid) {
                    endpointOne = i;
                    endpointTwo = j;
                    break;
                }
            }
        }
        long smallest = Long.MAX_VALUE;
        long largest = Long.MIN_VALUE;
        for (int i = endpointOne; i <= endpointTwo; i++) {
            smallest = Math.min(smallest, beforeInvalid.get(i));
            largest = Math.max(largest, beforeInvalid.get(i));
        }
        return smallest + largest;
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
