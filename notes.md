# Why?
* F. Brooks in No Silver Bullet, states four steps to grow. The third step is episodes of advanced formal education with top designers
* learning to solve problems using the C++ language and the object paradigm

# Implementation
* simplicity (minimize the accidental complexity, the complexity brought in when solving the problem)
    * built-ins, class member functions, standard library, 3rd party library, and roll your own
    * compile-time verification eliminates the need for run-time check... this isn't Python
* cohesion and coherence
    * separation of concerns, (separate context specific logic from common member functions)
    * self-documenting and predictable behavior
* ease of extension/contraction
    * greater flexibility is smaller increments of capability; flexibility is ease of change 
    * generality is availability of smaller subsets, generality is usability without change
    * virtual machine approach, to avoid a chain of data transforming components design extensions that are useful in designing many such programs
    * "uses" hierarchy, restrict the "uses" relation so that its graph is loop free
    * "uses" criteria, A is simpler because it uses B and B is not substantially more complex because it is not allowed to use A
* adherence to standards (UML/C++)
* test driven development

## Implementation: Specific principles and concepts
* Duck typing, a type system which relies on the duck test: suitability for a purpose is determined by methods and properties
* LSP, Liskov Substitution Principle, if S is subtype of T then S may replace T
* first-class concept, an idea the is represented in a system in a well-defined manner (e.g. as a class)
* second-class concept, an idea that pervades the system but is not consistently used or defined.
* Class-responsibility-collaboration cards (CRC cards),
    1. class name
    2. super-sub classes
    3. responsibilities class
    4. names of other classes that it will interact with
    5. author name
* SOLID: Single responsibility, open/closed principle, LSP, Interface segregation, dependency inversion
    * open/close principle: easy to add a new concrete component 

