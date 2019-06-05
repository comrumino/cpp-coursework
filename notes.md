# Readings
* Lippman Sec 5.6 and 18.1 Exception Handling ( Skip Function try blocks Sec 18.1.3) May 15th
* Lippman Sec 3.4, 9.2.1, 9.2.3 Iterators  10.5.1 Iterator categories May 22nd
* VTBL pdf
* RVO pdf
* Lippman Sec 16.5 Template specialization
* Lippman Chapter 10 Generic Algorithms
* Effective C++: Read items 37, 42, 45, 50
* Effective C++: Items 44
* Design Patterns: Singleton, Proxy, Template method, Prototype, Observe
# Justifaction of value
* learning to solve problems using the C++ language and the object paradigm

## Philosophical jokes
* what software architects do is make something up and get everyone else to believe

## How to test
* Write tests first, otherwise implemented solution might not allow for automated testing    
* Mainline data, usage scenarios, boundary conditions, and stress conditions
* if a function takes a pointer test for nullptr, NULL, or 0 is passed
* Infrequently followed flows of logic

## Commenting    
* a null/pass statement should be commented `;`
* Stating intent (i.e. identify the purpose of a variable)
* Strategy or general design (i.e. summarize an algorithm)
* Stating invariants, pre- and post-conditions
* if the comment and code disagree, both are most likely wrong

## Design Philosophy
* easy to use right, hard to use wrong
* procedural paradigm, algorithms are required to solve our problem (provide a function values to provide answer)
* data-driven paradigm, the relationships between data and its abstractions is often more important than algorithms
* functional paradigm, composition of functions without state and mutable data are independent of execution order---so, the functions can be executed in parrallel...
* logical programs, logical expressions or statements to encapsulate the data and functions    
* object-based paradigm, organization is based on interactions of objects so that ultimately a solution can be found
* object-orientatd paradigm, adds inheritcance to polymorphism to object-based paradigm
* a function is where logically separate copmutation starts---best point to think about correct code and catch errors
* is it easy to know when a boundary condition is violated    

