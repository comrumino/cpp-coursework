# General
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
* http://www.stroustrup.com/Programming/PPP-style-rev3.pdf

## Commenting    
* Stating intent (i.e. identify the purpose of a variable)
* Strategy or general design (i.e. summarize an algorithm)
* Stating invariants, pre- and post-conditions
* if the comment and code disagree, both are most likely wrong

## Design Philosophy
* procedural paradigm, algorithms are required to solve our problem
* data-driven paradigm, the relationships between data and its abstractions is often more important than algorithms
* functional paradigm, composition of functions without state and mutable data are independent of execution order---so, the functions can be executed in parrallel...
* logical programs, logical expressions or statements to encapsulate the data and functions    
* object-based paradigm, object is used to store data which describes a particular entity; encapsulation is wrapped data and functions; data-hiding, object data should only be manipulated by itself
* object-orientatd paradigm, adds inheritcance to polymorphism to object-based paradigm


## Design Considerations
* a function is where logically separate copmutation starts---best point to think about correct code and catch errors
* is it easy to know when a boundary condition is violated    


## Terms
* clash, two incompatible declarations within the same scope
* pre-conditions, function argument requirements to run properly (doc if always good arguments, not too slow, not too complicated).
* post-conditions, the promis of what is returned
* invariant, a set of constraints which make the state valid (a rule for object value)
* state, the value of an object
* valid state, the idea of a valid value

## Operator: new
* `new type; // returns a valid address, memory is not initialized, and calls the class constructor`
* `new type(aValue); // initialize the allocated storage to aValue`
* `new type[N]; // allocate storage for N instance of type`

## Operator: delete
* if allocated with `new[]`, then free with `delete[]`
* `delete expression // non-array type structures` 
* `delete [] expression // free an array, deleting array type structures`

## float
* `float f = 45.6f; // the f suffix denotes a literal float constant`

## auto
* if a var is not initialized at declaration, then auto cannot be used

## vectors
* a vector is a template
* `for (std::vector::iterator element = values.begin(); element != values.end(); ++element)`
* `for (auto element = values.begin(); element != values.end(); ++element) `
* `std::stringstream actual; for (auto value : values)`

## string
* Any variable used to store the result of string size should be stored in `std::size_type`---`auto len = line.size()`


## Pointers
* `const char* q = hello; // can't modify the data being pointed at, but can change what we point at`
* `char* const r = hello; // can't change what is pointed at, but can change the value at what we point`
* `const char* const s = hello; // cant change what is pointed at and can't change the value at what we point` 
* `int* myPtr = new int; // allocate storage for an int and assign the pointer to the storage to myPtr`
* `new int(33); // to the address (the pointer) of a newly allocated int with the value of 33`

## Compile
* `g++ -fPIC *.cpp -shared -Wl,-soname,libUnitLite.so  -o ./lib/libUnitLite.so`
* `reset && g++ ./include/Main.cpp ./assignment-1/RWDoubleTest.cpp ./assignment-1/jstronz-1-3.cpp -I./assignment-1 -I./include -L./lib/ -lUnitLite && LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH ./a.out`

# Week 1:   
### Primer    
* ~~1.1-1.4 pg 1-19~~
* 2.1-2.2 pg 31-50
* 3.1-3.3 pg 81-102

### Effective
* intro, item 1, item 2 pg 2-17

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
* `>>` the "get from" or "extraction" operator: read from `s` into `x`, `s >> x`
* `<<` the "instertion" operator: write `x` to `s`, `s << x`    
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

## MD Cheatsheet
* https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet
