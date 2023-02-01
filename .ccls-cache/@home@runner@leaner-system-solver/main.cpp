//https://en.wikipedia.org/wiki/Gaussian_elimination

#include <bits/stdc++.h>
#include <boost/rational.hpp>

using namespace std;
using namespace boost;

#define all(c) (c).begin(), (c).end()

using Q = rational<int>;
using M = vector<vector<Q>>;

istream& operator>> (istream& in, Q& r)
{
    int n, d = 1;
    in >> n;
    char ch = in.peek();
    if (ch == '/') cin >> ch >> d;
    r = Q(n, d);
    return in;
}

ostream& operator<< (ostream& out, const Q& r)
{
    out << r.numerator();
    if (r.denominator() != 1) out << '/' << r.denominator();
    return out;
}
    
istream& operator>> (istream& in, M& m)
{
    int n; in >> n;
    m.resize(n);
    for (auto& r : m)
    {
        //copy_n(istream_iterator<Q>(in), n+1, back_inserter(r));
        r.resize(n+1); // input additional column for the augmented matrix (A|b) of size [n][n+1]
        for (auto& e : r)
        {
            in >> e;
        }
    }
    return in;
}

ostream& operator<< (ostream& out, const M& m)
{
    for (const auto& r : m)
    {
        //copy(all(r), ostream_iterator<Q>(out, " "));
        for (const auto& e : r)
            out << e << ' ';
        out << '\n';
    }
    return out;
}

void gausian_elimination(M& m)
{
    int n = m.size();
    for (int i = 0; i < n-1; ++i)
    {
        for (int j = i+1; j < n; ++j)
        {
            Q ratio = m[j][i] / m[i][i];
            for (int k = i; k < n+1; ++k)
            {
                m[j][k] -= (ratio * m[i][k]);
            }
        }
        cout << m << '\n';
    }
}

void back_substitution(M& m)
{
    int n = m.size();
    for (int i = n-1; i >=0; --i)
    {
        for (int j = i+1; j < n; ++j)
        {
            m[i][n] -= m[i][j]*m[j][n];
            m[i][j] = 0;
        }
        m[i][n] /= m[i][i];
        m[i][i] = 1;
        cout << m << '\n';
    }
}

// soves Ax=b matric equasions
void solve(M& m)
{
    gausian_elimination(m);
    back_substitution(m);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream in("input");
    M m; in >> m;
    cout << m << '\n';

    solve(m);

    return 0;
}
