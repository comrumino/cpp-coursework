# General
* learning to solve problems using the C++ language and the object paradigm

## Philosophical jokes
* what software architects do is make something up and get everyone else to believe
* easy to use right, hard to use wrong
## Assignment Checklist
* Write tests
* Write solution
* Check style
* Only include `.cpp`, `.h`, and unit tests `.cpp` all in the same directory    
* Use the same function and class names as specified
* Clarity and consistency of style 30%, Correctness of solution 40%, Demonstrated testing of the solution 30%
* Code listing, copy of output, and annotated test cases

## How to test
* Write tests first, otherwise implemented solution might not allow for automated testing    
* Mainline data, usage scenarios, boundary conditions, and stress conditions
* if a function takes a pointer test for nullptr, NULL, or 0 is passed
* input is outside of a boundary

## Style
* type names are capital
* non-type names are not capital
* underscores for multipart names
* length of name should be roughly proportional to the size of its scope
* initialize unless you have a good reason not to
* http://www.stroustrup.com/Programming/PPP-style-rev3.pdf
* almost always auto: choice between auto and explicit, choose auto. changing an object iterated requires fewer changes

## Things to know
* assignment changes the LHS

## Commenting    
* a null statement should be commented `;`
* Stating intent (i.e. identify the purpose of a variable)
* Strategy or general design (i.e. summarize an algorithm)
* Stating invariants, pre- and post-conditions
* if the comment and code disagree, both are most likely wrong

## Design Philosophy
* procedural paradigm, algorithms are required to solve our problem (provide a function values to provide answer)
* data-driven paradigm, the relationships between data and its abstractions is often more important than algorithms
* functional paradigm, composition of functions without state and mutable data are independent of execution order---so, the functions can be executed in parrallel...
* logical programs, logical expressions or statements to encapsulate the data and functions    
* object-based paradigm, organization is based on interactions of objects so that ultimately a solution can be found
* object-orientatd paradigm, adds inheritcance to polymorphism to object-based paradigm

### Design Considerations
* a function is where logically separate copmutation starts---best point to think about correct code and catch errors
* is it easy to know when a boundary condition is violated    

### UML
* unified modeling language

#### Identity, behavior, state (IBS)
* object idenity, how the object is distinguished from all other objects
* object behavior, responses to events or messages from other objects (C++ even is a function call)
* object state, the current value of all attributes

#### Terms
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

### Object model framework
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
* concurrency, the ability to be Future at the same damn time
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
    3. ooperations, `visibility name(parameter list): return type`    
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


## Types
* unsigned type when you know that the the values cannot be negative
* int for integer arithmetic
* short is usually too small and long is often has the same size as int
* use long long when values are larger than the minimum gauranteed size of an int
* char or bool should only be used to hodl characters or truth values
* use double for floating-point arithematic, long double is unnecessary and often entails run-time cost
* integral types
* auto, type deduction looks at the initializer to deduce what auto should be

## Type Conversion
* nonbool -> if value == 0 then false, so nonzero is true
* undefined operation such as assign an out-of-range value to an object of signed type the result is undefined
* don't mixed signed and unsigned types
* `20 /* decimal */ 024 /* octal */ 0x14 /* hexidecimal */
* string literal is array of chars followed by a null character
* escape single quotes, double quotes, question mark, backslash
* specify the type of a literal e.g. `L'a'`
* double quote is a literal type char array and single quote is a literal type char

## References
* References are type, not objects
* bind the reference to initializer and cannot not be re-bindined, so it must be initialized

## Terms
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
* index/subscript, the value you use in an subscript
* vector is template, which generates types such as `vector<int>`
* compound type, type defined in terms of others types such as pointer and reference
* redeclaration, return type and signatures match so redefined
* erroneous redclaration, return types differ
* overloaded, if signature differ
* polymorphism, refers to how some operations behave diffeenty to the same event, most likely virtual function

## Operators:
* operators such as the insertion operator `<<` can be overloaded to accept user defined types

### Operator: new
* `new type; // returns a valid address, memory is not initialized, and calls the class constructor`
* `new type(aValue); // initialize the allocated storage to aValue`
* `new type[N]; // allocate storage for N instance of type`

### Operator: delete
* if allocated with `new[]`, then free with `delete[]`
* `delete expression // non-array type structures` 
* `delete [] expression // free an array, deleting array type structures`

### Operator: insertion or extraction
* `>>` the "get from" or "extraction" operator: read from `s` into `x`, `s >> x`
* `<<` the "instertion" operator: write `x` to `s`, `s << x`    
* `<<` manipulate precision of float w/ `cout.precision(i); cout << "The precision is: " << cout.precision() << "\t" << 9.87654321 << endl;`

## float
* `float f = 45.6f; // the f suffix denotes a literal float constant`

## auto
* the type is deduced by the value it is initialized to `template<typename T> struct TD; TD<decltype(var_auto_decl)> td;`

* if a var is not initialized at declaration, then auto cannot be used

