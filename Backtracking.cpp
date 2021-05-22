#include <bits/stdc++.h>
using namespace std;

//Permutations 1

// Combinations 2
  public static void combinations(int[] boxes, int ci, int ti, int lb){
    // write your code here
    if(ci == ti+1){
        for(int i = 0; i<boxes.length; i++){
            if(boxes[i] == 1) System.out.print('i');
            else System.out.print('-');
        }
        System.out.println();
    }
    
    for(int i = 0; i<boxes.length; i++){
        if(boxes[i] == 0){
            boxes[i] = 1;
            combinations(boxes, ci+1, ti, lb+1);
            boxes[i] = 0;
        }
    }
  }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}