import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.Stack;

public class hw02 {
    public static class Graph {
        private Map<String, Vertex> vertices;
        private List<String> verticesData;

        public Graph() {
            this.vertices = new LinkedHashMap<>();
            this.verticesData = new ArrayList<>();
        }

        private class Vertex {
            List<String> adjacencies;

            Vertex() {
                this.adjacencies = new ArrayList<>();
            }
        }

        public void addVertex(String vertex) {
            vertices.put(vertex, new Vertex());
            verticesData.add(vertex);
        }

        public void addEdge(String vertex1, String vertex2) {
            if (vertex1 == null || vertex2 == null) {
                return;
            }
            getVertex(vertex1).adjacencies.add(vertex2);
        }

        private Vertex getVertex(String data) {
            return vertices.get(data);
        }
    }

    private static Graph[] graphs;

    private static void parseInput() {
        Scanner input = new Scanner(System.in);
        int numInstances = input.nextInt();
        graphs = new Graph[numInstances];

        for (int i = 0; i < numInstances; i++) {
            Graph currentGraph = new Graph();
            int numNodes = input.nextInt();
            input.nextLine();

            for (int j = 0; j < numNodes; j++) {
                String[] vertices = input.nextLine().split(" ");
                currentGraph.addVertex(vertices[0]);

                for (int v = 1; v < vertices.length; v++) {
                    currentGraph.addEdge(vertices[0], vertices[v]);
                }
            }
            graphs[i] = currentGraph;
        }
        input.close();
    }

    private static void topologicalOrder(Graph graph) {
        Set<String> visited = new HashSet<>();
        StringBuilder result = new StringBuilder();

        for (String vertex : graph.verticesData) {
            if (!visited.contains(vertex)) {
                depthFirstSearch(graph, visited, vertex, result);
            }
        }
        System.out.println(result.toString().trim());
    }

    private static void depthFirstSearch(Graph graph, Set<String> visited, String vertex, StringBuilder result) {
        Stack<String> stack = new Stack<>();
        stack.push(vertex);

        while (!stack.isEmpty()) {
            String current = stack.pop();
            if (!visited.contains(current)) {
                result.append(current).append(" ");
                visited.add(current);
            }

            List<String> neighbors = graph.getVertex(current).adjacencies;
            for (int i = neighbors.size() - 1; i >= 0; i--) {
                String neighbor = neighbors.get(i);
                if (!visited.contains(neighbor)) {
                    stack.push(neighbor);
                }
            }
        }
    }

    public static void main(String[] args) {
        parseInput();

        for (Graph graph : graphs) {
            topologicalOrder(graph);
        }
    }
}