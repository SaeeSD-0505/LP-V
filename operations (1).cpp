#include <iostream>
#include <vector>
#include <limits>
#include <climits>     // ✅ Include this for INT_MAX and INT_MIN
#include <omp.h>

using namespace std;

int main() {
    int n, num_threads;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> data(n);
    cout << "Enter the elements separated by space:\n";
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    cout << "Enter number of threads to use: ";
    cin >> num_threads;

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    // Parallel reduction using OpenMP
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum) num_threads(num_threads)
    for (int i = 0; i < n; ++i) {
        if (data[i] < min_val)
            min_val = data[i];
        if (data[i] > max_val)
            max_val = data[i];
        sum += data[i];
    }

    double average = static_cast<double>(sum) / n;

    cout << "\n--- Parallel Reduction Results ---\n";
    cout << "Minimum: " << min_val << "\n";
    cout << "Maximum: " << max_val << "\n";
    cout << "Sum    : " << sum << "\n";
    cout << "Average: " << average << "\n";

    return 0;
}



OUTPUT

abc@abc-Latitude-5480:~$ g++ /home/abc/operations.cpp -fopenmp
abc@abc-Latitude-5480:~$ ./a.out
Enter number of elements: 6
Enter the elements separated by space:
5 10 15 20 25 30
Enter number of threads to use: 4

--- Parallel Reduction Results ---
Minimum: 5
Maximum: 30
Sum    : 105
Average: 17.5

