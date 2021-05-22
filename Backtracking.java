import java.io.*;
import java.util.*;

public class Backtracking {
    // Permutations 1
    public static void permutations(int[] boxes, int ci, int ti) {
        // write your code here
        if (ci == ti + 1) {
            for (int i = 0; i < boxes.length; i++) {
                System.out.print(boxes[i]);
            }
            System.out.println();
        }

        for (int i = 0; i < boxes.length; i++) {
            if (boxes[i] == 0) {
                boxes[i] = ci;
                permutations(boxes, ci + 1, ti);
                boxes[i] = 0;
            }
        }
    }

    // Combinations 2
    public static void combinations(int[] boxes, int ci, int ti, int lb) {
        if (ci > ti) {
            for (int i = 0; i < boxes.length; i++) {
                if (boxes[i] == 1)
                    System.out.print('i');
                else
                    System.out.print('-');
            }

            System.out.println();

            return;
        }

        for (int i = lb + 1; i < boxes.length; i++) {
            if (boxes[i] == 0) {
                boxes[i] = 1;
                combinations(boxes, ci + 1, ti, i);
                boxes[i] = 0;
            }
        }
    }

    // Combinations - 1
    public static void combinations(int cb, int tb, int ssf, int ts, String asf) {
        if (cb == tb + 1) {
            if (ssf == ts)
                System.out.println(asf);

            return;
        }

        // include in box
        combinations(cb + 1, tb, ssf + 1, ts, asf + 'i');

        // leave box empty
        combinations(cb + 1, tb, ssf, ts, asf + '-');
    }

    // Permutations - 2
    public static void permutations(int cb, int tb, int[] items, int ssf, int ts, String asf) {
        // write your code here
        if (cb == tb + 1) {
            if (ssf == ts)
                System.out.println(asf);

            return;
        }

        // include in box
        for (int i = 0; i < ts; i++) {
            if (items[i] == 0) {
                items[i] = 1;
                permutations(cb + 1, tb, items, ssf + 1, ts, asf + (i + 1));
                items[i] = 0;
            }
        }

        // leave box empty
        permutations(cb + 1, tb, items, ssf, ts, asf + "0");
    }

    // Queens Combinations - 2d As 2d - Box Chooses
    public static void queensCombinations(int qpsf, int tq, int row, int col, String asf) {
        // write your code here
        if (row == tq) {
            if (qpsf == tq)
                System.out.println(asf);
            return;
        }

        // if not last column, include/exclude in next column
        if (col + 1 < tq) {
            queensCombinations(qpsf + 1, tq, row, col + 1, asf + 'q');
            queensCombinations(qpsf, tq, row, col + 1, asf + '-');

        }

        // if last column, move to next row
        else {
            queensCombinations(qpsf + 1, tq, row + 1, 0, asf + "q\n");
            queensCombinations(qpsf, tq, row + 1, 0, asf + "-\n");
        }

    }

    // Queens Permutations - 2d As 2d - Box Chooses
    public static void queensPermutations(int qpsf, int tq, int row, int col, String asf, boolean[] queens) {
        if (row == tq) {
            if (qpsf == tq) {
                System.out.println(asf);
                System.out.println();
            }
            return;
        }

        char smallAns;
        if (col + 1 < tq) {
            col++;
            smallAns = '\t';
        } else {
            row++;
            col = 0;
            smallAns = '\n';
        }

        for (int i = 0; i < tq; i++) {
            if (!queens[i]) {
                queens[i] = true;
                queensPermutations(qpsf + 1, tq, row, col, asf + 'q' + (i + 1) + smallAns, queens);
                queens[i] = false;
            }
        }

        queensPermutations(qpsf, tq, row, col, asf + '-' + smallAns, queens);
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int nboxes = Integer.parseInt(br.readLine());
        int ritems = Integer.parseInt(br.readLine());
        combinations(new int[nboxes], 1, ritems, -1);
    }

}