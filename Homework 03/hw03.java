import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class hw03 {
    private static int getMaxJobs(String[] jobs) {
        int[][] jobTimes = new int[jobs.length][2];

        for (int i = 0; i < jobs.length; i++) {
            String[] parts = jobs[i].trim().split(" ");
            jobTimes[i][0] = Integer.parseInt(parts[0]);
            jobTimes[i][1] = Integer.parseInt(parts[1]);
        }

        Arrays.sort(jobTimes, (job1, job2) -> Integer.compare(job1[1], job2[1]));

        int count = 1;
        int lastJobIndex = 0;

        for (int i = 1; i < jobTimes.length; i++) {
            if (jobTimes[lastJobIndex][1] <= jobTimes[i][0]) {
                count++;
                lastJobIndex = i;
            }
        }

        return count;
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int numTestCases = Integer.parseInt(scan.nextLine().trim());
        ArrayList<String[]> jobLists = new ArrayList<>();

        for (int i = 0; i < numTestCases; i++) {
            int numJobs = Integer.parseInt(scan.nextLine().trim());
            String[] jobs = new String[numJobs];
            for (int j = 0; j < numJobs; j++) {
                jobs[j] = scan.nextLine().trim();
            }
            jobLists.add(jobs);
        }

        scan.close();

        for (String[] jobs : jobLists) {
            System.out.println(getMaxJobs(jobs));
        }
    }
}