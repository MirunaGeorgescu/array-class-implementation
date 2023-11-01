#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("TextFile1.txt");
class Array
{
	// PRIVATE ATTRIBUTES
	int length;
	double* array;

public:

	// PUBLIC METHODS
	// getters and setters  
	int getLength()
	{
		return this->length;
	}

	void setLength(int length)
	{
		// since both the attribute and the parameter have the same name, 
		// we need to use the this keyword to differentiate between them
		if (length > 0)
			this->length = length;

	}


	void setValues(double values[])
	{
		// sets the values of the array to the values of the parameter
		for (int i = 0; i < length; i++)
			array[i] = values[i];
	}

	double* getValues()
	{
		// this method returns a copy of the array, since we don't want the user to be able to modify the array
		double* copy = new double[length];

		for (int i = 0; i < length; i++)
			copy[i] = array[i];

		return copy;
	}


	// input and output
	void displayValues()
	{
		for (int i = 0; i < length; i++)
			cout << array[i] << " ";
	}

	void inputValues()
	{
		int length; cout << "The length of the array: "; cin >> length;
		// because both the variable and the attribute have the same name, we need to
		// use the this keyword to differentiate between them
		this->length = length;

		double* newArray = new double[length];
		cout << "The elements of the array: ";
		for (int i = 0; i < length; i++)
			cin >> newArray[i];

		// if array had any previous values, we need to delete them, and then assign the new values
		delete[] array;
		this->array = newArray;
	}


	// other methods
	// the maximumValue method returns the maximum value in the array
	double maximumValue()
	{
		// the this keyword is optional here, since it's clear that we are referring to the attribute
		double maxValue = this->array[0];
		for (int i = 1; i < this->length; i++)
			if (maxValue < this->array[i])
				maxValue = array[i];
		return maxValue;
	}


	// the addNewComponents method updates the length of the array, and initializes 
	// the new components with a given number
	void addNewComponents(int const newLength, int const number)
	{
		if (newLength <= this->length)
		{
			cout << "The given length is not larger than the the length of the current array, so we can't add new components!" << '\n';
		}
		else
		{
			double* newArray = new double[newLength];

			// the this keyword is optional here, since it's clear that we are referring to the attribute
			// we copy the old values into the new array
			for (int i = 0; i < this->length; i++)
				newArray[i] = this->array[i];

			// we initialize the new components with the given number
			for (int i = this->length; i < newLength; i++)
				newArray[i] = number;

			this->length = newLength;

			// if array had any previous values, we need to delete them, and then assign the new values
			delete[] this->array;
			this->array = newArray;
		}
	}


	// OPERATORS
	// the assignment operator
	Array operator=(Array sursa)
	{
		this->length = sursa.length;

		// if the array had any previous values, we need to delete them, and then assign the new values
		if (this->array != nullptr)
			delete[] this->array;

		this->array = new double[this->length];
		for (int i = 0; i < this->length; i++)
			this->array[i] = sursa.array[i];

		// the assignment operator returns a reference to the current object
		return *this;
	}

	Array& operator++()
	{
		for (int i = 0; i < length; i++)
			this->array[i]++;
		return *this;
	}

	Array& operator++(int)
	{
		Array copieVector(*this);
		for (int i = 0; i < length; i++)
			this->array[i]++;
		return copieVector;
	}

	void operator+=(int nr)
	{
		for (int i = 0; i < this->length; i++)
			this->array[i] += nr;

	}

	double operator[] (const int i)
	{
		return array[i];
	}

	operator int()
	{
		return this->length;
	}



	// CONSTRUCTORS
	// the default constructor
	Array(const int length, double values[])
	{
		this->setLength(length);
		array = new double[length];
		this->setValues(values);
	}

	// this constructor initializes the array with a given number on all components
	Array(const int value, const int length)
	{
		this->array = new double[length];
		for (int i = 0; i < length; i++)
			array[i] = value;
		this->setLength(length);
	}

	// constructor without parameters: the array will have length 0, and the array will be nullptr
	Array() : length(0), array(nullptr)
	{

	}

	// copy constructor
	Array(const Array& obiect)
	{
		this->array = new double[obiect.length];
		for (int i = 0; i < obiect.length; i++)
			this->array[i] = obiect.array[i];
		this->length = obiect.length;
	}

