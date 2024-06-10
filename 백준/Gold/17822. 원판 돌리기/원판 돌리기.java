import java.io.*;
import java.util.*;

public class Main {

    public static int[] dr = {1, -1, 0, 0};
    public static int[] dc = {0, 0, 1, -1};
    public static int n, m, t;
    
    public static int[][] arr;
    public static int[] tmp;
    public static Deque<int[] > dq = new ArrayDeque<>();

    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringBuilder sb = new StringBuilder();
    static StringTokenizer st;
    static boolean isContact(int r, int c, int num) {
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= n) continue;
            nc = (nc + m)%m;
            if (arr[nr][nc] == num) return true;
        }
        return false;
    }

    static {
        n = 0; m = 0; t = 0;
    }

    public static int stoi (String s) {
        return Integer.parseInt(s);
    }

    public static void main(String[] args) throws IOException {
        st = new StringTokenizer(br.readLine());
        n = stoi(st.nextToken());
        m = stoi(st.nextToken());
        t = stoi(st.nextToken());

        arr = new int[n][m];
        tmp = new int[m];

        for (int i = 0; i < n; ++i) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < m; ++j) {
                arr[i][j] = stoi(st.nextToken());
            }
        }

        int x, d ,k;

        while (t-- > 0) {
            st = new StringTokenizer(br.readLine());
            x = stoi(st.nextToken());
            d = stoi(st.nextToken()); 
            k = stoi(st.nextToken());
            

            // rotate
            for (int i = x-1; i < n; i += x) {
                for (int j = 0; j < m; ++j) {
                    tmp[((j + (d == 0 ? k : m-k))%m)] = arr[i][j];
                }
                System.arraycopy(tmp, 0, arr[i], 0, m);
            }

            boolean done =false;

            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < m; ++c) {
                    if (arr[r][c] == 0) continue;
                    int score = arr[r][c];
                    if (!isContact(r, c, score)) continue;
                    done = true;
                    dq.add(new int[]{r, c});
                    arr[r][c] = 0;

                    while (!dq.isEmpty()) {
                        int[] loc = dq.poll();
                        int cr = loc[0], cc = loc[1];
                        for (int i = 0; i < 4; ++i) {
                            int nr = cr + dr[i], nc = cc + dc[i];
                            if (nr < 0 || nr >= n) continue;
                            nc = (nc + m)%m;
                            if (arr[nr][nc] != score) continue;
                            arr[nr][nc] = 0;
                            dq.push(new int[]{nr, nc});
                        }

                    }
                }
            }

            if (!done) {
                int cnt = 0, total = 0;
                for (int []line : arr) {
                    for (int a : line) {
                        if (a > 0) {
                            cnt++;
                            total+=a;
                        }
                    }
                }
                if (cnt == 0) break;
                double mean = 1.0 * total / cnt;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        if (arr[i][j] > 0) {
                            if (arr[i][j]*1.0 > mean) arr[i][j]--;
                            else if (arr[i][j] * 1.0 < mean) arr[i][j]++;
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (int []ar : arr) {
            for (int a : ar) {
                ans+=a;
            }
        }
        System.out.println(ans);
        br.close();
    }
}