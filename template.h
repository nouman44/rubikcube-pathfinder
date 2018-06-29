#pragma once

#include <iostream>
#include <fstream>
using namespace std;

enum Direction { LEFT, RIGHT };
enum BlockNO { A, B, C, D };
const int SIZE = 3;

//template for class Stack store data items
template <class myType>
class Stack
{
	private:
		myType *stackArr; //array for stack
		int currentIndex; //specifies the current index of stack
		int maxSize; //specifies max size for stack
		void ReallocateDouble(); //fucntions doubles size for stack
	public:
		Stack(); //constructor
		Stack(int inputSize); //paramterized constructor
		~Stack(); //destructor
		bool isFull(); //function to check if stack full
		bool isEmpty(); //function to check if stack is empty
		void Push(const myType value); //pushes data value/object onto stack
		myType Pop(); //returns topmost item of stack
};

//template of the specializtion of stack class
template <class myType>
class Stack<myType*>
{
	private:
		myType **stackArr; //array for stack
		int currentIndex; //specifies the current index of stack
		int maxSize; //specifies max size for stack
		void ReallocateDouble(); //fucntions doubles size for stack
	public:
		Stack(); //constructor
		Stack(int inputSize); //paramterized constructor
		~Stack(); //destructor
		bool isFull(); //function to check if stack full
		bool isEmpty(); //function to check if stack is empty
		void Push(myType* value); //pushes pointer of value/object onto stack
		myType* Pop(); //returns pointer of topmost item of stack
};

template <class myType>
class Array
{
	private:
		myType *arr; //array member
		int size; //specifies size for the array
		int currentSize; //specifies current szie for the array
		void ReallocateDouble(); //function doubles the size of array
	public:
		Array(); //constructor
		Array(const Array & arrObj); //copy contrcutor 
		~Array(); //destructor
		void AddItem(const myType value); //function to add item to array
		bool Find(myType value); //function to find if value exists in array
		friend ostream & operator<<(ostream & strm, const Array & arrObj); //to output array by stream
};

template <class myType>
class Array<myType*>
{
	private:
		myType **arr; //array member
		int size; //specifies size for the array
		int currentSize; //specifies current szie for the array
		void ReallocateDouble(); //function doubles the size of array
	public:
		Array(); //constructor
		Array(const Array & arrObj); //copy contrcutor 
		~Array(); //destructor
		void AddItem(myType* value); //function to add pointer of item to array
		bool Find(myType* value); //function to find if value exists in array
		friend ostream & operator<<(ostream & strm, const Array<myType> & arrObj)  //to output array by stream
		{
			int i;
			for (i = 0;i < arrObj.currentSize;i++)
			{
				strm << *(arrObj.arr[i]) << endl;
			}

			return strm;
		}
};

template <class myType>
class State
{
	private:
		myType **block; //2D Array to store state
		State *parent; //pointer to the parent of state
		Direction direc; //variable to store direction of state
		BlockNO bNo; //variable to store Block Number of state
		myType** Allocate2DArray(); //function to allocate 2D array for state
		void RotateA(Direction userDirec); //function to rotate block A by direction
		void RotateB(Direction userDirec); //function to rotate block B by direction
		void RotateC(Direction userDirec); //function to rotate block C by direction
		void RotateD(Direction userDirec); //function to rotate block D by direction
		char* stringDirection(); //fucntion to return string by direction
		char stringBlockNO(); //function to return char by Block number
	public:
		State(); //constructor
		State(const State & stateObj); //copy constructor
		~State(); //destructor
		void SetParent(State<myType> * statePtr); //function to set parent of state
		State Rotate(Direction userDirec, BlockNO userbNo); //function rotate block by direction

		friend ostream & operator<<(ostream & strm, const State<myType> & stateObj) //output state by stream
		{
			int i, j;
			for (i = 0;i < SIZE;i++)
			{
				strm << "-------------" << endl;

				for (j = 0;j < SIZE;j++)
				{
					strm << "|" << " " << stateObj.block[i][j] << " ";
				}
				strm << "|";
				strm << endl;
			}

			strm << "-------------" << endl;

			return strm;
		}

