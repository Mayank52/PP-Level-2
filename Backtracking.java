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

    // Queens Combinations - 2d As 2d - Queen Chooses
    public static void queensCombinations(int qpsf, int tq, boolean[][] chess, int i, int j) {
        if (qpsf == tq) {
            for (int row = 0; row < tq; row++) {
                for (int col = 0; col < tq; col++) {
                    if (chess[row][col])
                        System.out.print("q\t");
                    else
                        System.out.print("-\t");
                }
                System.out.println();
            }
            System.out.println();

            return;
        }

        // start column from next column of the first row of current step
        // otherwise column starts from 0
        // because we need to iterate on elements after the last element {i,j}
        for (int row = i; row < tq; row++) {
            for (int col = (row == i) ? (j + 1) : 0; col < tq; col++) {
                if (!chess[row][col]) {
                    chess[row][col] = true;
                    queensCombinations(qpsf + 1, tq, chess, row, col);
                    chess[row][col] = false;
                }
            }
        }
    }

    // Queens Permutations - 2d As 2d - Queen Chooses
    public static void queensPermutations(int qpsf, int tq, int[][] chess) {
        if (qpsf == tq) {
            for (int row = 0; row < tq; row++) {
                for (int col = 0; col < tq; col++) {
                    if (chess[row][col] != 0)
                        System.out.print("q" + chess[row][col] + "\t");
                    else
                        System.out.print("-\t");
                }
                System.out.println();
            }
            System.out.println();

            return;
        }

        for (int row = 0; row < tq; row++) {
            for (int col = 0; col < tq; col++) {
                if (chess[row][col] == 0) {
                    chess[row][col] = qpsf + 1;
                    queensPermutations(qpsf + 1, tq, chess);
                    chess[row][col] = 0;
                }
            }
        }
    }

    // Queens Combinations - 2d As 1d - Queen Chooses
    public static void queensCombinations(int qpsf, int tq, boolean[][] chess, int lcno) {
        if (qpsf == tq) {
            for (int row = 0; row < tq; row++) {
                for (int col = 0; col < tq; col++) {
                    if (chess[row][col])
                        System.out.print("q\t");
                    else
                        System.out.print("-\t");
                }
                System.out.println();
            }
            System.out.println();

            return;
        }

        int i = lcno / tq;
        int j = lcno % tq;
        for (int row = i; row < tq; row++) {
            for (int col = (row == i) ? (j + 1) : 0; col < tq; col++) {
                if (!chess[row][col]) {
                    chess[row][col] = true;
                    queensCombinations(qpsf + 1, tq, chess, row * tq + col);
                    chess[row][col] = false;
                }
            }
        }
    }

    // Nqueens Combinations - 2d As 1d - Queen Chooses
    public static boolean IsQueenSafe(boolean[][] chess, int row, int col) {
        // row
        for (int i = 0; i < col; i++) {
            if (chess[row][i])
                return false;
        }

        // col
        for (int i = 0; i < row; i++)
            if (chess[i][col])
                return false;

        // diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (chess[i][j])
                return false;

        // anti diagonal
        for (int i = row, j = col; i >= 0 && j < chess[0].length; i--, j++)
            if (chess[i][j])
                return false;

        return true;
    }

    // Nqueens Permutations - 2d As 1d - Queen Chooses
    public static boolean IsQueenSafe(int[][] chess, int row, int col) {
        // row
        for (int i = 0; i < chess.length; i++) {
            if (chess[row][i] != 0)
                return false;
        }

        // col
        for (int i = 0; i < chess.length; i++)
            if (chess[i][col] != 0)
                return false;

        // diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (chess[i][j] != 0)
                return false;
        for (int i = row, j = col; i < chess.length && j < chess[0].length; i++, j++)
            if (chess[i][j] != 0)
                return false;

        // anti diagonal
        for (int i = row, j = col; i >= 0 && j < chess[0].length; i--, j++)
            if (chess[i][j] != 0)
                return false;
        for (int i = row, j = col; j >= 0 && i < chess.length; i++, j--)
            if (chess[i][j] != 0)
                return false;

        return true;
    }

    public static void nqueens(int qpsf, int tq, int[][] chess) {
        // write your code here
        if (qpsf == tq) {
            for (int i = 0; i < chess.length; i++) {
                for (int j = 0; j < chess[0].length; j++) {
                    if (chess[i][j] != 0)
                        System.out.print("q" + chess[i][j] + "\t");
                    else
                        System.out.print("-" + "\t");
                }
                System.out.println();
            }
            System.out.println();

            return;
        }

        for (int i = 0; i < chess.length * chess.length; i++) {
            int row = i / chess.length;
            int col = i % chess.length;

            if (chess[row][col] == 0 && IsQueenSafe(chess, row, col)) {
                chess[row][col] = qpsf + 1;
                nqueens(qpsf + 1, tq, chess);
                chess[row][col] = 0;
            }
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int nboxes = Integer.parseInt(br.readLine());
        int ritems = Integer.parseInt(br.readLine());
        combinations(new int[nboxes], 1, ritems, -1);
    }

}