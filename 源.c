#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
	int arr[MAX+1];
	int size;
}Sqlist;

void Print(Sqlist *l){
	int i = 0;
	for (i = 1; i <= l->size; i++){
		printf("%d,", l->arr[i]);
	}
}

//冒泡排序
void BubbleSort0(Sqlist *l){
	int i = 0;
	int j = 0;
	for (i = 0; i < l->size; i++){  
		for (j = l->size; j >=i; j--){
			if (l->arr[j]<l->arr[j - 1]){
				int temp = l->arr[j];
				l->arr[j] = l->arr[j -1];
				l->arr[j - 1] = temp;
			}
		}
	}
	/*for (i = 0; i < l->size; i++){
		for (j = i + 1; j < l->size; j++){
			if (l->arr[i]>l->arr[j]){
				int temp = l->arr[j];
				l->arr[j] = l->arr[j + 1];
				l->arr[j + 1] = temp;
			}
		}
	}*/
}
//冒泡排序优化
void BubbleSort1(Sqlist *l){
	int i = 0;
	int j = 0;
	int flag = 1;
	for (i = 0; i < l->size&&flag; i++){
		flag = 0;
		for (j = l->size; j >= i; j--){
			if (l->arr[j]<l->arr[j - 1]){
				int temp = l->arr[j];
				l->arr[j] = l->arr[j - 1];
				l->arr[j - 1] = temp;
				flag = 1;
			}
		}
	}
}
//简单选择排序
void SelectSort(Sqlist *l){
	int i = 0;
	int j = 0;
	int min;
	for (i = 0; i < l->size; i++){
		min = i;
		for (j = i + 1; j < l->size; j++){
			if (l->arr[j] < l->arr[min]){
				min = j;
			}
		}
		if (min != i){
			int temp = l->arr[i];
			l->arr[i] = l->arr[min];
			l->arr[min] = temp;
		}
	}
}
//直接插入排序
void InsertSort(Sqlist *l){
	int i = 0;
	int j = 0;
	for (i = 2; i < l->size; i++){  //arr[0]用来保存需要插入的数，arr[1]默认是已经排好的序列 故从arr[2]开始。
		if (l->arr[i] < l->arr[i - 1]){
			l->arr[0] = l->arr[i];//将需要插入的数据复制到arr[0]中
			for (j = i - 1; l->arr[j]>l->arr[0]; j--){//找arr[j]比arr[0]小的位置
				l->arr[j + 1] = l->arr[j];//将数据后移一位，为arr[0]腾出位置
			}
			l->arr[j + 1] = l->arr[0];//将arr[0]插入正确的位置
		}
	}
}
//希尔排序
void ShellSort(Sqlist *l){
	int i = 0;
	int j = 0;
	int increment = l->size;
	do{
		increment = increment / 3 + 1;
		for (i = increment + 1; i <= l->size; i++){
			if (l->arr[i] < l->arr[i - increment]){
				l->arr[0] = l->arr[i];//arr[0]来存储需要调整的数
				for (j = i - increment; j>0 && l->arr[0] < l->arr[j]; j -= increment){
					l->arr[j + increment] = l->arr[j];
				}
				l->arr[j + increment] = l->arr[0];
			}
		}
	} while (increment>1);
}
//快速排序arr[0]不用来存储数据
int QuickSort(Sqlist *l,int left,int right){
	int temp;
	temp = l->arr[left];
	while (left < right){
		while (l->arr[right] >= temp && left < right){
			right--;
		}
		int num = l->arr[right];
		l->arr[right] = l->arr[left];
		l->arr[left] = num;
		while (l->arr[left] <=temp && left <right){
			left++;
		}
		 num = l->arr[right];
		l->arr[right] = l->arr[left];
		l->arr[left] = num;
	}
	return left;
}
void Sort(Sqlist *l,int left,int right){
	int pivot;
	if (left < right){
		pivot = QuickSort(l, left, right);
		Sort(l, left, pivot-1);
		Sort(l, pivot + 1, right);
	}
}
//归并排序
void Merge(int SR[], int TR[], int i, int m, int n){
	int l, j, k;
	for (j = m + 1, k = i; i <= m&&j <= n; k++){
		if (SR[i] < SR[j]){
			TR[k] = SR[i++];
		}
		else{
			TR[k] = SR[j++];
		}
	}
	if (i <= m){
		for (l = 0; l <= m - i; l++){
			TR[k + 1] = SR[i + 1];
		}
	}
	if (j <= n){
		for (l = 0; l <= n - j; l++){
			TR[k + 1] = SR[j + 1];
		}
	}
}
void MSort(int SR[], int TR1[], int s, int t){
	int m;
	int TR2[MAX];
	if (s == t){
		TR1[s] = SR[s];
	}
	else{
		m = (s + t) / 2;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR1, s, m, t);
	}
}
void MergeSort(Sqlist *l){
	MSort(l->arr, l->arr, 1, l->size);
}
int main(){
	Sqlist l;
	l.size = 0;
	int array[] = { 23, 41, 12, 54, 24, 77, 93, 20 };
	int len = sizeof(array) / sizeof(array[1]);
	int i = 0;
	for (i = 1; i <= len; i++){
		l.arr[i] = array[i-1];
	}
	l.size = len;


	/*int left = 1;
	int right = l.size;
	Sort(&l,left,right);*/

	/*ShellSort(&l);*/

	MergeSort(&l);

	Print(&l);
	system("pause");
	return 0;
}