		friend istream & operator>>(istream & strm, State<myType> & stateObj) //input state by stream
		{
			int i, j;
			for (i = 0;i < SIZE;i++)
			{
				for (j = 0;j < SIZE;j++)
				{
					strm >> stateObj.block[i][j];
				}
			}

			return strm;
		}

		bool operator==(const State & stateObj); //check if two states are equal
		bool operator!=(const State & stateObj); //check is two states are not equal
		const State<myType> & operator=(const State & stateObj); //make one state equal to the other
		void PrintPathReverse(); //print path of how state achieved in reverse order
		void PrintPath(); //print path of how state achieved
};

template <class myType>
class GameSolver
{
	private:
		Stack<State<myType> *> myStack; //stack of state pointers
		Array<State<myType> *> visitedArray; //array of pointers to state
		State<myType> initialState; //initial state
		State<myType> goalState; //goal state 
		State<myType> *currentState; //pointer to store the current state
		void GenerateChildStates(State<myType> * stateObj); //function to genereate possible 8 child states of provided state
	public:
		GameSolver(); //constructor
		void ReadStatesFromFile(char* statesFile); //function to read intial and goal
		void DepthFirstSearchAlgo(); //Depth first search algorithm to reach goal state from initial
};

class Menu
{
	private:
		GameSolver<int> Gint; //gamesolver for integer state
		GameSolver<char> Gchar; //gamesolver for character state
		GameSolver<float> Gfloat; //gamesolver for float state
	public:
		void RunProgram(); //function to run the whole program
};

template<class myType>
void Stack<myType>::ReallocateDouble()
{
	int i, newSize = maxSize * 2;
	myType *temp = new myType[newSize];

	for (i = 0;i < currentIndex;i++)
	{
		temp[i] = stackArr[i];
	}

	delete[] stackArr;

	stackArr = temp;
}

template <class myType>
Stack<myType>::Stack()
{
	currentIndex = 0;
	maxSize = 0;
	stackArr = NULL;
}

template <class myType>
Stack<myType>::Stack(int inputSize)
{
	currentIndex = 0;
	maxSize = inputSize;

	stackArr = new myType[inputSize];
}

template <class myType>
Stack<myType>::~Stack()
{
	if (currentIndex != 0)
		delete[] stackArr;
}

template <class myType>
bool Stack<myType>::isFull()
{
	bool check = true;

	if (currentIndex < maxSize)
		check = false;

	return check;
}

template <class myType>
bool Stack<myType>::isEmpty()
{
	bool check = true;

	if (currentIndex > 0)
		check = false;

	return check;
}

template <class myType>
void Stack<myType>::Push(const myType value)
{

	if (currentIndex == 0)
	{
		maxSize = 1;
		stackArr = new myType[maxSize];
	}
	else if (currentIndex == maxSize)
	{
		ReallocateDouble();
		maxSize = maxSize * 2;
	}

	stackArr[currentIndex] = value;
	currentIndex++;
}

template <class myType>
myType Stack<myType>::Pop()
{
	bool check = isEmpty();
	myType var = NULL;

	if (!check)
	{
		var = stackArr[currentIndex - 1];
		stackArr[currentIndex - 1] = NULL;
		currentIndex--;
	}

	return var;
}
template<class myType>
void Stack<myType*>::ReallocateDouble()
{
	int i, newSize = maxSize * 2;

	myType **temp = new myType*[newSize];

	for (i = 0;i < currentIndex;i++)
	{
		temp[i] = stackArr[i];
	}

	delete[] stackArr;

	stackArr = temp;
}

template <class myType>
Stack<myType*>::Stack()
{
	currentIndex = 0;
	maxSize = 0;
	stackArr = NULL;
}

template <class myType>
Stack<myType*>::Stack(int inputSize)
{
	currentIndex = 0;
	maxSize = inputSize;

	stackArr = new myType*[inputSize];
}