## vectors
* only subscript known elements to exist, a range constructor might help `vector<unsigned> scores(11, 0);`
* `for (std::vector::iterator element = values.begin(); element != values.end(); ++element)`
* `for (auto element = values.begin(); element != values.end(); ++element) `
* `std::stringstream actual; for (auto value : values)`

## arrays
* for dynamically allocated arrays begin/end are not defined as in C size tracking required, stl collection classes are preferred. 
* `auto array = new int[10];` or `auto array = std::make_unique<int[]>(10);`

## string
* Any variable used to store the result of string size should be stored in `std::size_type`---`auto len = line.size()`
* `string s5 = "hiya"; //copy initialization`
* `string s6("hiya"); //direct initialization`

## struct
* struct by default members are public

## class
* class by default members are private

## Namespace
* don't use `using` declarations because they'll be copied into the including programs text

## Function
* TODO definition
* copy-by-value not suitable for large objects

### Function prototype
* used to identify to the compiler
* signature is the parameters to the prototype
* default parameters, in proto `returnType functionName (type0 arg0=value0 . . . typen argn=valuen);` not define

### Function overloading
* within the same scope functions with the same name are differentiated by name and signature
* signature, Type of arguments, Number of arguments, Sequence of arguments &, Qualifiers like const and volatile.

### Lambda function
* unnamed inline function

## Enum
* a type which can be set to one value out of a set, prefer enum class for their scope resolution
* old style, `enum Color` and `enum class Color`
* name refers to the formal definition of establishing the number of something

## Pointers
* a pointer is an object, initialize all pointers, behavior is not defined for all states
* four states of a pointer: point to an object, point to a location past the end of an object, null, and invalid otherwise
* trying to access an object via a pointer when it does not point to one results in undefined behavior
* `int \**p1 = nullptr/NULL/0;` ordered in preference

### Unique pointers
* unique pointers use heap memory and delete memory automatically via destructor, make unique is a way of initializing a unique pointer
* `std::unique_ptr<int> p2; //initializes to a nullptr`
* (cont. ) `std::unique_ptr<int[]> values2 = std::make_unique<int[]>(10);` alternatively
* (cont. ) `auto values2 = std::make_unique<int[]>(10);`

### Shared pointers
* shared pointer, syntax `std::shared_ptr<int[]> sharedValues = std::make_shared<int[]>(20);` allows multiple clients to share access to that dynamically allocated heap memory by using reference counting use unique pointer unless you really need sharing
* void pointers, deal with memory as memory
* read it right to left for complicated point or reference declarations `int *&r`
* `const char* q = hello; // can't modify the data being pointed at, but can change what we point at`
* `char* const r = hello; // can't change what is pointed at, but can change the value at what we point`
* `const char* const s = hello; // cant change what is pointed at and can't change the value at what we point` 
* `int* myPtr = new int; // allocate storage for an int and assign the pointer to the storage to myPtr`
* `new int(33); // to the address (the pointer) of a newly allocated int with the value of 33`
* pointer arithmetic, `int* p; int arr[2] = {0, 1}; p = arr; ++p;`

## Class
* field, data members which determine state

## Compile
* flags: `-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused`
* `g++ -fPIC ./include/*.cpp -shared -Wl,-soname,libUnitLite.so  -o ./lib/libUnitLite.so`
* `reset && g++ ./include/Main.cpp ./assignment-2/SwapTest.cpp ./assignment-2/jstronz-2-1.cpp -L./lib -lUnitLite`

# Week 1:   
### Primer    
* 5.1 to 5.5
* 6.1 to 6.4
* 15.1

### Effective
* item 16
* Item 53

### UML
* Chapter 1, "Introduction"
* Chapter 4, "Class Diagrams: The Essentials"

### Bjarne
* pg 59-89

## Readings Abbrev
* iostream is the standard input and strandard output streams library    
* istream is a type to handle streams of input    
* ostream is a type to handle streams of output     
* cin (Character IN) is the standard input stream object
* cout (Character OUT) is the standard output stream object    
* clog is the std out stream for logging    
* cerr is the std err stream for logging    
* Note the operators `<<` and `>>` point to the flow of the stream and expect a stream object on the LHS.    
* String literal, a sequence of characters enclosed by "".    
* Condition, an expression that yields a result which is t/f
* `int v1 = 0;` define `v1` as int & initialize `0`    
* `++i` is modified then evaluated    
* `i++` is modified after evaluation   
* istream becomes invalid when ctrl-d EOF or invalid input    

## Manipulators    
An operator that changes the behavior of stream is called manipulator
* std::endl put '\n' and flush stream
* std::flush flushes the stream 

## Practice Questions

### Practice 3
* What is the purpose of a function prototype?
* Can I choose which function parameters have default values?
* Can an overloaded function have default parameters? https://stackoverflow.com/questions/1637332/static-const-vs-define
* What is the difference between `#define` and `const`?  `#define` can only be used onces

## MD Cheatsheet
* https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet
