#include <bits/stdc++.h>

using namespace std;

long long prefixSum(vector<long long> &farr, int idx)
{
    long long sum = 0;
    while (idx > 0)
    {
        sum += farr[idx];
        idx -= (idx & -idx);
    }
    
    return sum;
}

long long query(vector<long long> &farr, int l, int r){
    return prefixSum(farr, r) - prefixSum(farr, l-1);
}

void update(vector<long long> &farr, int idx, int delta)
{
    while (idx < farr.size())
    {
        farr[idx] += delta;
        idx += (idx & -idx);
    }
}

int construct(vector<long long> &arr, vector<long long> &farr)
{
    int n = arr.size();

    for (int i = 1; i <= n; i++)
    {
        update(farr, i, arr[i]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> arr(n + 1), farr(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    
    construct(arr, farr);

    int q;
    cin >> q;
    while (q-- > 0)
    {
        char ch;
        cin >> ch;

        if (ch == 'q')
        {
            int l, r;
            cin >> l >> r;

            long long ans = query(farr, l, r);
            cout<<ans<<endl;
        }
        else
        {
            int idx, delta;
            cin >> idx >> delta;

            update(farr, idx, delta);
        }
    }

    return 0;
}