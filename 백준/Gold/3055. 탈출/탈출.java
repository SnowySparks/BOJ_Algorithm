import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

class Node {
    public int r;
    public int c;
    Node(int r, int c) {
        this.r = r;
        this.c = c;
    }
    Node() {
        this(0, 0);
    }
}

public class Main {
    public static StringBuilder pr = new StringBuilder();
    public static StringTokenizer st;
    public static int[] dr = {1, -1, 0, 0};
    public static int[] dc = {0, 0, 1, -1};
    public static int[][] waterTime; // 해당 물
    public static int[][] v;
    public static char[][] map;
    public static Queue<Node> pq = new LinkedList<>(); //player q
    public static Queue<Node> wq = new LinkedList<>(); //water q
    public static void main(String[] args) throws IOException {
        // Setting
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        //Input
        st = new StringTokenizer(br.readLine());
        int R = Integer.parseInt(st.nextToken());
        int C = Integer.parseInt(st.nextToken());

        waterTime = new int[R][C];
        v = new int[R][C];
        map = new char[R][C];

        int er = -1, ec = -1;

        for (int i = 0; i < R; ++i) {
            String s = br.readLine();
            for (int j = 0; j < C; ++j) {
                switch (s.charAt(j)) {
                    case '*':
                        wq.offer(new Node(i, j));
                        waterTime[i][j] = 1;
                        map[i][j] = '*';
                        break;
                    case 'D':
                        er = i;
                        ec = j;
                        map[i][j] = '.';
                        waterTime[i][j] = 1000000;
                        break;
                    case 'S':
                        pq.add(new Node(i, j));
                        map[i][j] = '.';
                        v[i][j] = 1;
                        break;
                    default:
                        map[i][j] = s.charAt(j);
                        break;
                }
            }
        }

        // water simulation
        
        while (!wq.isEmpty()) {
            Node nd = wq.poll();
            int r = nd.r, c = nd.c;
            // System.out.println("wqsize : " + wq.size() + "| " + r + ", " + c);
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C || map[nr][nc] == 'X' ||waterTime[nr][nc] != 0) continue;
                waterTime[nr][nc] = waterTime[r][c] + 1;
                wq.add(new Node(nr, nc));
            }
        }

        // System.out.println(Arrays.deepToString(waterTime));
        // player simulation
        while (!pq.isEmpty()) {
            Node nd = pq.poll();
            int r = nd.r, c = nd.c;
            if (r == er && c == ec) break;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C || map[nr][nc] == 'X' || v[nr][nc] != 0 || (waterTime[nr][nc] != 0 && waterTime[nr][nc] <= v[r][c] + 1)) continue;
                v[nr][nc] = v[r][c] + 1;
                pq.add(new Node(nr, nc));
            }           
        }
        // System.out.println(Arrays.deepToString(v));
        if (v[er][ec] != 0) {
            System.out.println(v[er][ec]-1);
        }
        else {
            System.out.println("KAKTUS");
        }

    }
}
