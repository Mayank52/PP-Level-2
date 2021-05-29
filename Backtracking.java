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

    // Coin Change - Combinations - 1
    public static void coinChange(int i, int[] coins, int amtsf, int tamt, String asf) {
        // write your code here
        if (amtsf == tamt) {
            System.out.println(asf + ".");
            return;
        }
        if (i == coins.length)
            return;

        if (amtsf + coins[i] <= tamt)
            coinChange(i + 1, coins, amtsf + coins[i], tamt, asf + coins[i] + "-");
        coinChange(i + 1, coins, amtsf, tamt, asf);

    }

    // Coin Change - Combinations - 2
    public static void coinChange(int i, int[] coins, int amtsf, int tamt, String asf) {
        // write your code here
        if (amtsf == tamt) {
            System.out.println(asf + ".");
            return;
        }
        if (i == coins.length)
            return;

        if (amtsf + coins[i] <= tamt) {
            coinChange(i, coins, amtsf + coins[i], tamt, asf + coins[i] + "-");
        }
        coinChange(i + 1, coins, amtsf, tamt, asf);
    }

    // Coin Change - Permutations - 1
    public static void coinChange(int[] coins, int amtsf, int tamt, String asf, boolean[] used) {
        // write your code here
        if (amtsf == tamt) {
            System.out.println(asf + ".");
            return;
        }

        for (int i = 0; i < coins.length; i++) {
            if (!used[i] && amtsf + coins[i] <= tamt) {
                used[i] = true;
                coinChange(coins, amtsf + coins[i], tamt, asf + coins[i] + "-", used);
                used[i] = false;
            }
        }
    }

    // Coin Change - Permutations - 2
    public static void coinChange(int[] coins, int amtsf, int tamt, String asf) {
        // write your code here
        if (amtsf == tamt) {
            System.out.println(asf + ".");
            return;
        }

        for (int i = 0; i < coins.length; i++) {
            if (amtsf + coins[i] <= tamt) {
                coinChange(coins, amtsf + coins[i], tamt, asf + coins[i] + "-");
            }
        }
    }

    // Magnets
    public static boolean solution(char[][] arr, int[] top, int[] left, int[] right, int[] bottom, char[][] ans,
            int row, int col) {

        if (row == arr.length) {
            if (isvalid(ans, top, left, right, bottom)) {
                print(ans);
                return true;
            }
            return false;
        }

        int nr = row;
        int nc = col;

        if (col == arr[0].length - 1) {
            nr++;
            nc = 0;
        } else {
            nc++;
        }

        if (ans[row][col] == 'X') {
            if (col + 1 < arr[0].length && arr[row][col] == 'L' && arr[row][col + 1] == 'R') {
                if (issafe(ans, top, left, right, bottom, row, col, '+')
                        && issafe(ans, top, left, right, bottom, row, col + 1, '-')) {
                    ans[row][col] = '+';
                    ans[row][col + 1] = '-';

                    boolean flag1 = solution(arr, top, left, right, bottom, ans, nr, nc);
                    if (flag1 == true) {
                        return true;
                    }

                    ans[row][col] = 'X';
                    ans[row][col + 1] = 'X';
                }

                if (issafe(ans, top, left, right, bottom, row, col, '-')
                        && issafe(ans, top, left, right, bottom, row, col + 1, '+')) {
                    ans[row][col] = '-';
                    ans[row][col + 1] = '+';
                    boolean flag2 = solution(arr, top, left, right, bottom, ans, nr, nc);
                    if (flag2 == true) {
                        return true;
                    }

                    ans[row][col] = 'X';
                    ans[row][col + 1] = 'X';

                }
            }

            if (row + 1 < arr.length && arr[row][col] == 'T' && arr[row + 1][col] == 'B') {
                if (issafe(ans, top, left, right, bottom, row, col, '+')
                        && issafe(ans, top, left, right, bottom, row + 1, col, '-')) {
                    ans[row][col] = '+';
                    ans[row + 1][col] = '-';

                    boolean flag1 = solution(arr, top, left, right, bottom, ans, nr, nc);
                    if (flag1 == true) {
                        return true;
                    }

                    ans[row][col] = 'X';
                    ans[row + 1][col] = 'X';
                }

                if (issafe(ans, top, left, right, bottom, row, col, '-')
                        && issafe(ans, top, left, right, bottom, row + 1, col, '+')) {
                    ans[row][col] = '-';
                    ans[row + 1][col] = '+';
                    boolean flag2 = solution(arr, top, left, right, bottom, ans, nr, nc);
                    if (flag2 == true) {
                        return true;
                    }
                    ans[row][col] = 'X';
                    ans[row + 1][col] = 'X';
                }
            }
        }

        boolean flag3 = solution(arr, top, left, right, bottom, ans, nr, nc);
        if (flag3 == true) {
            return true;
        }

        return false;
    }

    private static boolean isvalid(char[][] ans, int[] top, int[] left, int[] right, int[] bottom) {
        for (int i = 0; i < ans.length; i++) {
            if (left[i] != -1 && rowcount(ans, i, 0, '+') != left[i]) {
                return false;
            }
        }

        for (int i = 0; i < ans.length; i++) {
            if (right[i] != -1 && rowcount(ans, i, 0, '-') != right[i]) {
                return false;
            }
        }

        for (int i = 0; i < ans[0].length; i++) {
            if (top[i] != -1 && colcount(ans, 0, i, '+') != top[i]) {
                return false;
            }
        }
        for (int i = 0; i < ans[0].length; i++) {
            if (bottom[i] != -1 && colcount(ans, 0, i, '-') != bottom[i]) {
                return false;
            }
        }

        return true;
    }

    private static boolean issafe(char[][] ans, int[] top, int[] left, int[] right, int[] bottom, int row, int col,
            char ch) {
        if (ans[row][col] != 'X') {
            return false;
        }
        if (row - 1 >= 0 && ans[row - 1][col] == ch) {
            return false;
        }
        if (col - 1 >= 0 && ans[row][col - 1] == ch) {
            return false;
        }
        if (row + 1 < ans.length && ans[row + 1][col] == ch) {
            return false;
        }
        if (col + 1 < ans[0].length && ans[row][col + 1] == ch) {
            return false;
        }
        int rowchcount = rowcount(ans, row, col, ch);
        int colchcount = colcount(ans, row, col, ch);
        if (ch == '+') {
            if (top[col] != -1 && colchcount == top[col]) {
                return false;
            }

            if (left[row] != -1 && rowchcount == left[row]) {
                return false;
            }
        } else {
            if (bottom[col] != -1 && colchcount == bottom[col]) {
                return false;
            }

            if (right[row] != -1 && rowchcount == right[row]) {
                return false;
            }
        }

        return true;
    }

    public static int rowcount(char[][] ans, int row, int col, char ch) {

        int count = 0;
        for (int j = 0; j < ans[0].length; j++) {
            if (ans[row][j] == ch) {
                count++;
            }
        }
        return count;
    }

    public static int colcount(char[][] ans, int row, int col, char ch) {

        int count = 0;
        for (int i = 0; i < ans.length; i++) {
            if (ans[i][col] == ch) {
                count++;
            }
        }
        return count;
    }

    public static void print(char[][] arr) {
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[0].length; j++) {
                System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void magnets() {
        Scanner scn = new Scanner(System.in);
        int m = scn.nextInt();
        int n = scn.nextInt();
        char[][] arr = new char[m][n];
        for (int i = 0; i < arr.length; i++) {
            String str = scn.next();
            arr[i] = str.toCharArray();
        }
        int[] top = new int[n];
        for (int i = 0; i < n; i++) {
            top[i] = scn.nextInt();
        }
        int[] left = new int[m];
        for (int i = 0; i < m; i++) {
            left[i] = scn.nextInt();
        }
        int[] right = new int[m];
        for (int i = 0; i < m; i++) {
            right[i] = scn.nextInt();
        }
        int[] bottom = new int[n];
        for (int i = 0; i < n; i++) {
            bottom[i] = scn.nextInt();
        }

        // write your code here
        char[][] ans = new char[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans[i][j] = 'X';
            }
        }

        boolean flag = solution(arr, top, left, right, bottom, ans, 0, 0);
        if (flag == false) {
            System.out.println("No Solution");
        }

    }

    // Crossword Puzzle
    public static boolean canPlaceV(char[][] arr, String word, int sr, int sc) {
        // enough cells available
        if (sr + word.length() - 1 >= arr.length)
            return false;

        // either each index empty OR the right character already present
        for (int i = 0; i < word.length(); i++) {
            if (arr[sr + i][sc] != '-' && arr[sr + i][sc] != word.charAt(i))
                return false;
        }

        return true;
    }

    public static boolean canPlaceH(char[][] arr, String word, int sr, int sc) {
        // enough cells available
        if (sc + word.length() - 1 >= arr[0].length)
            return false;

        // either each index empty OR the right character already present
        for (int j = 0; j < word.length(); j++) {
            if (arr[sr][sc + j] != '-' && arr[sr][sc + j] != word.charAt(j))
                return false;
        }

        return true;
    }

    public static void placeV(char[][] arr, String word, int r, int c) {
        for (int i = 0; i < word.length(); i++) {
            arr[i + r][c] = word.charAt(i);
        }
    }

    public static void unplaceV(char[][] arr, String word, int r, int c) {
        for (int i = 0; i < word.length(); i++) {
            arr[i + r][c] = '-';
        }
    }

    public static void placeH(char[][] arr, String word, int r, int c) {
        for (int j = 0; j < word.length(); j++) {
            arr[r][j + c] = word.charAt(j);
        }
    }

    public static void unplaceH(char[][] arr, String word, int r, int c) {
        for (int j = 0; j < word.length(); j++) {
            arr[r][j + c] = '-';
        }
    }

    public static boolean solveCrossword(char[][] arr, String[] words, int idx) {
        // write your code here
        if (idx == words.length) {
            print(arr);
            return true;
        }

        String word = words[idx];

        boolean res = false;

        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[0].length; j++) {
                if (canPlaceH(arr, word, i, j)) {
                    placeH(arr, word, i, j);
                    res = res || solveCrossword(arr, words, idx + 1);
                    unplaceH(arr, word, i, j);
                }
                if (canPlaceV(arr, word, i, j)) {
                    placeV(arr, word, i, j);
                    res = res || solveCrossword(arr, words, idx + 1);
                    unplaceV(arr, word, i, j);
                }
            }
        }

        return res;

    }

    public static void print(char[][] arr) {
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr.length; j++) {
                System.out.print(arr[i][j]);
            }
            System.out.println();
        }

    }

    // Cryptarithmetic
    public static int getNum(String str, HashMap<Character, Integer> charIntMap) {
        int num = 0;
        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            int d = charIntMap.get(ch);
            num = num * 10 + d;
        }

        return num;
    }

    public static boolean isValid(String s1, String s2, String s3, HashMap<Character, Integer> charIntMap) {
        int num1 = getNum(s1, charIntMap);
        int num2 = getNum(s2, charIntMap);
        int num3 = getNum(s3, charIntMap);

        return (num1 + num2) == num3;
    }

    public static void crypto(String unique, int idx, HashMap<Character, Integer> charIntMap, boolean[] usedNumbers,
            String s1, String s2, String s3) {
        if (idx == unique.length()) {
            if (isValid(s1, s2, s3, charIntMap)) {
                char[] charArr = unique.toCharArray();
                Arrays.sort(charArr);
                for (char ch : charArr) {
                    int n = charIntMap.get(ch);
                    System.out.print(ch + "-" + n + " ");
                }
                System.out.println();
            }

            return;
        }

        char ch = unique.charAt(idx);
        for (int i = 0; i < usedNumbers.length; i++) {
            if (!usedNumbers[i]) {
                usedNumbers[i] = true;
                charIntMap.put(ch, i);
                crypto(unique, idx + 1, charIntMap, usedNumbers, s1, s2, s3);
                charIntMap.put(ch, -1);
                usedNumbers[i] = false;
            }
        }
    }

    // Lexicographical Numbers
    public static void lexi(int curr, int n) {
        if (curr > n)
            return;

        System.out.println(curr);
        // for current number append 0-9 to it, and make next call
        for (int i = 0; i < 10; i++)
            lexi(curr * 10 + i, n);
    }

    public static void printLexi(int n) {
        // for 1-9 print all lexicogrpahically number in given range
        for (int i = 1; i < 10; i++)
            lexi(i, n);
    }

    // Largest Number Possible After At Most K Swaps
    static String max;

    public static void findMaximum(String str, int k) {
        if (str.compareTo(max) > 0)
            max = str;

        if (k == 0) {
            return;
        }

        // Brute Force
        for (int i = 0; i < str.length(); i++) {
            for (int j = i + 1; j < str.length(); j++) {
                if (str.charAt(j) > str.charAt(i)) {
                    // swap
                    StringBuilder sb = new StringBuilder(str);
                    sb.setCharAt(i, str.charAt(j));
                    sb.setCharAt(j, str.charAt(i));

                    String newStr = sb.toString();
                    findMaximum(newStr, k - 1);
                }
            }
        }

    }

    // Tug Of War
    static int mindiff = Integer.MAX_VALUE;
    static String ans = "";

    public static void solve(int[] arr, int idx, ArrayList<Integer> set1, ArrayList<Integer> set2, int soset1,
            int soset2) {
        if (idx == arr.length) {
            int diff = Math.abs(soset1 - soset2);
            if (diff < mindiff) {
                mindiff = diff;
                ans = "[";
                for (int i = 0; i < set1.size(); i++) {
                    if (i < set1.size() - 1)
                        ans += set1.get(i) + ", ";
                    else
                        ans += set1.get(i) + "] [";
                }
                for (int i = 0; i < set2.size(); i++) {
                    if (i < set2.size() - 1)
                        ans += set2.get(i) + ", ";
                    else
                        ans += set2.get(i) + "]";
                }
            }
            return;
        }

        int maxSize = (arr.length + 1) / 2;
        if (set1.size() < maxSize) {
            set1.add(arr[idx]);
            solve(arr, idx + 1, set1, set2, soset1 + arr[idx], soset2);
            set1.remove(set1.size() - 1);
        }
        if (set2.size() < maxSize) {
            set2.add(arr[idx]);
            solve(arr, idx + 1, set1, set2, soset1, soset2 + arr[idx]);
            set2.remove(set2.size() - 1);
        }
    }

    // Word Break - I
    public static void wordBreak(String sentence, String ans, HashSet<String> dict, int idx) {
        if (idx == sentence.length()) {
            System.out.println(ans);
            return;
        }

        for (int i = idx; i < sentence.length(); i++) {
            String word = sentence.substring(idx, i + 1);
            if (dict.contains(word)) {
                wordBreak(sentence, ans + word + " ", dict, i + 1);
            }
        }
    }

    public static void wordBreak(String str, String ans, HashSet<String> dict) {
        // write your code here
        wordBreak(str, "", dict, 0);
    }

    // Max Score
    /*
     * For each word if check if it can be included i.e its letters are <= to the
     * letters available Then include it and make call for next word and exclude it
     * and call for next word
     */
    public static int maxScore = Integer.MIN_VALUE;

    public static void solution(String[] words, int[] farr, int[] score, int idx, int ans) {
        // write your code
        if (idx == words.length) {
            maxScore = Math.max(maxScore, ans);
            return;
        }

        // not include current word
        solution(words, farr, score, idx + 1, ans);

        int myScore = 0;
        boolean canInclude = true;
        int[] myFreq = new int[26];
        // find letter freq of current word
        for (char ch : words[idx].toCharArray()) {
            myFreq[ch - 'a']++;
        }

        // check if it is <= available letters
        for (int i = 0; i < 26; i++) {
            if (myFreq[i] > farr[i]) {
                canInclude = false;
                break;
            }
        }

        if (canInclude) {
            // add it to score, and reduce the frequency in letters by current word's letter
            // frequency
            for (char ch : words[idx].toCharArray()) {
                myScore += score[ch - 'a'];
                farr[ch - 'a']--;
            }
            solution(words, farr, score, idx + 1, ans + myScore);
            for (char ch : words[idx].toCharArray()) {
                farr[ch - 'a']++;
            }
        }

    }

    public static int solution(String[] words, int[] farr, int[] score, int idx) {
        // write your code here
        solution(words, farr, score, 0, 0);
        return maxScore;
    }

    // 1255. Maximum Score Words Formed by Letters
    public int maxScore = Integer.MIN_VALUE;

    public void solution(String[] words, int[] farr, int[] score, int idx, int ans) {
        if (idx == words.length) {
            maxScore = Math.max(maxScore, ans);
            return;
        }

        solution(words, farr, score, idx + 1, ans);

        int myScore = 0;
        boolean canInclude = true;
        int[] myFreq = new int[26];
        for (char ch : words[idx].toCharArray()) {
            myFreq[ch - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (myFreq[i] > farr[i]) {
                canInclude = false;
                break;
            }
        }

        if (canInclude) {
            for (char ch : words[idx].toCharArray()) {
                myScore += score[ch - 'a'];
                farr[ch - 'a']--;
            }
            solution(words, farr, score, idx + 1, ans + myScore);
            for (char ch : words[idx].toCharArray()) {
                farr[ch - 'a']++;
            }
        }

    }

    public int maxScoreWords(String[] words, char[] letters, int[] score) {
        maxScore = Integer.MIN_VALUE;
        int[] farr = new int[26];
        for (char ch : letters) {
            farr[ch - 'a']++;
        }
        solution(words, farr, score, 0, 0);
        return maxScore;
    }

    // Pattern Matching(Done in Backtracking.cpp)
    public static void solution(String str, String pattern, HashMap<Character, String> map, int idx) {
        // (Done in Backtracking.cpp)
    }

    public static void main(String[] args) throws Exception {
    }

}