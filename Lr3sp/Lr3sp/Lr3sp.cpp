#include <iostream>
#include <time.h>

using namespace std;

int main() 
{                                              //создает и заполняется массив
	srand (time(NULL));
	const int array_size = 3;

	int** array = new int* [array_size];
	for (int i = 0; i < array_size; i++) 
	{
		array[i] = new int[array_size];
		for (int j = 0; j < array_size; j++) 
		{
			array[i][j] = rand()%10;
			cout << array[i][j] << ' ';
		}
		cout << endl;
	}

	int sum = 0;

	__asm 
	{                                                  //ассемблерная вставка
		mov esi, array                                 
		mov ecx, array_size                            
		mov edi, 0                                     
		mov eax, 0                                     
		lines:                                         //внешний цикл i
			cmp eax, ecx                               
			jge ext                                    
			mov ebx, 0                                 
			elems :                                    //внутренний цкил j
				cmp ebx, ecx                          
				jge inc_lines                          
				mov edx, [esi + eax * 4]               
				mov edx, [edx + ebx * 4]                
				imul edx, edx                         
				add edi, edx                          
				inc ebx                                //j++
				jmp elems                              
			inc_lines :
				inc eax                                // i++
				jmp lines                              // к новой строке
		ext :
			mov sum, edi                              
	};
	                                                   
	cout << "Sum = " << sum << endl;

	for (int i = 0; i < array_size; i++)
		delete[] array[i];
	delete[] array;
}