	// constructor with a single parameter: a boolean value
	// if the value is true, we read the values of the array from the keyboard
	// if the value is false, we read the values of the array from a file
	Array(const bool val)
	{
		if (val == true)
		{
			int length; cout << "The length of the array: "; cin >> length;
			// because both the variable and the attribute have the same name, we need to
			// use the this keyword to differentiate between them
			this->length = length;

			// we create a new array, and we read the values from the keyboard
			double* newArray = new double[length];

			cout << "The values of the array: ";
			for (int i = 0; i < length; i++)
				cin >> newArray[i];

			// if array had any previous values, we need to delete them, and then assign the new values
			delete[] array;
			this->array = newArray;
		}
		else
		{
			int length;  fin >> length;
			// because both the variable and the attribute have the same name, we need to
			// use the this keyword to differentiate between them
			this->length = length;

			double* newArray = new double[length];

			for (int i = 0; i < length; i++)
				fin >> newArray[i];

			// if array had any previous values, we need to delete them, and then assign the new values
			delete[] array;
			this->array = newArray;
		}
	}

	// constructor with a single parameter: an integer value representing the length of the array
	// the array will be initialized with 0 on all components
	Array(int length)
	{
		this->array = new double[length];
		for (int i = 0; i < length; i++)
			array[i] = 0;
		this->setLength(length);
	}


	//DESTRUCTOR
	~Array()
	{
		delete[] this->array;
	}

	//FRIEND FUNCTIONS
	friend Array operator+(Array v1, Array v2);
	friend Array operator-(Array v1, Array v2);
	friend void operator-=(Array v, int nr);
	friend bool operator==(Array v1, Array v2);
	friend bool operator!=(Array v1, Array v2);
	friend int length(Array v);
	friend ostream& operator<<(ostream& console, Array v);
	friend istream& operator>>(istream& console, Array& v);
	friend Array operator-(Array v);
	friend bool operator!(Array v);
	friend Array operator+=(Array v1, Array V2);
};

// FRIEND FUNCTIONS
// the operator+ returns a new array, the elements of the new array are the sum of
//  the two elements on the same position in the two arrays
Array operator+(Array array1, Array array2)
{

	if (array1.length == array2.length)
	{
		double* arrayOfSums = new double[array1.length];
		for (int i = 0; i < array1.length; i++)
			arrayOfSums[i] = array1.array[i] + array2.array[i];

		Array returnedArray(array1.length, arrayOfSums);
		return returnedArray;

	}
	else
		cout << "The arrays have different lengths" << endl;
}

// the operator- returns a new array, the elements of the new array are the difference of
//  the two elements on the same position in the two arrays
Array operator-(Array array1, Array array2)
{

	if (array1.length == array2.length)
	{
		double* arrayOfDifs = new double[array1.length];
		for (int i = 0; i < array1.length; i++)
			arrayOfDifs[i] = array1.array[i] - array2.array[i];

		Array returnedArray(array1.length, arrayOfDifs);
		return returnedArray;

	}
	else
		cout << "The arrays have different lengths" << endl;
}

// the operator- returns an array, the elements of this array are the opposite of
//  the elements of the inital array
Array operator-(Array initialArray)
{
	for (int i = 0; i < initialArray.length; i++)
		initialArray.array[i] = (-1) * initialArray.array[i];
	return initialArray;
}

// the operator-= subtracts a given number from all the elements of the array
void operator-=(Array array, int value)
{
	for (int i = 0; i < array.length; i++)
		array.array[i] -= value;
}

// the operator== reurns false if the arrays have different lengths, or if there is at least one
//  element that is different in the two arrays, and true otherwise
bool operator==(Array v1, Array v2)
{
	if (v1.length != v2.length)
		return false;

	for (int i = 0; i < v1.length; i++)
		if (v1.array[i] != v2.array[i])
			return false;

	return true;
}

// similarly, the operator!= reurns true if the arrays have different lengths, or if there is at least one
//  element that is different in the two arrays, and false otherwise
bool operator!=(Array v1, Array v2)
{
	if (v1.length != v2.length)
		return true;
	for (int i = 0; i < v1.length; i++)
		if (v1.array[i] != v2.array[i])
			return true;
	return false;
}

// the length function returns the length of the array
int length(Array v)
{
	return v.length;
}


// the operator<< prints the length of the array and the elements of the array
ostream& operator<<(ostream& console, Array array)
{
	console << "The lenght of the array is: " << array.length << endl;

	console << "The elements of the array are: ";
	for (int i = 0; i < array.length; i++)
		console << array.array[i] << " ";
	cout << endl;

	return console;
}

// the operator>> reads the length of the array and the elements of the array
istream& operator>>(istream& console, Array& array)
{
	cout << "The length of the array: ";
	console >> array.length;

	cout << "The elements of the array: ";
	double* newArray = new double[array.length];
	for (int i = 0; i < array.length; i++)
		console >> newArray[i];

	// if the array already has elements, we delete the old array, before assigning the new one
	if (array.array != nullptr)
		delete[] array.array;

	array.array = newArray;

	return console;
}

// the operator! returns true if the array has at least one element, and false otherwise
bool operator!(Array array)
{
	if (array.length != 0)
		return true;
	else
		return false;
}

// the operator+= adds the elements of the second array to the elements of the first array
Array operator+=(Array array1, Array array2)
{
	if (array1.length == array2.length)
	{
		for (int i = 0; i < array1.length; i++)
			array1.array[i] += array2.array[i];
		return array1;
	}
	else cout << "The arrays don't have the same sumber of elemenets!" << endl;
}


// OTHER FUNCTIONS

// the sumArray is a global variable, it is used to store the sum of the arrays
Array sumArray;

// the st, nd, rd, th functions are used to print the correct ordinal number
void st(int i)
{
	std::cout << endl;
	std::cout << "The " << i << "st array ----------------------------------------------------------------------------------------" << endl;

	Array inputArray;
	// inputValues is a function that reads the length of the array and the elements of the array
	inputArray.inputValues();

	if (length(inputArray) == length(sumArray))
		sumArray = sumArray + inputArray;
	else
		if (length(inputArray) > length(sumArray))
			cout << "The " << i << "st array has more elements than the sum array" << endl;
		else
			cout << "The " << i << "st array has less elements than the sum array" << endl;
}

void nd(int i)
{
	std::cout << endl;
	std::cout << "The " << i << "nd array ----------------------------------------------------------------------------------------" << endl;

	Array inputArray;
	// inputValues is a function that reads the length of the array and the elements of the array
	inputArray.inputValues();

	if (length(inputArray) == length(sumArray))
		sumArray = sumArray + inputArray;
	else
		if (length(inputArray) > length(sumArray))
			cout << "The " << i << "nd array has more elements than the sum array" << endl;
		else
			cout << "The " << i << "nd array has less elements than the sum array" << endl;
}

void rd(int i)
{
	std::cout << endl;
	std::cout << "The " << i << "rd array ----------------------------------------------------------------------------------------" << endl;

	Array inputArray;
	// inputValues is a function that reads the length of the array and the elements of the array
	inputArray.inputValues();

	if (length(inputArray) == length(sumArray))
		sumArray = sumArray + inputArray;
	else
		if (length(inputArray) > length(sumArray))
			cout << "The " << i << "rd array has more elements than the sum array" << endl;
		else
			cout << "The " << i << "rd array has less elements than the sum array" << endl;
}

void th(int i)
{
	std::cout << endl;
	std::cout << "The " << i << "th array ----------------------------------------------------------------------------------------" << endl;

	Array inputArray;
	// inputValues is a function that reads the length of the array and the elements of the array
	inputArray.inputValues();

	if (length(inputArray) == length(sumArray))
		sumArray = sumArray + inputArray;
	else
		if (length(inputArray) > length(sumArray))
			cout << "The " << i << "th array has more elements than the sum array" << endl;
		else
			cout << "The " << i << "th array has less elements than the sum array" << endl;
}

int main()
{
	int numberOfArrays;  std::cout << "Number of arrays: "; cin >> numberOfArrays;

	// the first array is a special case, we add it directly to sumArray
	// we also print the maximum value of the first array
	std::cout << "The first array ----------------------------------------------------------------------------------------" << endl;
	sumArray.inputValues();
	std::cout << "The element with the maximum value in this array is: " << sumArray.maximumValue() << endl;

	// for the next arrays, we add them to the sumArray, if they have the same length as the sumArray
	for (int i = 2; i <= numberOfArrays; i++)
	{
		switch (i % 10)
		{
		case 1:
			st(i); break;
		case 2:
			nd(i); break;
		case 3:
			rd(i); break;
		default:
			th(i); break;
		}
	}

	// we print the sumArray
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "The sum of the " << length(sumArray) << " elements in the arrays is: ";
	sumArray.displayValues();

	cout << endl << endl;
}