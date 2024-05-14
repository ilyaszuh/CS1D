#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


void CountingSort2(int* , int, int);
void RadixSort(int a[], int n, int k);
void QuickSort(int a[], int p, int r);
int Partition(int a[], int p, int r);
int* CountingSort(int [], int, int);
void display(int arr[], int size);
int parent(int index);
int left(int index);
int right(int index);
void MaxHeapify(int arr[], int arrSIZE, int index);
void BuildMaxHeap(int arr[], int arrSIZE);
void HeapSort(int arr[], int arrSIZE);void bubbleSort(int arr[], int arrSize);
void mergeSort(int arr[], int start, int end);
void merge(int arr[], int start, int mid, int end);
void InsertionSort(int arr[], const int arrSIZE);

int main(int argc, char *argv[])
{

	int arrSIZE = 0;
	int *arr;
	int index = 0;
	string fileName = argv[1];
   ifstream inFile(fileName);
	int tempNum = 0;
	int l = 0;
	int k = 0;
	while(!inFile.eof())
	{
		inFile >> tempNum;
		arrSIZE++;
		tempNum = 0;
	}
	inFile.close();
	arrSIZE--;
   arr = new int[arrSIZE];
	inFile.open(fileName);

	while(!inFile.eof() && index < arrSIZE)
	{
		inFile >> arr[index];
		index++;
	}

	 switch(*argv[2])
    {
        case '0':
			{
				cout << "Calling insertion sort" << endl;
    			InsertionSort(arr, arrSIZE);
				cout << "Done calling insertion sort" << endl;
			}
        break;
        case '1':
			{
        		cout << "Calling merge sort" << endl;
				mergeSort(arr, 0, arrSIZE - 1);
				cout << "Done calling merge sort" << endl;
			}
        break;
	     case '2':
			{
	         cout << "Calling bubble sort" << endl;
				bubbleSort(arr, arrSIZE);
				cout << "Done calling bubble sort" << endl;
			}
        break;
        case '3':
			{
	         cout << "Calling heap sort" << endl;
	    		for(int i = arrSIZE / 2 - 1; i >= 0; i--)
	    		{
	        		MaxHeapify(arr, arrSIZE, i);
	    		}

	    		HeapSort(arr, arrSIZE);
				cout << "Done calling heap sort" << endl;
			}
        break;
        case '4':
			{
	         cout << "Calling quick sort" << endl;
			  	QuickSort(arr, 0, arrSIZE - 1);
				cout << "Done calling quick sort" << endl;
			}
        break;
        case '5':
			{
	         cout << "Calling counting sort" << endl;
	    		//Find largest element
	    		l = arr[0];
	    		for(int i = 0; i < arrSIZE; i++)
	    		{
	        		if(arr[i] > l)
	        		{
	           		 l = arr[i];
	        		}
	   		}
	    		k = l;
				arr = CountingSort(arr, arrSIZE, k);
				cout << "Done calling counting sort" << endl;
			}
        break;
        case '6':
			{
	         cout << "Calling radix sort" << endl;
	    		//Find largest element
	    		l = arr[0];
	    		for(int i = 0; i < arrSIZE; i++)
	    		{
	        		if(arr[i] > l)
	        		{
	           		 l = arr[i];
	        		}
	   		}
	    		k = l;
				RadixSort(arr, arrSIZE, k);
				cout << "Done calling radix sort" << endl;
			}
        break;
			default:
			{
				cout << "Not a valid choice\n";
			}
    }

	delete [] arr;
	inFile.close();
	return 0;
}

void display(int arr[], int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

void InsertionSort(int arr[], const int arrSIZE)
{
    int key = 0;
    int i = 0;
    for(int j = 1; j < arrSIZE; j++)
    {
        key = arr[j];
        i = j - 1;
        while(i >= 0 && arr[i] > key)
        {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

void merge(int arr[], int start, int mid, int end)
{
  int len1 = mid - start + 1;
  int len2 = end - mid;

  int leftArr[len1], rightArr[len2];

  for (int i = 0; i < len1; i++)
    leftArr[i] = arr[start + i];
  for (int j = 0; j < len2; j++)
    rightArr[j] = arr[mid + 1 + j];

  int i, j, k;
  i = 0;
  j = 0;
  k = start;

  while (i < len1 && j < len2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  while (i < len1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  while (j < len2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

//MergeSort function
void mergeSort(int arr[], int start, int end)
{
	//If we are not at the end
  if (start < end) {
	//Find the middle
    int mid = start + (end - start) / 2;

	//Call mergeSort on the right half and left half
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);

	//Merge the two halvs
    merge(arr, start, mid, end);
  }
}

void bubbleSort(int arr[], int arrSize) {
    for (int i = 0; i < arrSize - 1; i++) {
        for (int j = 0; j < arrSize - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int Parent(int index) {
    return (floor(index / 2));
}

int Left(int index) {
    return (2 * index + 1);
}

int Right(int index) {
    return (2 * index + 2);
}

void MaxHeapify(int arr[], int arrSIZE, int index) {
    int largest = index;
    int left = Left(index);
    int right = Right(index);

    if (left < arrSIZE && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < arrSIZE && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(arr[index], arr[largest]);
        MaxHeapify(arr, arrSIZE, largest);
    }
}

void BuildMaxHeap(int arr[], int arrSIZE) {
    for (int i = arrSIZE / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, arrSIZE, i);
    }
}

void HeapSort(int arr[], int arrSIZE) {
    BuildMaxHeap(arr, arrSIZE);
    for (int i = arrSIZE - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        MaxHeapify(arr, i, 0);
    }
}


int* CountingSort(int a[], int n, int k)
{
    int *b, *c;
    b = new int[n];
    c = new int[k + 1];
    int i, j = 0;
    for(i = 0; i <= k; i++)
    {
        c[i] = 0;
    }

    for(j = 0; j < n; j++)
    {
        c[a[j]]++;
    }

    for(i = 1; i <= k; i++)
    {
        c[i] += c[i - 1];
    }

    for(j = n - 1; j >= 0; j--)
    {
        b[--c[a[j]]] = a[j];
    }

    for(i = 0; i < n; i++)
    {
        a[i] = b[i];
    }

    delete [] b;
    delete [] c;

    return a;
}


void QuickSort(int a[], int p, int r)
{
    int q = 0;
    if(p < r)
    {
        q = Partition(a, p, r);
        QuickSort(a, p, q - 1);
        QuickSort(a, q + 1, r);
    }
}

int Partition(int a[], int p, int r)
{
    int x = a[r];
    int i = p - 1;

    for(int j = p; j < r; j++)
    {
        if(a[j] <= x)
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

//Refrance: geeksforgeeks.com
void CountingSort2(int* a, int n, int exp)
{
    int b[n];
    int c[exp];
    int i, j = 0;

	 for(i = 0; i < exp; i++)
		{
			c[i] = 0;
		}

    for(j = 0; j < n; j++)
    {
        c[(a[j] / exp) % 10]++;
    }

    for(i = 1; i < 10; i++)
    {
        c[i] += c[i - 1];
    }

    for(j = n - 1; j >= 0; j--)
    {
        b[c[(a[j] / exp) % 10] - 1] = a[j];
        c[(a[j] / exp) % 10]--;
    }

    for(i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}

//Refrance: geeksforgeeks.com
void RadixSort(int* a, int n, int k)
{
    for(int exp = 1; k / exp > 0; exp *= 10)
    {
        CountingSort2(a, n, exp);
    }
}
