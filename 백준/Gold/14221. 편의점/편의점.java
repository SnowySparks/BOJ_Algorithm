import java.io.*;
import java.util.*;


public class Main {
    public static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    public static StringTokenizer st = null;
    public static StringBuilder sb = new StringBuilder();
    public static final int inf = (int)1e9+7;

    public static int stoi(String s) { //문자열 s -> int형으로
        return Integer.parseInt(s);
    }

    static class Node implements Comparable<Node> {
        int loc, cost;
        Node(int loc, int cost) {
            this.loc = loc;
            this.cost = cost;
        }
        @Override
        public int compareTo(Node o) {
            if (cost == o.cost) return loc - o.loc;
            return cost - o.cost;
        }
    }

    public static PriorityQueue<Node> pq = new PriorityQueue<>(); // 
    static ArrayList<Node>[] adj;

    @SuppressWarnings("unchecked")
    public static void main(String[] args) throws IOException {
        st = new StringTokenizer(br.readLine());
        int n = stoi(st.nextToken()), m = stoi(st.nextToken());
        adj = new ArrayList[n + 1]; //subpresswarnings 적용 이유
        for (int i = 1; i <= n; ++i) adj[i] = new ArrayList<>();

        int dist[] = new int[n+1]; // Dijkstra
        for (int i =1; i <= n; ++i) dist[i] = inf; 

        for (int i = 0; i < m; ++i) {
            st = new StringTokenizer(br.readLine());
            int a = stoi(st.nextToken()), b =stoi(st.nextToken()), c =stoi(st.nextToken());
            
            adj[a].add(new Node(b, c));
            adj[b].add(new Node(a, c));
        }

        st = new StringTokenizer(br.readLine());
        int p = stoi(st.nextToken()), q = stoi(st.nextToken()); // p :집후보지, q : 편의점 후보지

        int[] House = new int[p];
        int[] ConvenientStore = new int[q];

        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < p; ++i) House[i] = stoi(st.nextToken());
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < q; ++i) {
            ConvenientStore[i] = stoi(st.nextToken());
            pq.add(new Node(ConvenientStore[i], 0));
            dist[ConvenientStore[i]] = 0;
        }

        Arrays.sort(House);

        // System.out.println(Arrays.toString(dist));

        // Dijkstra Algorithm
        while (!pq.isEmpty()) {
            Node top = pq.poll();
            int loc = top.loc, cost = top.cost;

            if (cost < dist[loc]) continue;

            for (Node nxt : adj[loc]) {
                int nxt_node = nxt.loc, new_cost = cost + nxt.cost;
                if (new_cost < dist[nxt_node]) {
                    dist[nxt_node] = new_cost;
                    pq.add(new Node(nxt_node, new_cost));
                }
            }
        }

        //답처리
        int ans = inf;
        int ans_dist = inf;
        for (int house : House) {
            if (ans_dist > dist[house]) {
                ans_dist = dist[house];
                ans = house;
            }
        }
        // System.out.println(Arrays.toString(dist));
        System.out.println(ans);
    }

}