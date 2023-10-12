import java.io.*;

public class hw04 {
    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        for (int i = 0; i < T; i++) {
            int cacheSize = Integer.parseInt(br.readLine());
            int[] cache = new int[cacheSize];
            
            for (int j = 0; j < cacheSize; j++) {
                cache[j] = -1;
            }

            int requestCount = Integer.parseInt(br.readLine());
            int[] requests = new int[requestCount];
            String[] requestTokens = br.readLine().split(" ");

            for (int j = 0; j < requestCount; j++) {
                requests[j] = Integer.parseInt(requestTokens[j]);
            }

            bw.write(countPageFaults(cache, requests) + "\n");
        }

        bw.flush();
        br.close();
        bw.close();
    }

    private static boolean isInCache(int[] cache, int page) {
        for (int val : cache) {
            if (val == page) {
                return true;
            }
        }
        return false;
    }

    private static int farthestFutureUse(int[] cache, int[] pages, int start) {
        int maxDistance = -1;
        int res = -1;

        for (int i = 0; i < cache.length; i++) {
            int j;

            for (j = start; j < pages.length; j++) {
                if (cache[i] == pages[j]) {
                    break;
                }
            }

            if (j == pages.length) {
                return i;
            }
            if (j > maxDistance) {
                maxDistance = j;
                res = i;
            }
        }

        return res;
    }

    private static int countPageFaults(int[] cache, int[] pages) {
        int pageFaults = 0;
        int filledSlots = 0;

        for (int pageIndex = 0; pageIndex < pages.length; pageIndex++) {
            if (!isInCache(cache, pages[pageIndex])) {
                pageFaults++;

                if (filledSlots < cache.length) {
                    cache[filledSlots++] = pages[pageIndex];
                } else {
                    int indexToReplace = farthestFutureUse(cache, pages, pageIndex + 1);
                    cache[indexToReplace] = pages[pageIndex];
                }
            }
        }

        return pageFaults;
    }
}