## Type Conversion
* nonbool -> if value == 0 then false, so nonzero is true
* undefined operation such as assign an out-of-range value to an object of signed type the result is undefined
* don't mixed signed and unsigned types
* `20 /* decimal */ 024 /* octal */ 0x14 /* hexidecimal */
* string literal is array of chars followed by a null character
* escape single quotes, double quotes, question mark, backslash
* specify the type of a literal e.g. `L'a'`
* double quote is a literal type char array and single quote is a literal type char

## Patterns
* [generalized hoisting](http://www.stroustrup.com/SCARY.pdf)
* template hoisting, type independent moved into base (e.g. IsEmpty(), GetNumElements(), etc)

## Terms
* RAII, exception safety for stack resources and locality of aquistion/release logic
* object, a region of memory which contains data and has a type
* declaration, makes a name known to program (variable declaration specifies name & type)
* identifiers, e.g. name
* variable provides us with a named storage that our programs can manipulate
* initialized, when an object is given a value at creation time
* default initialized, variables are given a default value when created
* assignment, overwrites an objects current value
* type specifier, the name of a type
* reference/alias, a name for already existing object aka the "lvalue" `int &refVal = ival; // refVal is another name for ival`
* clash, two incompatible declarations within the same scope
* pre-conditions, function argument requirements to run properly (doc if always good arguments, not too slow, not too complicated).
* post-conditions, the promis of what is returned
* invariant, a set of constraints which make the state valid (a rule for object value)
* state, the value of an object
* valid state, the idea of a valid value
* lvalues persist and rvalues are ephemeral
* lvalue is an object w/ an identifiable memory location
* rvalue is memory location
* index/subscript, the value you use in an subscript
* vector is template, which generates types such as `vector<int>`
* compound type, type defined in terms of others types such as pointer and reference
* redeclaration, return type and signatures match so redefined
* erroneous redclaration, return types differ
* overloaded, if signature differ
* polymorphism, refers to how some operations behave diffeenty to the same event, most likely virtual function
* class field, class data members which determine state
* class getters/setters, methods which provide an interface to access class fields (preferred to public avail)
* types breakdown: static type, integral types
* auto, type deduction looks at the initializer (RHS of initialization) to deduce what auto should be
* references, a type, bind the reference to initializer and cannot not be re-bindined, so it must be initialized
* manipulator, an operator that changes the behavior of stream
* assignment operation, changes the LHS
* new operator, `new type; // returns a valid address, memory is not initialized, and calls the class constructor`
* new operator, `new type(aValue); // initialize the allocated storage to aValue`
* new operator, `new type[N]; // allocate storage for N instance of type`
* delete operator, `new[]` requires free by `delete[]`, `delete expression // non-array`, and `delete [] expression // free an array`
* extraction, get from, `>>` 
* insertation, `<<`  write `x` to `s`, `s << x`
* concurrency, parrellism is normally described by Flynn's classification, multiple instruct and multiple data, tightly/loosely coupled
* tightly/loosely coupled systems, rather vauge term to describe the MIMD group. Shared-memory ~ tightly and distributed/wan/lan ~ loosely
* concurrent assignment, `x, y = y, x`
* [stack unwinding](http://www.stroustrup.com/except89.pdf), when an exception is thrown find a handling in the call chain.

## Condensed quarter one
* `for (auto element = values.begin(); element != values.end(); ++element) ` st auto `vector::iterator` or `const_iterator`
* `std::stringstream actual; for (auto value : values)`
* float, `float f = 45.6f; // the f suffix denotes a literal float constant`
* auto, the type is deduced by the value it is initialized to `template<typename T> struct TD; TD<decltype(var_auto_decl)> td;`
* auto, if a var is not initialized at declaration, then auto cannot be used
* array, dynamically allocated arrays don't define begin/end, C size check required---stl collection classes are preferred. 
* array, `auto array = new int[10];` or `auto array = std::make_unique<int[]>(10);`
* type define of `std::size_type` is `unsigned int`
* `string s5 = "hiya"; //copy initialization`
* `string s6("hiya"); //direct initialization`
* struct, members are public by default
* class, members are private by default
* namespace, don't use `using` declarations because they'll be copied into the including programs text
* factory function, a function that returns a class instance (e.g. make_unique which returns a unique_ptr instance)
* function prototype, define signature with defaults and all to the compiler
* signature, Type of arguments, Number of arguments, Sequence of arguments &, Qualifiers like const and volatile.
* lambda function, unnamed inline function
* `virtual void draw() const = 0;` indicates a pure virtual function so parent class is abstract
* `virtual void error(const std::string& msg);` indicates a simple virtual so we wish to inherit the def
* VTBL, each class with a virtual function has it's own VTBL which contains the addresses of it's virtual functions
* enum, one value out of a set, preferred for scope resolution, `enum Color` (old style) and `enum class Color` (new style)
* enum, name refers to the formal definition of establishing the number of something
* pointer, an object, initialize all pointers, behavior is not defined for all states `int \**p1 = nullptr/NULL/0;`
* pointer states: point to an object, point to a location past the end of an object, null, and invalid otherwise
* pointer undefined behavior: trying to access an object via a pointer when it does not point
* pointer, `const int *ptr = &foo; // NON-CONST pointer (memory value mutable), CONST data`
* pointer, `int * const ptr = &foo; // CONST pointer (memory value immutable), NON-CONST data.`
* unique ptr, use heap memory and destructor auto-delete, make unique returns this `std::unique_ptr<int> p2; //initializes to a nullptr`
* unique ptr, `std::unique_ptr<int[]> values2 = std::make_unique<int[]>(10);` Reminder, Almost Always `auto`
* upcast, convert into base class type
* downcast, by dynamic_cast mostly for debugging
* base class, should almost always have a virtual destructor (why?)
* Derived object has a subobject for itself and each base class which allows a reference/pointer to be bound to the base

## Condensed quarter two
* overloaded operator, redefine the built-in operation---member of class or operand of type class
* conversion operator, performs class-type/user-defined conversions (judicious, clear, avoid mutual conversions, multiple arith type convs)
* explicit conversion, implicit conversion restricted to expressions used as a condition
* function-objects, callable objects (class w/ operator def)---lambdas are function objects
* function-table, datastructure allowing search of function-objects with the same call signature---function templates
* function-template, library template representing any callable type
* vectors, contiguous storage can result in reallocation operations and reserve can help reduce the amoritized cost
* containers, template types that hold a collection of objects such that all objects are the same type
* container operations, ctor, add, remove, size, and iteration---algorithms cover search and such
* sequential container, elmts are ordered and accessed by position
* associative container, a map or a set such that state varies for the ordered and uniqueness of keys
* iterator (concept), general mechanism to move from one element to the next for the entire collection of objects
* iterator (type), defined by a container and instance of which is returned by `begin()` and `end()`
* iterator (object), an object st it can... reference, dereference, or equality check the element it denotes; also load next element in collection
* valid iterator, denotes element or off-the-{beginning,end}
* invalid iterator, iterators invalidated iff allocation or deallocation moves the elements it denotes
* invalidated iter example, elmt in doubly-linked list is removed, then only iterator denoting elmt are invalidated
* list, sequential container of doubly-linked elements
* adaptor, provides an interface to type which is consistent with another---stack, queue, priority_queue
* library headers, c headers have `ctype.h` and c++ headers have `cctype`
* subscripts, unchecked, outside of range is undefined, of empty is undefined
* strict weak ordering, the set of keys used for associative containers should be provably well-ordered by definition of the less-than operator
* ordered, less than is the binary operator for keys used to load and write elements
* unordered, hash equality is the binary operator for keys used to load and write elements
* class templates, cannot deduce template parameter types and each instantiation of a class template is an independent class with its own version of member functions
* class-template member function, only instantiated when use so if an instance does not meet the requirements of an operation it's all good
* template class, a class which has a class-template member (from class usage)
* More generally, if two specializations have the same number of partial evaluated args, then we must define the partial (or full) specialization such that it disambiguates specialization.
* Exceptions can only be one at a type so use primitive types in your exception classes
* default template arguments, default a type for a template
* function templates, can deduce template parameter types
* explicit instantiation, `extern` declares the arguments for all parameters and nonextern instationation---extern is promise of instantiation elsewhere to avoid overheard
* function parameter pack, one or more arguments
* instantiate, the replacement of template arguments with corresponding args based on a call.
* member template, member function that is a template (applies ordinary non template classes aswell)
* template nontype parameters, intergral parameters are consts, refs/ptrs have lifetimes
* template specialization, all parameters of template function are specified. class template and member templates allow partial specialization via partial evalation of the base template
* template type parameter, named used to abstract a type (that is the parameters to the template dipshit)
* trailing return types, `auto fcn(It beg, It end) -> typename remove_reference<decltype(*beg)>::type` if the function template return type is a related type of a template type parameter, instantiation of all possibilities is burdensome
* type transformation template, metaprogramming, tranform a given template type parameter to a related type
* variadic template, varying number of template arguments---use template parmeter pack

## Shared pointers
* shared pointer, syntax `std::shared_ptr<int[]> sharedValues = std::make_shared<int[]>(20);` allows multiple clients to share access to that dynamically allocated heap memory by using reference counting use unique pointer unless you really need sharing
* void pointers, deal with memory as memory
* read it right to left for complicated point or reference declarations `int *&r`
* `const char* q = hello; // can't modify the data being pointed at, but can change what we point at`
* `char* const r = hello; // can't change what is pointed at, but can change the value at what we point`
* `const char* const s = hello; // cant change what is pointed at and can't change the value at what we point` 
* `int* myPtr = new int; // allocate storage for an int and assign the pointer to the storage to myPtr`
* `new int(33); // to the address (the pointer) of a newly allocated int with the value of 33`
* pointer arithmetic, `int* p; int arr[2] = {0, 1}; p = arr; ++p;`

## Compile
* gdb: `-ggdb`
* flags: `-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused`
* `g++ -fPIC ./include/*.cpp -shared -Wl,-soname,libUnitLite.so  -o ./lib/libUnitLite.so`
* `reset && g++ ./include/Main.cpp ./assignment-2/SwapTest.cpp ./assignment-2/jstronz-2-1.cpp -L./lib -lUnitLite`
* `%s/^[^ ]* \([^(]*\)() {/TEST(\1, \1) {/g`
* `astyle --lineend=linux --style=linux ./*`

# References
* https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet
* [Architectural Principles That Prevent Code Modification](https://www.owasp.org/index.php/Architectural_Principles_That_Prevent_Code_Modification_or_Reverse_Engineering#Controls)
* [Risks, explainations, and mitigations](https://www.owasp.org/index.php/Technical_Risks_of_Reverse_Engineering_and_Unauthorized_Code_Modification)
* [Licensing security pt 2](https://blogs.flexera.com/ecm/2016/03/what-you-need-to-know-about-software-licensing-security-part-2/)
* [Licensing security pt 1](https://blogs.flexera.com/ecm/2016/03/what-you-need-to-know-about-software-licensing-security-part-1/)
* [openssl official](https://www.openssl.org/)
* [Openssl asymmetrict](http://www.firmcodes.com/asymmetric/)
* [Openssl forum](https://bytes.com/topic/c/answers/490515-please-help-how-do-i-include-openssl-my-code)
* [Example in C++](https://eclipsesource.com/blogs/2016/09/07/tutorial-code-signing-and-verification-with-openssl/)
* [C++ best example](https://gist.github.com/irbull/08339ddcd5686f509e9826964b17bb59)
* http://www.stroustrup.com/Programming/PPP-style-rev3.pdf
* [Amortized Analysis, CMU Algo](https://www.cs.cmu.edu/afs/cs/academic/class/15451-s07/www/)

# UML: Identity, behavior, state (IBS)
* unified modeling language
* object idenity, how the object is distinguished from all other objects
* object behavior, responses to events or messages from other objects (C++ even is a function call)
* object state, the current value of all attributes
* OO programming, organization is based on interactions of objects so that ultimately a solution can be found
* OO requirements, method of analysis that captures the behavioral expectations of a system
* OO design, a way to decompose a system or physiscal process into logical models and physical models
* OO analysis, to take a problem domain and identify entities/objects and classes. Nouns, verbs, adjectives -> identity/object, behavior/action, state/properties.
* Class-responsibility-collaboration cards (CRC cards),
    1. class name
    2. super-sub classes
    3. responsibilities class
    4. names of other classes that it will interact with
    5. author name

## Object model framework
**Major elements**    
* abstraction, identify characteristics which distinguish it for conceptual boundaries (entity abstractions & action abstraction)
* encapsulation, should be a consequence of abstraction
* modularity, a partition of a logical components which form a program 
    1. minimize interfaces among different parts of the organization.
    2. maximize stability of module interfaces
    3. improve security (e.g. exposure of data)
    4. inheritance:  
        a. implementation inheritance, data of function implementations  
        b. interface inheritcance, function signatures  
        c. abstrace, all of the above  
* hierarchy, keep your shit flat---fewer multiple inheritance and interfaces
    1. ISA, inheritance; a is-a relationship
    2. HASA, composition and aggregation; a has-a relationship
        a. reduce namespace pollution
        b. concept of ownership

**Minor elements**    
* typing, provides charactization of the properties
    1. variations of typing:
        a. strong typing, each signature of operation is defined (no type classes can interact freely)
        b. weak typing, possible to suppress type information
        c. none typing, no enforcement of signature
    2. static-typing/static-binding/early-binding, variable names are bound to the types and variables are fixed at compile
    3. dyanmic-typing/dyamic-binding/late-binding, types of the variables and expressions are not known until runtime
* concurrency, the ability to wait on a Future at the same damn time
* persistence, 
    1. the lifetime of an object, is it transient
    2. local variables only persist in scope
    3. lifetime for which the extent is diffent from their scope
    4. persist between executions, between versions, between the life of the program

**Class Diagrams**    
* object name, or class name, the identifier
* object properties, a way to capture structural features (i.e. attributes, associations, operations)
    1. attributes, describe a characteristic `visibility name:type = optional default value`    
        a. visibility: public (all objects), protected (classes/subclasses), private (within instance)    
        b. name, id of attr & type, of attr    
    2. associations, relates to others and by multiplicity  
    3. operations, `visibility name(parameter list): return type`    
        a. param, `direction name:type = optional default value`      
        b. in, no change; out, change always; inout, might change      
        c. constructors, init objects      
        d. destructors, executed when instances no longer exists and fress system resources  
        e. accessors, i.e. get, is  
        f. mutators, alter values of attrs  
* use protected or private for operations that only support behavioral responsibilites
**Class Relationships**
* Generalization, class is generalized (superclass) from specialization (subclass)
* Association, structural relations
    1. multiplicity/cardinality, how many `1..*` is one to any
    2. containment, a whole part made up of objects    
        a. aggregation, one or more parts which can exist independently        
        b. composition, one or more parts strong ownership so parts canot exist outside        
* Dependency, one class requires the behavior of another object    
