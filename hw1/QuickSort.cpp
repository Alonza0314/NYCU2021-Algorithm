#include<iostream>
#include<stack>
#include<ctime>
using namespace std;

//find the pivot
int find_pivot(int* arr)
{
	int pivot;
	for (int i = 0; i < 3; i++)
	{
		for (int j = i; j < 2; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	pivot = arr[1];
	return pivot;
}
//put int small than middle to left
//put int large than middle to right
int replace(int* arr, int head, int last, int pivot)
{
	int return_pivot = pivot;
	//use for test
	/*cout << "Return_pivot = " << return_pivot << endl;
	cout << "Array[return_pivot] = " << arr[return_pivot] << endl;*/
	
	for (int i = head; i < return_pivot; i++)
	{
		if (arr[i] <= arr[return_pivot])
		{
			continue;
		}
		else
		{
			int temp = arr[i];
			for (int j = i; j < last; j++)
			{
				arr[j] = arr[j + 1];
			}
			arr[last] = temp;
			return_pivot--;
			i--;
		}
	}
	//use for test
	/*cout << "head = " << head << " , last = " << last << endl;
	cout << "Array after < replace:" << endl;
	for (int i = head; i < last + 1; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;*/
	
	for (int i = return_pivot + 1; i <= last; i++)
	{
		if (arr[i] >= arr[return_pivot])
		{
			continue;
		}
		else
		{
			int temp = arr[i];
			for (int j = i; j > head; j--)
			{
				arr[j] = arr[j - 1];
			}
			arr[head] = temp;
			return_pivot++;
		}
	}
	//use for test
	/*cout << "Array[return_pivot] = " << arr[return_pivot] << endl;
	cout << "Array after > sorted:" << endl;
	for (int i = head; i <= last; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;*/
	
	return return_pivot;
}
//quick sort
void quick_sort(int* arr, int head, int last)
{
	stack<int> stack;
	stack.push(head);
	stack.push(last);
	while (!stack.empty())
	{
		int new_last = stack.top();
		stack.pop();
		int new_head = stack.top();
		stack.pop();
		int middle = (new_head + new_last) / 2;
		int arrarr[3] = { arr[new_head],arr[middle],arr[new_last] };
		int temp = find_pivot(arrarr);
		int pivot;
		if (temp == arr[new_head])
		{
			pivot = new_head;
		}
		else if (temp == arr[middle])
		{
			pivot = middle;
		}
		else
		{
			pivot = new_last;
		}
		int new_pivot = replace(arr, new_head, new_last, pivot);
		if (new_pivot - 1 > new_head)
		{
			stack.push(new_head);
			stack.push(new_pivot - 1);
		}
		if (new_pivot + 1 < new_last)
		{
			stack.push(new_pivot + 1);
			stack.push(new_last);
		}
	}
}
//use to check the array has been sorted or not
bool check(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] <= arr[i + 1])
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
//check correct use in the 500 test case
bool checkcheck(int* arr)
{
	for (int i = 0; i < 500; i++)
	{
		if (arr[i] == 0)
		{
			return false;
		}
	}
	return true;
}
//main function
void main()
{
	//generate 500 test case ,if all of the test is right, it will cout "correct~~~~~" at end
	/*int count = 0;
	int arrarr[500];
	while (count != 500)
	{
		cout << "The " << count << " test." << endl;
		int* arr;
		int num = rand() % 101;
		arr = (int*)malloc(num * sizeof(int));
		for (int i = 0; i < num; i++)
		{
			arr[i] = rand() % 101;
		}
		cout << "There is " << num << " numbers." << endl;
		cout << "The random array:";
		for (int i = 0; i < num; i++)
		{
			if (i == 0 || i % 10 == 0)
			{
				cout << endl << arr[i] << " ";
			}
			else
			{
				cout << arr[i] << " ";
			}
		}
		cout << endl;
		quick_sort(arr, 0, num - 1);
		cout << "The sorted array:";
		for (int i = 0; i < num; i++)
		{
			if (i == 0 || i % 10 == 0)
			{
				cout << endl << arr[i] << " ";
			}
			else
			{
				cout << arr[i] << " ";
			}
		}
		cout << endl;
		if (check(arr, num))
		{
			arrarr[count] = 1;
			cout << "Sorted" << endl;
		}
		else
		{
			cout << "Non-Sorted" << endl;
		}
		count++;
		cout << endl;
	}
	if (!checkcheck(arrarr))
	{
		cout << "Wrong!!!!!!!!!!" << endl;
	}
	else
	{
		cout << "Correct~~~~~~~~~~~~~" << endl;
	}*/
	//main code
	int* arr;
	srand(time(NULL));
	int num = rand() % 101;
	arr = (int*)malloc(num * sizeof(int));
	for (int i = 0; i < num; i++)
	{
		arr[i] = rand() % 101;
	}
	cout << "There is " << num << " numbers." << endl;
	cout << "The random array:";
	for (int i = 0; i < num; i++)
	{
		if (i == 0 || i % 10 == 0)
		{
			cout << endl << arr[i] << " ";
		}
		else
		{
			cout << arr[i] << " ";
		}
	}
	cout << endl << endl;
	quick_sort(arr, 0, num - 1);
	cout << "The sorted array:";
	for (int i = 0; i < num; i++)
	{
		if (i == 0 || i % 10 == 0)
		{
			cout << endl << arr[i] << " ";
		}
		else
		{
			cout << arr[i] << " ";
		}
	}
	cout << endl;
}