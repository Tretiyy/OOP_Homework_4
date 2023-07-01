#include <iostream>
using namespace std;

class SetOfIntegers
{
public:
    SetOfIntegers() : elements(nullptr), size(0) {} // constructor default

    SetOfIntegers(const int* arr, int arrSize) // constructor with params
    {
        elements = new int[arrSize];
        size = 0;
        for (int i = 0; i < arrSize; i++)
        {
            if (!contains(arr[i]))
            {
                elements[size] = arr[i];
                size++;
            }
        }
    }

    SetOfIntegers(const SetOfIntegers& other) : size(other.size) // constructor copy
    {
        elements = new int[size];
        for (int i = 0; i < size; i++)
            elements[i] = other.elements[i];
    }

    ~SetOfIntegers() // destructor
    {
        delete[] elements;
    }


    bool contains(int element) const // check
    {
        for (int i = 0; i < size; i++) 
        {
            if (elements[i] == element)
                return true;
        }
        return false;
    }


    void add(int element) // add element
    {
        if (!contains(element))
        {
            int* newArray = new int[size + 1];
            for (int i = 0; i < size; i++)
                newArray[i] = elements[i];
            newArray[size] = element;
            delete[] elements;
            elements = newArray;
            size++;
        }
    }

    SetOfIntegers operator+(const SetOfIntegers& other) const // merge
    {
        SetOfIntegers mergedSet(*this);
        for (int i = 0; i < other.size; i++)
            mergedSet.add(other.elements[i]);
        return mergedSet;
    }

    SetOfIntegers& operator+=(const SetOfIntegers& other) // add another
    {
        for (int i = 0; i < other.size; i++)
            add(other.elements[i]);
        return *this;
    }

    void remove(int element) // remove element
    {
        if (contains(element)) 
        {
            int* newArray = new int[size - 1];
            int newArrayIndex = 0;
            for (int i = 0; i < size; i++) 
            {
                if (elements[i] != element)
                {
                    newArray[newArrayIndex] = elements[i];
                    newArrayIndex++;
                }
            }
            delete[] elements;
            elements = newArray;
            size--;
        }
    }

    SetOfIntegers& operator-=(const SetOfIntegers& other) // remove another
    {
        for (int i = 0; i < other.size; i++)
            remove(other.elements[i]);
        return *this;
    }

    SetOfIntegers operator-(const SetOfIntegers& other) const // difference
    {
        SetOfIntegers diffSet(*this);
        diffSet -= other;
        return diffSet;
    }

    SetOfIntegers operator*(const SetOfIntegers& other) const // intersection
    {
        SetOfIntegers intersectionSet;
        for (int i = 0; i < size; i++)
        {
            if (other.contains(elements[i]))
                intersectionSet.add(elements[i]);
        }
        return intersectionSet;
    }

    SetOfIntegers& operator=(const SetOfIntegers& other) // assign to another
    {
        if (this == &other)
            return *this;
        delete[] elements;
        size = other.size;
        elements = new int[size];
        for (int i = 0; i < size; i++)
            elements[i] = other.elements[i];
        return *this;
    }

    bool operator==(const SetOfIntegers& other) const // comparsion
    {
        if (size != other.size)
            return false;

        for (int i = 0; i < size; i++) 
        {
            if (!other.contains(elements[i]))
                return false;
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const SetOfIntegers& set) // output
    {
        os << "{ ";
        for (int i = 0; i < set.size; i++)
            os << set.elements[i] << " ";
        os << "}";
        return os;
    }

    friend istream& operator>>(istream& is, SetOfIntegers& set) // input
    {
        cout << "Enter the number of elements in the set: ";
        int numElements;
        is >> numElements;
        cout << "Enter the elements separated by spaces: ";
        int element;
        for (int i = 0; i < numElements; i++) 
        {
            is >> element;
            set.add(element);
        }
        return is;
    }
private:
    int* elements;
    int size;
};

int main()
{
    SetOfIntegers set1;
    cout << "Enter elements for set1:\n";
    cin >> set1;
    cout << "set1: " << set1 << endl;

    SetOfIntegers set2;
    cout << "Enter elements for set2:\n";
    cin >> set2;
    cout << "set2: " << set2 << endl;

    SetOfIntegers set3(set1);
    cout << "set3 (copy of set1): " << set3 << endl;

    set3 += set2;
    cout << "set3 after merging set2: " << set3 << endl;

    set3.remove(5);
    cout << "set3 after removing 5: " << set3 << endl;

    SetOfIntegers set4 = set1 - set2;
    cout << "set4 (difference of set1 and set2): " << set4 << endl;

    SetOfIntegers set5 = set1 * set2;
    cout << "set5 (intersection of set1 and set2): " << set5 << endl;

    SetOfIntegers set6;
    cout << "Enter elements for set6:\n";
    cin >> set6;
    cout << "set6: " << set6 << endl;

    set6 = set1;
    cout << "set6 after assignment from set1: " << set6 << endl;

    bool isEqual = set1 == set2;
    cout << "set1 and set2 are " << (isEqual ? "equal" : "not equal") << endl;

    system("pause");

    return 0;
}