## Implementation: Miscellaneous
* move assignment operator should use default implementation for class assignments. See [considerations](http://scottmeyers.blogspot.com/2014/06/the-drawbacks-of-implementing-move.html) of using std::swap in move assignment operator 
* performing a copy inside of a function declared with move sematics will cause your coworkers to change careers (e.g. `operator=(T&&)`)
* `noexcept`, use on move construct, move assign, and swap
* check for safer alternatives to `operator[]` (e.g. `vector::at`)
* sometimes you may not want to inherit from things that don't define a virtual destructor
* classes that have single parameter ctor should use explicit
* default ctor may limit, or even render useless, a class missing setters
* final can be applied to the entire class
* copy references that are dependent on object scope
* given two public class methods, they should be independently callable
* within `operator==`, since it is a class member, consider using the inline-method's definition so performance is not reliant on in-line
* deprecated features ought be avoided
* interfaces should have their own `.h` file

## Testing
* Write tests first, otherwise implemented solution might not allow for automated testing    
* Mainline data, usage scenarios, boundary conditions, and stress conditions
* if a function takes a pointer test for nullptr, NULL, or 0 is passed
* Infrequently followed flows of logic
* all methods should be tested
* avoid circular tests and favor explicit testing
* if more than one test prove the same thing, the duplication probably detracts from overall code quality

## Commenting    
* a null/pass statement should be commented `;`
* Stating intent (i.e. variable purpose)
* Strategy or general design (i.e. algorithm outline)
* Stating invariants, pre- and post-conditions
* if the comment and code disagree, both are most likely wrong

## Design Philosophy
* [rule of five](https://en.cppreference.com/w/cpp/language/rule_of_three)
* encapsulation, coupling, cohesion, shared data, and synchronization (starting, waiting, and in-background)
* concurrent data structures should consider contention, false-sharing, and data proximity
* easy to use right, hard to use wrong
* procedural paradigm, algorithms are required to solve our problem (provide a function values to provide answer)
* data-driven paradigm, the relationships between data and its abstractions is often more important than algorithms
* functional paradigm, composition of functions without state and mutable data are independent of execution order---so, the functions can be executed in parallel...
* logical programs, logical expressions or statements to encapsulate the data and functions    
* object-based paradigm, organization is based on interactions of objects so that ultimately a solution can be found
* object-orientated paradigm, adds inheritance to polymorphism to object-based paradigm
* a function is where logically separate computation starts---best point to think about correct code and catch errors
* is it easy to know when a boundary condition is violated    
* test design, consider scalability of multi-threaded applications and explore possibility of contention


## Patterns
* [generalized hoisting](http://www.stroustrup.com/SCARY.pdf)
* template hoisting, type independent moved into base (e.g. IsEmpty(), GetNumElements(), etc)

# UML: Identity, behavior, state (IBS)
* unified modeling language
* object identify, how the object is distinguished from all other objects
* object behavior, responses to events or messages from other objects (C++ even is a function call)
* object state, the current value of all attributes
* OO programming, organization is based on interactions of objects so that ultimately a solution can be found
* OO requirements, method of analysis that captures the behavioral expectations of a system
* OO design, a way to decompose a system or physical process into logical models and physical models
* OO analysis, to take a problem domain and identify entities/objects and classes. Nouns, verbs, adjectives -> identity/object, behavior/action, state/properties.
* Class-responsibility-collaboration cards (CRC cards),
    1. class name
    2. super-sub classes
    3. responsibilities class
    4. names of other classes that it will interact with
    5. author name

## Object Model Framework
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

## Concurrency Basics
* task switch, doing a bit of one task followed by doing a bit of another task
* context switch, the system operations that are performed to switch from one task to another
    * save CPU state and instruction pointer
    * determine the next task
    * reload CPU state
    * sometimes the instructions load from memory into cache and prevent CPU from executing instructions meanwhile
* concurrency, a system performing multiple activities in parallel
* concurrency illusion, single-core interleaves tasks and multiple activities are quick enough to feel like parallelism
* hardware concurrency, multi-core or multi-processor systems can complete multiple activities in parallel
* hardware threads, the number of independent tasks a processor can genuinely run concurrently
* task parallelism, takes the parts of a task and does them concurrently (a task is divided in terms of processing)
* data parallelism, takes the parts of data and process them concurrently (a task is divided in terms of data)
* conveniently concurrent, a task which is easily made parallel in terms of processing or data
* cost benefit, added complexity (likeli-hood of bugs), performance gain, overhead of thread spawning, and separation of concerns
* client/server application, thread for each connection will at some point reduce overall performance due to task switching
* abstraction penalty, the cost of using high-level facilities in terms of performance (but increased coherence and decreased errors)
* data race, concurrent modification of the same object resulting in undefined behavior
* lock-free programming, (difficult to get right) design the data structure and its invariants so that modifications are done as a series of indivisible changes which preserves the invariants
* transaction, series of reads and writes followed by a commit all done in a single step. if can't proceed, then restarted
* uniform initialization syntax, one use is to avoid "C++'s most vexing parse" (like accidental prototype of thread)
* mutex, (mutual exclusion) synchronization primitive used to lock the associated data while being accessed and unlocked when done
    * protect the right data---deadlocks, too much, or too little
* over-subscription, when the number of threads running decreases performance due to task switching overhead
* cache ping-pong, passing data back and forth between caches many times
* mutex cache ping-pong, allows the system to schedule another ready-to-run thread while waiting for the mutex
* atomic operation cache ping-pong, at the processor level causes a stall which does not allow anything else to run
* high contention, processor one is waiting to update a value and processor two is currently updating; processor one has to wait for two to finish and for the change to propagate
* cache-lines, blocks of memory which store 32/64 bytes of data
* false sharing, the cache-line is shared between threads and the data is not which results in cache ping-pong 
* scalability, the application can take advantage of additional processors (see Amdahl's law)
* lock-free queue, this could still be a time-sink so consider separate work queue per thread (post work to local queue, check local queue for work, and check global queue for work if local is empty)
* work stealing, a design which allows a thread with no work to steal work from a thread with a full queue
* thread-safe, no data loss or corruption, all invariants are upheld, and no race conditions
* serialization, preventing genuine concurrent access and requires threads to access it serially
* atomic action, indivisible sequence of primitive operations that must be complete without interruption

## Terms
* abstract, refer to the [documentation](https://en.cppreference.com/w/cpp/types/is_abstract) for `std::is_abstract` 
* [abstract class](https://en.cppreference.com/w/cpp/language/abstract_class)
    * overly restrictive description: all trivial classes are concrete, but not all concrete classes are trivial
* concrete, something that is not abstract
* RAII, exception safety for stack resources and locality of acquisition/release logic
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
* invariant, a rules/statement which is always true
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
* CODEC, comes from "code/decode" (similar to MODEM which comes from "Modulator/Demodulator")

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
* [Skip Lists: A Probabilistic Alternative to Balanced Trees](https://cglab.ca/~morin/teaching/5408/refs/p90a.pdf)

## CTRL+F Notes
* float, `float f = 45.6f; // the f suffix denotes a literal float constant`
* auto, the type is deduced by the value it is initialized to `template<typename T> struct TD; TD<decltype(var_auto_decl)> td;`
* auto, if a var is not initialized at declaration, then auto cannot be used
* array, dynamically allocated arrays don't define begin/end, C size check required---stl collection classes are preferred. 
* array, `auto array = new int[10];` or `auto array = std::make_unique<int[]>(10);`
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
* Derived object has a sub-object for itself and each base class which allows a reference/pointer to be bound to the base
* overloaded operator, redefine the built-in operation---member of class or operand of type class
* conversion operator, performs class-type/user-defined conversions (judicious, clear, avoid mutual conversions, multiple arith type convs)
* explicit conversion, implicit conversion restricted to expressions used as a condition
* function-objects, callable objects (class w/ operator def)---lambdas are function objects
* function-table, data structure allowing search of function-objects with the same call signature---function templates
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
* explicit instantiation, `extern` declares the arguments for all parameters and nonextern instantiation---extern is promise of instantiation elsewhere to avoid overheard
* function parameter pack, one or more arguments
* instantiate, the replacement of template arguments with corresponding args based on a call.
* member template, member function that is a template (applies ordinary non template classes as well)
* template nontype parameters, integral parameters are consts, refs/ptrs have lifetimes
* template specialization, all parameters of template function are specified. class template and member templates allow partial specialization via partial evaluation of the base template
* template type parameter, named used to abstract a type (that is the parameters to the template)
* trailing return types, `auto fcn(It beg, It end) -> typename remove_reference<decltype(*beg)>::type` if the function template return type is a related type of a template type parameter, instantiation of all possibilities is burdensome
* type transformation template, metaprogramming, transform a given template type parameter to a related type
* variadic template, varying number of template arguments---use template parameter pack
* bitmap, are unstructured (a list of colored dots such as BMP, JPG, GIF, and TIFF)
* vector, are structured (geometric definitions)
* unstructured, flat, raw generally refer to bitmaps
* structured, generally refers to vectors
* unstructured surface, a dot matrix used in printers and monitors
* primary point, defines the point a curve passes through
* relative point handles, the two points that are relative to the primary point in a curve
* curve, set of relative point handles and a primary point
* shape, an ordered set of points
* closed, the term used to describe if there is a line between the first point and last point in the ordered set of points
* Archetypal rectangle, a rectangle for which all lines a rotated either 0 or 90 degrees
* lvalue, something that can appear on the LHS of an assignment
* rvalue, cannot appear on the LHS of an assignment
* rvalue reference, is a reference to something nobody else can assign to, safe to steal its value
* universal reference, `T&&` can be treated as an lvalue reference or an rvalue reference (a.k.a. forward reference)
* parameters, the variables referenced in the function
* argument, the expressions evaluated at the location where the function is called
* move semantics, compiler moves the objects (non const arguments, leave in state that is destructor safe)
    * move operations defined by compiler iff no copy operations defined, no move operations defined, no destructor defined in the class
* `std::move`, a cast to an rvalue, doesn't actually move anything, the object can become empty in the previous context
* `std::forward`, produces an rvalue from an universal-reference/rvalue only (Myeres' rule #25)
* persistence, data continues to exists after a process exits
* transparent persistence, complexities of periodic saving are hidden from object use
* serialization, the process of transforming an object into sequentially stored/transferred bits
* file format, a defined convention for encoding a file
* POD, plain old data, contiguous sequence of bytes in memory
* scene, collection of objects and their orientation to each other
* layer, collection of graphics, no width and height
* locking, disable modification
* z-layer, dictates the order in which graphics are drawn
* synergy, worth more in its whole than the parts
* smart_pointers, reference count to same object
* unique_ptr, retains exclusive ownership
* weak_ptr, does not affect shared_ptr count
* fundamental collections, generic collections that are the foundation to collections designed for a precise use, (i.e. list, deque, vector)
* weakest link, the part of a design which should be optimized when worth it and necessary
* list, element access is linear
* deque, efficient start/end insertion/removal, random access, start/end operations don't invalidate iterators otherwise iterators are invalidated
* Horizontal alignment, placement relative to the archetypal rectangle
* assignment of self is no operator `if (this != &rhs) { value = rhs.value; } return *this`
* be aware of which operators invalidate the iterator
* first-class concept, an idea the is represented in a system in a well-defined manner (e.g. as a class)
* second-class concept, an idea that pervades the system but is not consistently used or defined.
* extend functionality two options: decorators or subclasses (decorators for dynamic, transparent, and when subclasses are impractical)
* iterator/cursor, sequential access for an aggregate object
* prototype, dynamic loading that avoids a class hierarchy of factories when there a finite number of state combinations
* end iterators, a result of a pointer based mental model and overly biased to primitive type behavior
* unsigned int, rarely necessary to save one more bit for storage and trying to ensure something is positive futile due to implicit rule conversions
* std::iterator. it does not define a virtual destructor
* nonbool -> if value == 0 then false, so nonzero is true
* undefined operation such as assign an out-of-range value to an object of signed type the result is undefined
* don't mixed signed and unsigned types
* `20 /* decimal */ 024 /* octal */ 0x14 /* hexidecimal */
* string literal is array of chars followed by a null character
* escape single quotes, double quotes, question mark, backslash
* specify the type of a literal e.g. `L'a'`
* double quote is a literal type char array and single quote is a literal type char
