#include <iostream>
using namespace std;

class MyClass{
    public:
        MyClass(){}; // explicit constructor
        MyClass(int a){}; // explicit constructor
};

int main(){

//         WIDENING
//    ──────────────────→
//    int → long long → double
//    float → double


//         NARROWING
//    ←──────────────────
//    double → float → int
//    long long → int


    // Initialization
    // Default Initialization - No initializer is provided. For a local int, the value is indeterminate:, 
    //          For a class: default constructor is called
    int x1;
    MyClass obj1;
    
    
    // Copy Initialization - Uses =: 
    //           For classes: It permits implicit conversions, which is important with explicit constructors.
    int x2 = 10; 
    MyClass obj2 = 10;
    int x2f = 10.5; // ✅ 
    
    
    // Direct Initialization - Uses parentheses: 
    //           For classes: It directly initializes the object using the specified arguments.
    
    int x3(10); 
    MyClass obj3(10);
    int x3f(3.14); // ✅

    // Direct-list Initialization - Uses {} directly: 
    //           For classes: A major benefit is that narrowing conversions are prohibited:
    int x4{10};
    MyClass obj4{10};
    // int x4f{10.5}; // ❌
    
    // Copy-list Initialization - Uses = {}: 
    //           For classes: Like list initialization, it also prevents narrowing: There is also an important difference from direct-list initialization regarding explicit constructors.
    int x5 = {10};
    MyClass obj5 = {10};
    // int x5f = {10.5};   // ❌ Error


    // Value Initialization - Usually seen as {}: 
    //           For an int, this gives: 0, For a class: the object is value-initialized, which generally means its default constructor is used, with additional zero-initialization rules depending on the type.
    int x6{}; // initializes with 0
    MyClass obj6{};


    cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<x5<<" "<<x6<<" "<<x7<<endl;
}