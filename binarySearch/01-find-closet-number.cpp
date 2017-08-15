/**
 * Find a closest number in array.
 */
#include <iostream>

using namespace std;

int findInsertPos(int *arr, int len, int needle)
{
  int bottom = 0, top = len, mid, next, prev, min, minIndex;
  while (bottom <= top) {
    mid = bottom + (int)((top - bottom) / 2);
    next = mid - 1 >= 0 ? mid - 1 : 0;
    prev = mid + 1 <= len - 1 ? mid + 1 : len -1;
    if (needle >= arr[next] && needle <= arr[prev]) {
      minIndex = mid;
      min = abs(needle - arr[mid]);
      if (min > abs(needle - arr[prev])) {
        min = abs(needle - arr[prev]);
        minIndex = prev;
      }
      if (min > abs(needle - arr[next])) {
        min = abs(needle - arr[next]);
        minIndex = next;
      }
      return minIndex;
    } else if (needle > arr[prev]){
      bottom = mid + 1;
    } else {
      top = mid - 1;
    }
  }
  if (bottom <= 0) {
    return 0;
  } else {
    return len - 1;
  }
}


int main(int argc, char const *argv[])
{
  int arr[] = {2, 4, 7, 9, 30, 35, 43};
  int len = sizeof(arr) / sizeof(arr[0]);
  int pos;
  pos = findInsertPos(arr, len, 9);
  cout<<"The closest number of 9 " << " is :" << arr[pos] << ", " << pos  << endl;
  pos = findInsertPos(arr, len, 25);
  cout<<"The closest number of 25 " << " is :" << arr[pos] << ", " << pos << endl;
  pos = findInsertPos(arr, len, 40);
  cout<<"The closest number of 40 " << " is :" << arr[pos] << ", " << pos << endl;
  pos = findInsertPos(arr, len, 1);
  cout<<"The closest number of 1 " << " is :" << arr[pos] << ", " << pos << endl;
  pos = findInsertPos(arr, len, 99);
  cout<<"The closest number of 99 " << " is :" << arr[pos] << ", " << pos << endl;
  return 0;
}