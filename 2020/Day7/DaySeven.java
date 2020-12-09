import java.util.*;
import java.io.*;

public class DaySeven {
    public static class Edge {
        int weight;
        int child;

        public Edge(int weight, int child) {
            this.weight = weight;
            this.child = child;
        }
    }

    public static boolean bfs(int target, int source, ArrayList<ArrayList<Integer>> graph) {
        boolean[] visited = new boolean[graph.size()];
        Arrays.fill(visited, false);
        Queue<Integer> queue = new LinkedList<>();
        queue.add(source);
        visited[source] = true;
        while (!queue.isEmpty()) {
            int curr = queue.poll();
            for (int child : graph.get(curr)) {
                if (!visited[child]) {
                    visited[child] = true;
                    queue.add(child);
                }
                if (child == target) {
                    return true;
                }
            }
        }
        return false;
    }

    public static int computeWeight(int source, ArrayList<ArrayList<Edge>> graph) {
        if (graph.get(source).size() == 0) {
            return 0;
        }
        int totalWeight = 0;
        for (Edge child : graph.get(source)) {
            totalWeight += child.weight * (computeWeight(child.child, graph) + 1);
        }
        return totalWeight;
    }

    public static int partOne() throws IOException {
        File input = new File("./input7.txt");
        Scanner sc = new Scanner(input);
        int count = 0;
        int totalTypes = 0;
        ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
        Map<String, Integer> indexes = new HashMap<>();
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parse = line.split("contain");
            String parent = parse[0].split("bags")[0].trim();
            String[] children = parse[1].split(",");
            if (indexes.get(parent) == null) {
                indexes.put(parent, totalTypes);
                graph.add(new ArrayList<Integer>());
                totalTypes++;
            }
            int parentIndex = indexes.get(parent);
            if (children[0].trim().equals("no other bags.")) {
                continue;
            }
            for (String child : children) {
                String[] keywords = child.trim().split(" ");
                String color = keywords[1] + " " + keywords[2];
                if (indexes.get(color) == null) {
                    indexes.put(color, totalTypes);
                    graph.add(new ArrayList<Integer>());
                    totalTypes++;
                }
                int childIndex = indexes.get(color);
                graph.get(parentIndex).add(childIndex);
            }
        }

        // Do graph traversal
        int target = indexes.get("shiny gold");
        for (String key : indexes.keySet()) {
            if (bfs(target, indexes.get(key), graph)) {
                count++;
            }
        }
 
        return count;
    }

    public static int partTwo() throws IOException {
        File input = new File("./input7.txt");
        Scanner sc = new Scanner(input);
        int totalTypes = 0;
        ArrayList<ArrayList<Edge>> graph = new ArrayList<>();
        Map<String, Integer> indexes = new HashMap<>();
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parse = line.split("contain");
            String parent = parse[0].split("bags")[0].trim();
            String[] children = parse[1].split(",");
            if (indexes.get(parent) == null) {
                indexes.put(parent, totalTypes);
                graph.add(new ArrayList<Edge>());
                totalTypes++;
            }
            int parentIndex = indexes.get(parent);
            if (children[0].trim().equals("no other bags.")) {
                continue;
            }
            for (String child : children) {
                String[] keywords = child.trim().split(" ");
                int weight = Integer.parseInt(keywords[0].trim());
                String color = keywords[1] + " " + keywords[2];
                if (indexes.get(color) == null) {
                    indexes.put(color, totalTypes);
                    graph.add(new ArrayList<Edge>());
                    totalTypes++;
                }
                int childIndex = indexes.get(color);
                graph.get(parentIndex).add(new Edge(weight, childIndex));
            }
        }

        return computeWeight(indexes.get("shiny gold"), graph);
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