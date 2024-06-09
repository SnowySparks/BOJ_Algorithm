import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        // Input Setting
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        StringBuilder pr = new StringBuilder();
        // 자료구조
        Deque<Integer> dq = new LinkedList<>();
        int cmd;
        // 시행
        int n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; ++i) {
            st = new StringTokenizer(br.readLine());
            cmd = Integer.parseInt(st.nextToken());

            switch (cmd) {
                case 1:
                    dq.addFirst(Integer.parseInt(st.nextToken()));
                    break;
                case 2:
                    dq.addLast(Integer.parseInt(st.nextToken()));
                    break;
                case 3:
                    pr.append( dq.isEmpty() ? -1 : dq.pollFirst()).append("\n");
                    break;
                case 4:
                    pr.append( dq.isEmpty() ? -1 : dq.pollLast()).append("\n");
                    break;
                case 5:
                    pr.append(dq.size()).append("\n");
                    break;
                case 6:
                    pr.append( dq.isEmpty() ? 1 : 0).append("\n");
                    break;
                case 7:
                    pr.append(dq.isEmpty() ? -1 : dq.peekFirst()).append("\n");
                    break;
                case 8:
                    pr.append(dq.isEmpty() ? -1 : dq.peekLast()).append("\n");
                    break;
                default:
                    break;
            }
        }
        System.out.println(pr.toString());
        br.close();
    }
}