template <class myType>
Stack<myType*>::~Stack()
{
	int i;

	if (currentIndex != 0)
	{
		for (i = 0;i < currentIndex;i++)
		{
			delete stackArr[i];
		}
		
		delete[] stackArr;
	}
}

template <class myType>
bool Stack<myType*>::isFull()
{
	bool check = true;

	if (currentIndex < maxSize)
		check = false;

	return check;
}

template <class myType>
bool Stack<myType*>::isEmpty()
{
	bool check = true;

	if (currentIndex > 0)
		check = false;

	return check;
}

template <class myType>
void Stack<myType*>::Push(myType * value)
{
	if (currentIndex == 0)
	{
		maxSize = 1;
		stackArr = new myType*[maxSize];
	}
	else if (currentIndex == maxSize)
	{
		ReallocateDouble();
		maxSize = maxSize * 2;
	}

	stackArr[currentIndex] = value;
	currentIndex++;
}

template <class myType>
myType* Stack<myType*>::Pop()
{
	bool check = isEmpty();
	myType* returnVal = NULL;

	if (!check)
	{
		returnVal = stackArr[currentIndex - 1];
		stackArr[currentIndex - 1] = NULL;
		currentIndex--;
	}

	return returnVal;
}

template<class myType>
void Array<myType>::ReallocateDouble()
{
	int i, newSize = size * 2;
	myType *temp = new myType[newSize];

	for (i = 0;i < currentSize;i++)
	{
		temp[i] = arr[i];
	}

	delete[] arr;

	arr = temp;
}

template<class myType>
Array<myType>::Array()
{
	arr = NULL;
	size = 0;
	currentSize = 0;
}

template<class myType>
Array<myType>::Array(const Array<myType> & arrObj)
{

}

template<class myType>
Array<myType>::~Array()
{
	int i;

	if (currentSize != 0)
	{
		for (i = 0;i < currentSize;i++)
		{
			delete arr[i];
		}

		delete[] arr;
	}
}

template<class myType>
void Array<myType>::AddItem(const myType value)
{
	if (currentSize == 0)
	{
		size = 1;
		arr = new myType[size];
	}
	else if (currentSize == size)
	{
		ReallocateDouble();
		size = size * 2;
	}

	arr[currentSize] = value;
	currentSize++;
}

template<class myType>
bool Array<myType>::Find(myType value)
{
	bool doesExist = false;

	for (int i = 0;i < currentSize && !doesExist;i++)
	{
		if (arr[i] == value)
			doesExist = true;
	}

	return doesExist;
}

template<class myType>
ostream & operator<<(ostream & strm, const Array<myType> & arrObj)
{
	int i;

	for (i = 0;i < arrObj.currentSize;i++)
	{
		strm << arrObj.arr[i];
	}
}

template<class myType>
void Array<myType*>::ReallocateDouble()
{
	int i, newSize = size * 2;

	myType **temp = new myType*[newSize];

	for (i = 0;i < currentSize;i++)
	{
		temp[i] = arr[i];
	}

	delete[] arr;

	arr = temp;
}

template<class myType>
Array<myType*>::Array()
{
	arr = NULL;
	size = 0;
	currentSize = 0;
}

template<class myType>
Array<myType*>::Array(const Array<myType*> & arrObj)
{

}

template<class myType>
Array<myType*>::~Array()
{
	if (currentSize != 0)
		delete[] arr;
}

template<class myType>
void Array<myType*>::AddItem(myType * value)
{
	if (currentSize == 0)
	{
		size = 1;
		arr = new myType*[size];
	}
	else if (currentSize == size)
	{
		ReallocateDouble();
		size = size * 2;
	}

	arr[currentSize] = value;
	currentSize++;
}

template<class myType>
bool Array<myType*>::Find(myType * value)
{
	bool doesExist = false;

	for (int i = 0;i < currentSize && !doesExist;i++)
	{
		if (*arr[i] == *value)
			doesExist = true;
	}

	return doesExist;
}

template<class myType>
ostream & operator<<(ostream & strm, const Array<myType*> & arrObj)
{
	int i;

	for (i = 0;i < arrObj.currentSize;i++)
	{
		strm << *(arrObj.arr[i]);
	}
}

