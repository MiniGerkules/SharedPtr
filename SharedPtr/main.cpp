#include <iostream>
#include "SharedPtr.h"
#include "WeakPtr.h"
#include "MakeMyShared.h"

int main()
{
    // SharedPtr tests
    std::cout << "SharedPtr tests" << std::endl;

    SharedPtr<int> smartPointer1(new int[5] {1, 2, 3, 4, 5}, true);

    const int* array = smartPointer1.Get();
    for (size_t i = 0; i < 5; ++i)
        std::cout << array[i] << " ";

    SharedPtr<int> smartPointer2 = smartPointer1;
    std::cout << "\n\n" << smartPointer1.UseCount() << std::endl;
    std::cout << smartPointer2.UseCount() << std::endl;

    SharedPtr<int> smartPointer3 = std::move(smartPointer1);
    std::cout << '\n' << smartPointer1.UseCount() << std::endl;
    std::cout << smartPointer2.UseCount() << std::endl;
    std::cout << smartPointer3.UseCount() << std::endl;

    SharedPtr<int> smartPointer4;
    smartPointer4 = smartPointer3;
    std::cout << '\n' << smartPointer1.UseCount() << std::endl;
    std::cout << smartPointer2.UseCount() << std::endl;
    std::cout << smartPointer3.UseCount() << std::endl;
    std::cout << smartPointer4.UseCount() << std::endl;

    SharedPtr<int> smartPointer5;
    smartPointer5 = std::move(smartPointer4);
    std::cout << '\n' << smartPointer1.UseCount() << std::endl;
    std::cout << smartPointer2.UseCount() << std::endl;
    std::cout << smartPointer3.UseCount() << std::endl;
    std::cout << smartPointer4.UseCount() << std::endl;
    std::cout << smartPointer5.UseCount() << std::endl;

    SharedPtr<int> smartPointer6 = smartPointer2;
    std::cout << '\n' << smartPointer1.UseCount() << std::endl;
    std::cout << smartPointer2.UseCount() << std::endl;
    std::cout << smartPointer3.UseCount() << std::endl;
    std::cout << smartPointer4.UseCount() << std::endl;
    std::cout << smartPointer5.UseCount() << std::endl;
    std::cout << smartPointer6.UseCount() << std::endl;

    SharedPtr<int> smartPointer7 = std::move(smartPointer2);
    std::cout << '\n' << smartPointer1.UseCount() << std::endl;
    std::cout << smartPointer2.UseCount() << std::endl;
    std::cout << smartPointer3.UseCount() << std::endl;
    std::cout << smartPointer4.UseCount() << std::endl;
    std::cout << smartPointer5.UseCount() << std::endl;
    std::cout << smartPointer6.UseCount() << std::endl;
    std::cout << smartPointer7.UseCount() << std::endl;

    // WeakPtr tests
    std::cout << "\nWeakPtr tests" << std::endl;
    WeakPtr<int> weakPointer1(smartPointer7);
    std::cout << smartPointer7.UseCount() << std::endl;

    std::cout << std::endl;
    SharedPtr<int> smartPointer8 = weakPointer1.Lock();
    std::cout << smartPointer8.UseCount() << std::endl;

    std::cout << std::endl;
    std::cout << smartPointer1.UseCount() << std::endl;
    WeakPtr<int> weakPointer2(smartPointer1);
    weakPointer2 = weakPointer1;
    std::cout << smartPointer1.UseCount() << std::endl;
    WeakPtr<int> weakPointer3 = std::move(weakPointer1);
    std::cout << smartPointer8.UseCount() << std::endl;

    // MakeMyShared tests
    std::cout << "\nMakeMyShared tests" << std::endl;
    SharedPtr<Person> person1 = MakeMyShared("Vladimir", 68);
    std::cout << person1.UseCount() << std::endl;
    SharedPtr<Person> person2 = person1;
    std::cout << person1.UseCount() << std::endl;
    std::cout << person2.UseCount() << std::endl;
    person2 = MakeMyShared("Aleksandr", 66)
}