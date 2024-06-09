import java.io.BufferedReader;
// import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
// import java.io.OutputStreamWriter;
import java.util.*;

public class Main {

    public static long hash(String s) {
        return 0L;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
        HashSet<String> table = new HashSet<>();
        table.add("ChongChong");

        int n = Integer.parseInt(br.readLine()); // n 입력
        for (int i = 0; i < n; ++i) {
            st = new StringTokenizer(br.readLine());
            String a = st.nextToken();
            String b = st.nextToken();

            if (table.contains(a) || table.contains(b)) {
                table.add(a);
                table.add(b);
            }
        }
        // bw.write(Integer.toString(table.size()));
        System.out.print(table.size());
        // bw.close();
        br.close();
    }
}
