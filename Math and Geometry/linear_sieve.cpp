// linear sieve, used to find all prines from 1...N in O(N) time
#include <iostream>
#include <vector>
#define MAXN 1000000
using namespace std;

vector<int> seive(int limit) {
    vector<int> primes;
    vector<bool> composite(limit + 10);

    for (int i = 2; i <= limit; i++) {
        if (!composite[i]) primes.push_back(i);

        for (int j = 0; j < primes.size() && i * primes[j] <= limit; j++) {
            composite[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
    return primes;
}

int main() {
    int N; cin >> N;

    vector<int> primes = seive(N);

    for (int i = 0; i < primes.size(); i++) 
        cout << primes[i] << ' ';
    cout << "\n";

    cout << "count: " << primes.size() << '\n';
    return 0;
}
