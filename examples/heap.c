#include "../header.h"

int		heap[256];
int		size = 0;

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	insert(int value)
{
	int	index;

	heap[size] = value;
	index = size;
	size++;
	// heapify - up
	while (index > 0 && heap[(index - 1) / 2] > heap[index])
	{
		swap(&heap[index], &heap[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}

void	deleteMin(int value)
{
	int	index;

	index = -1;
	// find index of the value to delete
	for (int i = 0; i < size; i++)
	{
		if (heap[i] == value)
		{
			index = i;
			break ;
		}
	}
	// value not found
	if (index == -1)
		return ;
	heap[index] = heap[size - 1];
	size--;
	// heapify down
	while (1)
	{
		int left = 2 * index + 1;  // left child
		int right = 2 * index + 2; // right child
		int smallest = index;      // assume current is the smallest
		// check if left child is smaller
		if (left < size && heap[left] < heap[smallest])
			smallest = left;
		// check if right child is smaller
		if (right < size && heap[right] < heap[smallest])
			smallest = right;
		if (smallest != index)
		{
			swap(&heap[index], &heap[smallest]);
			index = smallest;
		}
		else
			break ;
	}
	// heapify up
	while (index > 0 && head[(index - 1) / 2] > heap[index])
	{
		swap(&heap[index], &heap[(index - 1) / 2]);
		index = (index - 1) / 2:
	}
}

// Display heap
void	display(void)
{
	for (int i = 0; i < size; i++)
		printf("%d ", heap[i]);
	printf("\n");
}

int	main(void)
{
	int	values[] = {13, 16, 31, 41, 51, 100};
	int	n;

	n = sizeof(values) / sizeof(values[0]);
	// Insert elements
	for (int i = 0; i < n; i++)
		insert(values[i]);
	printf("Initial heap: ");
	display();
	// Delete element 13
	deleteMin(13);
	printf("Heap after deleting 13: ");
	display();
	return (0);
}
