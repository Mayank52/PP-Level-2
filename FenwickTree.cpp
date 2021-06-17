#include <bits/stdc++.h>

using namespace std;

vector<long long> farr;

long long prefixSum(int idx)
{
    long long sum = 0;
    while (idx > 0)
    {
        sum += farr[idx];
        idx -= (idx & -idx);
    }

    return sum;
}

long long query(int l, int r)
{
    return prefixSum(r) - prefixSum(l - 1);
}

void update(int idx, int delta)
{
    while (idx < farr.size())
    {
        farr[idx] += delta;
        idx += (idx & -idx);
    }
}

void construct(vector<long long> &arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        update(i, arr[i]);
    }
}

void fenwickTree(vector<long long> &arr)
{
    int n = arr.size();

    farr.resize(n);

    construct(arr);

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

            long long ans = query(l, r);
            cout << ans << endl;
        }
        else
        {
            int idx, delta;
            cin >> idx >> delta;

            update(idx, delta);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> arr(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    fenwickTree(arr);

    return 0;
}