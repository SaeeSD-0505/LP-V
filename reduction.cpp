#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

void min_reduction(vector<int>& arr) {
  int min_value = INT_MAX;
  double start = omp_get_wtime();

  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];
    }
  }

  double end = omp_get_wtime();
  cout << "Minimum value: " << min_value << endl;
  cout << "Time taken (min): " << (end - start) << " seconds" << endl;
}

void max_reduction(vector<int>& arr) {
  int max_value = INT_MIN;
  double start = omp_get_wtime();

  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
    }
  }

  double end = omp_get_wtime();
  cout << "Maximum value: " << max_value << endl;
  cout << "Time taken (max): " << (end - start) << " seconds" << endl;
}

void sum_reduction(vector<int>& arr) {
  int sum = 0;
  double start = omp_get_wtime();

  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }

  double end = omp_get_wtime();
  cout << "Sum: " << sum << endl;
  cout << "Time taken (sum): " << (end - start) << " seconds" << endl;
}

void average_reduction(vector<int>& arr) {
  int sum = 0;
  double start = omp_get_wtime();

  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }

  double end = omp_get_wtime();
  double avg = static_cast<double>(sum) / arr.size();
  cout << "Average: " << avg << endl;
  cout << "Time taken (average): " << (end - start) << " seconds" << endl;
}

int main() {
  int n;
  cout << "Enter number of elements: ";
  cin >> n;

  if (n <= 0) {
    cout << "Invalid number of elements." << endl;
    return 1;
  }

  vector<int> arr(n);
  cout << "Enter " << n << " elements:\n";
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  // Optional: set number of threads
  omp_set_num_threads(4);

  min_reduction(arr);
  max_reduction(arr);
  sum_reduction(arr);
  average_reduction(arr);

  return 0;
}
