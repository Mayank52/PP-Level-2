import java.io.*;
import java.util.*;

//Questions on Pepcoding site
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

    // Permutations - Words - 1
    public static void generateWords(int cs, int ts, HashMap<Character, Integer> fmap, String asf) {
        // write your code here
        if (cs == ts + 1) {
            System.out.println(asf);
            return;
        }
        for (char ch : fmap.keySet()) {
            if (fmap.get(ch) > 0) {
                fmap.put(ch, fmap.get(ch) - 1);
                generateWords(cs + 1, ts, fmap, asf + ch);
                fmap.put(ch, fmap.get(ch) + 1);
            }
        }
    }

    // Permutations - Words - 2
    public static void generateWords(int cc, String str, Character[] spots, HashMap<Character, Integer> lastOccurence) {
        if (cc == str.length()) {
            for (char ch : spots) {
                System.out.print(ch);
            }

            System.out.println();
            return;
        }

        char ch = str.charAt(cc);
        int lastOcc = lastOccurence.get(ch);

        for (int i = lastOcc + 1; i < str.length(); i++) {
            if (spots[i] == null) {
                spots[i] = ch;
                lastOccurence.put(ch, i);
                generateWords(cc + 1, str, spots, lastOccurence);
                spots[i] = null;
                lastOccurence.put(ch, lastOcc);
            }
        }
    }

    // Nknights Combinations - 2d As 1d - Knight Chooses
    public static boolean IsKnightSafe(boolean[][] chess, int i, int j) {
        // write your code here
        int[][] dir = { { -2, -1 }, { -2, 1 }, { 2, -1 }, { 2, 1 }, { -1, -2 }, { -1, 2 }, { 1, 2 }, { 1, -2 } };

        for (int d = 0; d < dir.length; d++) {
            int x = i + dir[d][0];
            int y = j + dir[d][1];

            if (x >= 0 && y >= 0 && x < chess.length && y < chess[0].length && chess[x][y])
                return false;
        }

        return true;
    }

    public static void nknights(int kpsf, int tk, boolean[][] chess, int lcno) {
        if (kpsf == tk) {
            for (int row = 0; row < chess.length; row++) {
                for (int col = 0; col < chess.length; col++) {
                    System.out.print(chess[row][col] ? "k\t" : "-\t");
                }
                System.out.println();
            }
            System.out.println();
            return;
        }

        for (int i = lcno + 1; i < chess.length * chess.length; i++) {
            int row = i / chess.length;
            int col = i % chess.length;

            if (chess[row][col] == false && IsKnightSafe(chess, row, col)) {
                chess[row][col] = true;
                nknights(kpsf + 1, tk, chess, row * chess.length + col);
                chess[row][col] = false;
            }
        }
    }

    // Words - K Selection - 1
    public static void solve() {
        Scanner scn = new Scanner(System.in);
        String str = scn.nextLine();
        int k = scn.nextInt();

        HashSet<Character> unique = new HashSet<>();
        String ustr = "";
        for (char ch : str.toCharArray()) {
            if (unique.contains(ch) == false) {
                unique.add(ch);
                ustr += ch;
            }
        }

        combination(0, ustr, 0, k, "");
    }

    public static void combination(int i, String ustr, int ssf, int ts, String asf) {
        if (ssf == ts) {
            System.out.println(asf);
            return;
        }

        for (int idx = i; idx < ustr.length(); idx++) {
            combination(idx + 1, ustr, ssf + 1, ts, asf + ustr.charAt(idx));
        }

    }

    // Words - K Selection - 2
    public static void combination(int i, String ustr, int ssf, int ts, String asf) {
        if (ssf == ts) {
            System.out.println(asf);
            return;
        }

        if (i == ustr.length())
            return;

        combination(i + 1, ustr, ssf + 1, ts, asf + ustr.charAt(i));
        combination(i + 1, ustr, ssf, ts, asf);

    }

    // Words - K Length Words - 1
    public static void solve() {
        Scanner scn = new Scanner(System.in);
        String str = scn.nextLine();
        int k = scn.nextInt();

        HashSet<Character> unique = new HashSet<>();
        String ustr = "";
        for (char ch : str.toCharArray()) {
            if (unique.contains(ch) == false) {
                unique.add(ch);
                ustr += ch;
            }
        }

        Character[] vis = new Character[k];
        combination(0, ustr, 0, k, vis);
    }

    public static void combination(int idx, String ustr, int ssf, int ts, Character[] vis) {
        if (idx == ustr.length()) {
            if (ssf == ts) {
                for (int i = 0; i < vis.length; i++)
                    System.out.print(vis[i]);
                System.out.println();
            }
            return;
        }

        char ch = ustr.charAt(idx);

        for (int i = 0; i < vis.length; i++) {
            if (vis[i] == null) {
                vis[i] = ch;
                combination(idx + 1, ustr, ssf + 1, ts, vis);
                vis[i] = null;
            }
        }

        combination(idx + 1, ustr, ssf, ts, vis);
    }

    // Words - K Length Words - 2
    public static void solve() {
        Scanner scn = new Scanner(System.in);
        String str = scn.nextLine();
        int k = scn.nextInt();

        HashSet<Character> unique = new HashSet<>();
        String ustr = "";
        for (char ch : str.toCharArray()) {
            if (unique.contains(ch) == false) {
                unique.add(ch);
                ustr += ch;
            }
        }

        boolean[] vis = new boolean[ustr.length()];
        combination(ustr, 0, k, "", vis);
    }

    public static void combination(String ustr, int ssf, int ts, String asf, boolean[] vis) {
        if (ssf == ts) {
            System.out.println(asf);
            return;
        }

        for (int i = 0; i < ustr.length(); i++) {
            if (vis[i] == false) {
                vis[i] = true;
                combination(ustr, ssf + 1, ts, asf + ustr.charAt(i), vis);
                vis[i] = false;
            }
        }
    }

    // Solve Sudoku
    public static void display(int[][] board) {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static boolean isValid(int[][] board, int i, int j, int n) {
        // row
        for (int c = 0; c < board.length; c++) {
            if (board[i][c] == n)
                return false;
        }

        // col
        for (int r = 0; r < board.length; r++) {
            if (board[r][j] == n)
                return false;
        }

        // 3X3 grid
        int x = i / 3 * 3;
        int y = j / 3 * 3;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (board[x + r][y + c] == n)
                    return false;
            }
        }
        return true;
    }

    public static void solveSudoku(int[][] board, int i, int j) {
        if (i == board.length) {
            display(board);
            return;
        }

        // Get the next row, col
        int r, c;
        if (j == board.length - 1) {
            r = i + 1;
            c = 0;
        } else {
            r = i;
            c = j + 1;
        }

        // if not empty go to next cell
        if (board[i][j] != 0) {
            solveSudoku(board, r, c);
        }
        // else try all 1 - 9 in that cell and call for next cell
        else {
            for (int n = 1; n <= 9; n++) {
                if (isValid(board, i, j, n)) {
                    board[i][j] = n;
                    solveSudoku(board, r, c);
                    board[i][j] = 0;
                }
            }
        }
    }

    // Magnets
    public static boolean isValid(char[][] ans, int row, int col, char sign, int[] top, int[] left, int[] right,
            int[] bottom) {
        // check count in T,B,L,R
        if (sign == '+') {
            if (top[col] == 0 || left[row] == 0)
                return false;
        } else {
            if (bottom[col] == 0 || right[row] == 0)
                return false;
        }

        // check adjacent signs
        int[][] dir = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
        for (int d = 0; d < 4; d++) {
            int x = row + dir[d][0];
            int y = col + dir[d][1];

            if (x >= 0 && y >= 0 && x < ans.length && y < ans[0].length) {
                if (sign == '+' || sign == '-') {
                    if (ans[x][y] == sign)
                        return false;
                }
            }
        }

        return true;
    }

    public static void updateCount(int[] top, int[] left, int[] right, int[] bottom, int row, int col, char sign,
            int change) {
        if (sign == '+') {
            if (top[col] != -1)
                top[col] += change;
            if (left[row] != -1)
                left[row] += change;
        } else {
            if (bottom[col] != -1)
                bottom[col] += change;
            if (right[row] != -1)
                right[row] += change;
        }
    }

    public static boolean solution(char[][] arr, int[] top, int[] left, int[] right, int[] bottom, char[][] ans,
            int row, int col) {
        // write your code here
        if (row == arr.length)
            return true;

        int nextRow, nextCol;
        if (col == arr[0].length - 1) {
            nextRow = row + 1;
            nextCol = 0;
        } else {
            nextRow = row;
            nextCol = col + 1;
        }

        if (ans[row][col] == '#') {
            //LR
           if(arr[row][col]=='L'){
               if(isValid())
           }

        }

        return false;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int nboxes = Integer.parseInt(br.readLine());
        int ritems = Integer.parseInt(br.readLine());
        combinations(new int[nboxes], 1, ritems, -1);
    }

}