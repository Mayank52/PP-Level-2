import java.io.*;
import java.util.*;

public class Strings {

    // Longest Prefix that is also a Suffix (LPS)
    // 1392. Longest Happy Prefix
    /*
        Approach: O(n), O(n)
        A string is a proper prefix, if it is also a suffix
        Eg: aabaacaabaad
        Here, lps is aabaa, as it a prefix as well as a suffix
        We see the suffix from left. Like in 'leetcodeleet', lps is 'leet'
    */
    public String longestPrefix(String str) {
        int n = str.length();
        int[] lps = new int[n];
        int len = 0, i = 1;

        while (i < n) {
            if (str.charAt(i) == str.charAt(len)) {
                len++;
                lps[i] = len;
                i++;

            } else {
                if (len > 0) {
                    len = lps[len - 1];
                } else
                    i++;
            }
        }

        String res = str.substring(0, len);

        return res;

    }

    // Kmp Pattern Searching
    /*
     * Approach: O(m + n), O(n)
     * Use the LPS Algo. 
     * Make the string = pattern#text.
     * Whenever the len is equal to pattern length, we have found an occurence of the pattern
     * To get its start index, we have to do start index = i - (pat.length() + 1) - pat.length() + 1
     * Where, (pat.length() + 1) = (length of the pattern + #) we added to txt
     * and - pat.length() + 1 to get the start index from the last index
     */
    public static void lps(String txt, String pat) {
        String str = pat + "#" + txt;
        int n = str.length();
        int[] lps = new int[n];
        int len = 0, i = 1;

        while (i < n) {
            if (str.charAt(i) == str.charAt(len)) {
                len++;
                lps[i] = len;

                if (len == pat.length()) {
                    int startIdx = i - (pat.length() + 1) - pat.length() + 1;
                    System.out.println(startIdx);
                }

                i++;

            } else {
                if (len > 0) {
                    len = lps[len - 1];
                } else
                    i++;
            }
        }
    }
    public static void solution(String txt, String pat) {
        // write your code here
        lps(txt, pat);
        System.out.println();
    }

    

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        String s1 = scn.nextLine();
        String s2 = scn.nextLine();
        solution(s1, s2);
    }

}