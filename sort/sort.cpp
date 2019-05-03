#include<stdio.h>
#include<stdlib.h>

void Print(int *array, int len) {
	//打印数组array(长度为len)的内容
	for (int i = 0; i < len; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}
void swap(int *a, int *b) {
	//交换a,b值
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*直接插入排序*/
void insertSort(int *array, int len) {
	//从小到大排序
	int i, j;
	printf("%d: ", array[0]);
	Print(array, len);//打印每轮排序后的数组内容
	for (i = 1; i < len; ++i) {
		//第一个元素i=0,不需要排序，从i=1开始
		printf("%d: ", array[i]);//每轮排序要插入的数字
		//新插入的元素小于前面的元素，需要插入到前面的位置，需要找到待插入新元素的位置
		int x = array[i];//哨兵
		for (j = i; j > 0 && x < array[j - 1]; --j) {
			//元素逐个后移，直到j为待插入的位置
			array[j] = array[j - 1];
		}
		array[j] = x;
		Print(array, len);//打印每轮排序后的数组内容
	}
}

/*希尔插入排序*/
void shellInsertSort(int *array, int len, int dk) {
	//与直接插入排序类似，但是每次排序是将分量排序
	//从小到大排序
	int i, j;
	printf("%d: ", array[dk - 1]);
	Print(array, len);//打印每轮排序后的数组内容
	for (i = dk; i < len; ++i) {
		printf("%d: ", array[i]);//每轮排序要插入的数字
		//新插入的元素小于前面的元素，需要插入到前面的位置，需要找到待插入新元素的位置
		int x = array[i];//哨兵
		for (j = i; j >= dk && x < array[j - dk]; j -= dk) {
			//元素逐个后移，直到j为待插入的位置
			array[j] = array[j - dk];
		}
		array[j] = x;
		Print(array, len);//打印每轮排序后的数组内容
	}
}
void shellSort(int *array, int len) {
	//增量dk初始设置为数组长度的一半，每次插入排序后减为1/2
	int dk = len / 2;
	while (dk > 0) {
		shellInsertSort(array, len, dk);
		dk /= 2;
	}
}

/*简单选择排序*/
void selectSort(int *array, int len) {
	//从小到大排序
	//每次选择最小的数，与未排序的部分第一个交换位置
	int i, j;
	for (i = 0; i < len; ++i) {
		//i标记未排序的第一个位置
		int min = i;
		for (j = i + 1; j < len; j++) {
			//j每次找出从i开始最小的数
			if (array[j] < array[min]) {
				min = j;
			}
		}
		if(min != i)
			swap(array + i, array + min);
		Print(array, len);
	}
}

/*二元选择排序*/
void selectTwoSort(int *array, int len) {
	//从小到大排序
	//每次选择最小的数和最大的数，与未排序的部分第一个和最后一个交换位置
	int i, j, min, max;
	for (i = 0; i < len / 2; ++i) {
		min = max = i;
		for (j = i; j < len - i; ++j) {
			if (array[j] < array[min]) {
				min = j;
			}
			if (array[j] > array[max]) {
				max = j;
			}	
		}
		if (!(i == min && len - i - 1 == max)) {
			if (i == max && len - i - 1 == min) {
				swap(array + min, array + max);
			}
			else if (i == max) {
				swap(array + max, array + len - i - 1);
				swap(array + min, array + i);
			}
			//else if (len - i - 1 == min) {
			//	swap(array + min, array + i);
			//	swap(array + max, array + len - i - 1);
			//}
			else {
				swap(array + i, array + min);
				swap(array + len - i - 1, array + max);
			}
		}
		Print(array, len);
	}
}

/*堆排序*/
//下标从1开始 parent:i/2,left:2*i,right:2*i+1
//下标从0开始
int parent(int i) { return (i - 1) / 2; }//返回父节点位置
int left(int i) { return 2 * i + 1; }//反回左孩子位置
int right(int i) { return 2 * (i + 1); }//返回右孩子位置
void maxHeapify(int *array, int i, int len) {
	//维护堆的性质
	//假定根节点为left(i)和right(i)的二叉树都为最大堆
	//array[i]可能会小于其孩子
	int l = left(i), r = right(i);
	//找到 i,l,r 最大的
	int largest;
	if (l<len && array[l]>array[i])
		largest = l;
	else largest = i;
	if (r<len && array[r]>array[largest])
		largest = r;
	//如果最大的不是i，说明违背了最大堆的性质
	if (largest != i) {
		swap(array + i, array + largest);
		//交换后，需要考虑子树是否会违背性质，递归调用
		maxHeapify(array, largest, len);
	}
}
void buildMaxHeap(int *array, int len) {
	//利用maxHeapify建立一个最大堆
	//最开始时数组array的每一个元素都是堆
	//而且可以证明，当数组长度为n时，叶节点下标分别为 n/2+1, n/2+2, ... ,n
	for (int i = len / 2; i >= 0; --i) {
		maxHeapify(array, i, len);
	}
}
void heapSort(int *array, int len) {
	//从小到大排序
	//首先将数组array建立成最大堆
	buildMaxHeap(array, len);
	Print(array, len);
	int size = len;
	for (int i = len - 1; i > 0; --i) {
		//将第一个元素（最大）与最后一个元素交换位置
		swap(array, array + i);
		size--;
		maxHeapify(array, 0, size);
		Print(array, len);
	}
	
}

/*冒泡排序*/
void bubbleSort(int *array, int len) {
	for (int i = 0; i < len - 1; ++i) {
		int isExchanged = 0;
		//需要len-1趟,每次将最大的”冒泡“到最后面的位置，小的往前移
		for (int j = 0; j < len - i - 1; ++j) {
			if (array[j] > array[j + 1]) {
				swap(array + j, array + j + 1);
				isExchanged = 1;
			}
		}
		Print(array, len);
		if (!isExchanged)//如果有一趟没有交换元素，说明已经排好序
			break;
	}
}

/*快速排序*/
int partition(int *array, int begin, int end) {
	//将数组原址划分
	//以某个值为界限，小于其的放前面，大于其的放后面，这里选择最后一个
	int x = array[end];
	int i = begin, j = end - 1;
	while (i < j) {
		while (i < j && array[i] <= x) i++;
		while (i < j && array[j] >= x) j--;
		swap(array + i, array + j);
	}
	swap(array + i, array + end);
	return i;
}
void quickSort(int *array, int begin, int end){
	if (begin < end) {
		int pivot = partition(array, begin, end);
		quickSort(array, begin, pivot - 1);
		quickSort(array, pivot + 1, end);
	}
	Print(array, end - begin + 1);
}

/*归并排序*/
void merge(int *array, int begin, int mid, int end) {
	int lenA = mid - begin + 1, lenB = end - mid;
	int i, j, k;
	//新建两个数组，长度分别为lenA+1和lenB+1，多余的一个用来设置为哨兵
	int *A = (int *)malloc(sizeof(int)*(lenA + 1));
	int *B = (int *)malloc(sizeof(int)*(lenB + 1));
	for ( i = 0; i < lenA; i++)
		A[i] = array[begin + i];
	for ( i = 0; i < lenB; i++)
		B[i] = array[mid + i + 1];
	A[lenA] = B[lenB] = 0x7fffffff;//模拟正无穷大
	//开始合并A,B到array
	i = j = 0;
	for (k = begin; k <= end; ++k) {
		if (A[i] <= B[j]) {
			array[k] = A[i];
			i++;
		}
		else {
			array[k] = B[j];
			j++;
		}
	}
	free(A);
	free(B);
}
void mergeSort(int *array, int begin, int end) {
	//利用递归
	//int begin = start, end = start + len - 1;
	if (begin < end) {
		int mid = (begin + end) / 2;
		mergeSort(array, begin, mid);
		mergeSort(array, mid + 1, end);
		//核心是合并两个已经排好序的数组
		merge(array, begin, mid, end);
	}
	Print(array, end - begin + 1);
}


int main(void) {
	const int len = 11;
	int array[11] = { 4,2,9,1,7,0,6,3,5,10,8 };
	//insertSort(array, len);//直接插入排序done
	//shellSort(array, len);//希尔排序
	//selectSort(array, len);//简单选择排序
	//selectTwoSort(array, len);//二元选择排序
	//heapSort(array, len);//堆排序
	//bubbleSort(array, len);//冒泡排序
	//mergeSort(array, 0, len - 1);//归并排序
	quickSort(array, 0, len - 1);//快速排序
	return 0;
}
