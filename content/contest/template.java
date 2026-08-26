import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main {
    static BufferedReader br;
    static PrintWriter pw;
    static StringTokenizer st;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new FileReader("datos.txt"));
        pw = new PrintWriter("salida.txt");
        solve();
        pw.close();
    }

    static void solve() throws IOException {
        // Your code here
        BigInteger a = nextBigInteger();
        BigInteger b = nextBigInteger();
        pw.println(a.add(b));
    }

    static String next() throws IOException {
        while (st == null || !st.hasMoreTokens())
            st = new StringTokenizer(br.readLine());
        return st.nextToken();
    }
    
    static BigInteger nextBigInteger() throws IOException {
        return new BigInteger(next());
    }

    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    static long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

    static String nextLine() throws IOException {
        return br.readLine();
    }
}