template<class myType>
myType ** State<myType>::Allocate2DArray()
{
	int i;
	myType **block = new myType*[SIZE];

	for (i = 0;i < SIZE;i++)
	{
		block[i] = new myType[SIZE];
	}

	return block;
}

template<class myType>
void State<myType>::RotateA(Direction userDirec)
{
	myType temp;

	if (userDirec == RIGHT)
	{
		temp = block[0][0];
		block[0][0] = block[1][0];
		block[1][0] = block[1][1];
		block[1][1] = block[0][1];
		block[0][1] = temp;
	}
	else
	{
		temp = block[0][0];
		block[0][0] = block[0][1];
		block[0][1] = block[1][1];
		block[1][1] = block[1][0];
		block[1][0] = temp;
	}

	bNo = A;
	direc = userDirec;
}

template<class myType>
void State<myType>::RotateB(Direction userDirec)
{
	myType temp;

	if (userDirec == RIGHT)
	{
		temp = block[0][1];
		block[0][1] = block[1][1];
		block[1][1] = block[1][2];
		block[1][2] = block[0][2];
		block[0][2] = temp;
	}
	else
	{
		temp = block[0][1];
		block[0][1] = block[0][2];
		block[0][2] = block[1][2];
		block[1][2] = block[1][1];
		block[1][1] = temp;
	}

	bNo = B;
	direc = userDirec;
}

template<class myType>
void State<myType>::RotateC(Direction userDirec)
{
	myType temp;

	if (userDirec == RIGHT)
	{
		temp = block[1][0];
		block[1][0] = block[2][0];
		block[2][0] = block[2][1];
		block[2][1] = block[1][1];
		block[1][1] = temp;
	}
	else
	{
		temp = block[1][0];
		block[1][0] = block[1][1];
		block[1][1] = block[2][1];
		block[2][1] = block[2][0];
		block[2][0] = temp;
	}

	bNo = C;
	direc = userDirec;
}

template<class myType>
void State<myType>::RotateD(Direction userDirec)
{
	myType temp;

	if (userDirec == RIGHT)
	{
		temp = block[1][1];
		block[1][1] = block[2][1];
		block[2][1] = block[2][2];
		block[2][2] = block[1][2];
		block[1][2] = temp;
	}
	else
	{
		temp = block[1][1];
		block[1][1] = block[1][2];
		block[1][2] = block[2][2];
		block[2][2] = block[2][1];
		block[2][1] = temp;
	}

	bNo = D;
	direc = userDirec;
}

template<class myType>
char * State<myType>::stringDirection()
{
	char* str = NULL;

	switch (direc)
	{
		case LEFT:
			str = "Left";
			break;
		case RIGHT:
			str = "Right";
			break;
	}

	return str;
}

template<class myType>
char State<myType>::stringBlockNO()
{
	char str;

	switch (bNo)
	{
		case A:
			str = 'A';
			break;
		case B:
			str = 'B';
			break;
		case C:
			str = 'C';
			break;
		case D:
			str = 'D';
			break;
	}

	return str;
}

template<class myType>
void State<myType>::SetParent(State<myType> * statePtr)
{
	parent = statePtr;
}

template<class myType>
State<myType>::State()
{
	block = Allocate2DArray();

	parent = NULL;
}

template<class myType>
State<myType>::State(const State<myType> & stateObj)
{
	block = Allocate2DArray();

	int i, j;

	for (i = 0;i < SIZE;i++)
	{
		for (j = 0;j < SIZE;j++)
		{
			block[i][j] = stateObj.block[i][j];
		}
	}

	direc = stateObj.direc;
	bNo = stateObj.bNo;
	parent = stateObj.parent;
}

template<class myType>
State<myType>::~State()
{
	for (int i = 0;i < SIZE;i++)
		delete[] block[i];

	delete[] block;
}

