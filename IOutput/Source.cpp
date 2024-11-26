#include <iostream>
using namespace std;

class IOutput
{
public:

    virtual void Show() const = 0;
    virtual void Show(const char* info) const = 0;
    virtual ~IOutput() = default;
};

class IMath
{
public:

    virtual int Max() const = 0;
    virtual int Min() const = 0;
    virtual float Avg() const = 0;
    virtual bool Search(int valueToSearch) const = 0;
    virtual ~IMath() = default;
};

class ISort
{
public:

    virtual void SortAsc() = 0;
    virtual void SortDesc() = 0;
    virtual void SortByParam(bool isAsc) = 0;
    virtual ~ISort() = default;
};

class Array : public IOutput, public IMath, public ISort
{
private:

    int* elements;
    int size;

public:

    Array(int* elems, int sz) : size(sz) 
    {
        elements = new int[size];

        for (int i = 0; i < size; i++) 
        {
            elements[i] = elems[i];
        }
    }

    ~Array()
    {
        delete[] elements;
    }

    void Show() const override 
    {
        for (int i = 0; i < size; i++)
        {
            cout << elements[i] << " ";
        }
        cout << endl;
    }

    void Show(const char* info) const override 
    {
        cout << info << ": ";
        Show();
    }

    int Max() const override 
    {
        int maxVal = elements[0];

        for (int i = 1; i < size; i++)
        {
            if (elements[i] > maxVal)
            {
                maxVal = elements[i];
            }
        }
        return maxVal;
    }

    int Min() const override
    {
        int minVal = elements[0];
        for (int i = 1; i < size; i++) 
        {
            if (elements[i] < minVal) 
            {
                minVal = elements[i];
            }
        }
        return minVal;
    }

    float Avg() const override 
    {
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += elements[i];
        }
        return static_cast<float>(sum) / size;
    }

    bool Search(int valueToSearch) const override
    {
        for (int i = 0; i < size; i++)
        {
            if (elements[i] == valueToSearch)
            {
                return true;
            }
        }
        return false;
    }

    void SortAsc() override
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++) 
            {
                if (elements[j] > elements[j + 1]) 
                {
                    swap(elements[j], elements[j + 1]);
                }
            }
        }
    }

    void SortDesc() override 
    {
        for (int i = 0; i < size - 1; i++) 
        {
            for (int j = 0; j < size - i - 1; j++) 
            {
                if (elements[j] < elements[j + 1]) 
                {
                    swap(elements[j], elements[j + 1]);
                }
            }
        }
    }

    void SortByParam(bool isAsc) override 
    {
        if (isAsc) 
        {
            SortAsc();
        }

        else 
        {
            SortDesc();
        }
    }
};

int main()
{
    int arr[] = { 3, 1, 9, 5, 7 };
    int size = sizeof(arr) / sizeof(arr[0]);

    Array array(arr, size);

    array.Show();
    array.Show("Array");

    cout << "Max: " << array.Max() << endl;
    cout << "Min: " << array.Min() << endl;
    cout << "Average: " << array.Avg() << endl;
    cout << "Search 7: " << (array.Search(7) ? "Found" : "Not Found") << endl;

    array.SortAsc();
    array.Show("Sorted Ascending");

    array.SortDesc();
    array.Show("Sorted Descending");

    array.SortByParam(true);
    array.Show("Sorted By Param (Ascending)");

    array.SortByParam(false);
    array.Show("Sorted By Param (Descending)");

    return 0;
}