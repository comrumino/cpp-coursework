# Project Proposal:
 + demonstrate as many of the principles of object-oriented design as possible in your project
 + Your grade will be based on style, the thoroughness of your design, the correctness of your implementation, and the completeness of your testing.


Project Proposal:
    Preventing license theft and improving transparency licensing model for client is fundamental to any business. Implementing a licensing model
which interacts with the C-API has a larger scope than is possible to finish within three weeks. So, the aim for this project is implement the core
features necessary for minimal functionality while still being extensible. Given the risk of scope creeping, it is important to be precise.

Initial requirements:
 + Basic integrity control, if not rudimentary, define a methodology to be used in the creation of a network which mitigates risks and ensures mutual integrity
 + License verification, define a class to verify a given input is a valid license which also interacts with integrity controls
 + License generation, define a function which takes transient data and returns a verifiable license
Reach requirement:
 + Create a C interface for licensing and integrity controls for python and go


# Specification Document for Your Course Project
The specification and design documents should follow the outline described in this assignment. Some of the sections in the outline may not be applicable to your project. If this is the case, simply make a statement to that effect.

## System Description
- [X] Give an overview and functional description of the system. Provide enough detail so that the reader understands what the project is and what it is to accomplish.
- [X] Include a description of the user interface.
- [X ] Write the description from a user's point of view—describe what you're going to design.
## Test Requirements
- [ ] Write a system test plan—when testing the completed system, what needs to be tested?
- [ ] Do validation or acceptance testing to make sure that you meet the user's requirements.
- [ ] You will not have time to field-test your project. If you were to do so, however, how would you accomplish this testing?
- [ ] Do verification—internal tests, like module tests—of the components of your project; this is not a test of the complete system. For example, test the boundary conditions in your class member functions.
## Initial Design Strategy
- [ ] Include your initial thoughts on how you will implement your project.

# Design Document
This document should be written from a designer's point of view. It should describe how you're going to implement the design and should give a road map of how the components of your design fit together.
- [ ] Give an overview of the class hierarchies. Remember the first class when we talked about design methodologies. I recommend using CRC cards for object discovery.
- [ ] Discuss why a particular design was chosen.
- [ ] Include class diagrams and other documentation to describe your design.
- [ ] Include public interface for each class.

# Specification
Preventing license theft and having a transparent licensing model that clients find reasonable and easy to understand is fundamental to any business. 
Clients have a background in compliance and security auditing for industrial control systems and critical infrastructure. Given that the primary use
case is compliance with NERC-CIP cyber security standards, the license is on a per device basis. The term device used generically for cyber assets
which enforce or monitor access controls (e.g. firewalls and routers).    
    
The goal is to support licensing for a fixed number of devices and making the licensing less trivial to bipass. This project will not have a direct user interface. So,
this project should be a magic black box which helps keep users honest.

## Test Requirements
The testing must be sufficient to ensure present and future functionality. Test cases:
### system true positive result:
Givens:
- license is valid format
- license is not expired
- number of unique devices across all projects is less than or equal to the license limit
Expected behavior:
- free to alternate between projects
- all features are available
### system true negative result:
Givens:
- license is valid format
- license is either is expired or the number of unique devices is greater than specified in license
Expected behavior:
- free to alternate between projects
- response provided results in disabled features
### integration and unit test requirements
- validate format, expect true positive result
- validate format, expect true negative result
- store valid license attributes
- ctor test of integrity controls and license classes 