template<class myType>
State<myType> State<myType>::Rotate(Direction userDirec, BlockNO userbNo)
{
	State stateObj(*this);

	switch (userbNo)
	{
		case A:
			stateObj.RotateA(userDirec);
			break;
		case B:
			stateObj.RotateB(userDirec);
			break;
		case C:
			stateObj.RotateC(userDirec);
			break;
		case D:
			stateObj.RotateD(userDirec);
			break;
	}

	return stateObj;
}

template<class myType>
bool State<myType>::operator==(const State & stateObj)
{
	bool isEqual = true;
	int i,j;

	for (i = 0;i < SIZE && isEqual;i++)
	{
		for (j = 0;j < SIZE && isEqual;j++)
		{
			if (block[i][j] != stateObj.block[i][j])
			{
				isEqual = false;
			}
		}
	}

	return isEqual;
}

template<class myType>
bool State<myType>::operator!=(const State & stateObj)
{
	bool notEqual = true;

	if (*this == stateObj)
		notEqual = false;

	return notEqual;
}

template<class myType>
const State<myType> & State<myType>::operator=(const  State<myType> & stateObj)
{
	int i, j;

	for (i = 0;i < SIZE;i++)
	{
		for (j = 0;j < SIZE;j++)
			block[i][j] = stateObj.block[i][j];
	}

	direc = stateObj.direc;
	bNo = stateObj.bNo;
	parent = stateObj.parent;

	return *this;
}

template<class myType>
void State<myType>::PrintPathReverse()
{
	State<myType> *stPtr = this;

	while (stPtr)
	{
		cout << *stPtr << endl;

		stPtr = stPtr->parent;
	}
}

template<class myType>
void State<myType>::PrintPath()
{
	Stack<State<myType> *> pathStack;
	State<myType> *stPtr = this;

	while (stPtr)
	{
		pathStack.Push(stPtr);
		stPtr = stPtr->parent;
	}

	stPtr = pathStack.Pop();
	cout << *stPtr << endl;
	bool isEmpty = pathStack.isEmpty();

	while (!isEmpty)
	{
		stPtr = pathStack.Pop();
		cout << "Rotate " << "block " << stPtr->stringBlockNO() << " " << stPtr->stringDirection() << endl << endl;
		cout << *stPtr << endl;
		isEmpty = pathStack.isEmpty();
	}

}

template<class myType>
void GameSolver<myType>::GenerateChildStates(State<myType> * stateObj)
{
	int i, j;
	Direction userDirec;
	BlockNO userbNo;
	State<myType> *newState;

	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 2;j++)
		{
			newState = new State<myType>;

			userDirec = static_cast<Direction>(j);
			userbNo = static_cast<BlockNO>(i);

			*newState = stateObj->Rotate(userDirec, userbNo);
			newState->SetParent(stateObj);

			myStack.Push(newState);
		}
	}
}

template<class myType>
GameSolver<myType>::GameSolver()
{
	currentState = new State<myType>;
}

template<class myType>
void GameSolver<myType>::ReadStatesFromFile(char* statesFile)
{
	ifstream readStates(statesFile);

	readStates >> initialState;
	readStates >> goalState;
}

template<class myType>
void GameSolver<myType>::DepthFirstSearchAlgo()
{
	*currentState = initialState;

	myStack.Push(currentState);

	bool isEmpty = myStack.isEmpty();
	bool isPresent;
	bool goalStateFound = (*currentState == goalState);

	cout << "Initial State is:" << endl;
	cout << initialState << endl;

	cout << "Goal State is:" << endl;
	cout << goalState << endl;

	cout << "PATH: " << endl << endl;

	while (!goalStateFound && !isEmpty)
	{
		currentState = new State<myType>;
		currentState = myStack.Pop();
		goalStateFound = (*currentState == goalState);
		isPresent = visitedArray.Find(currentState);

		if (!goalStateFound && !isPresent)
		{
			GenerateChildStates(currentState);
			visitedArray.AddItem(currentState);
		}
		isEmpty = myStack.isEmpty();
	}

	if (goalStateFound)
		currentState->PrintPath();
	else
		cout << "Failure! Solution not Possible";
}
