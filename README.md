[中文介绍](Doc/Introduction/中文/README.md)

# Wishing

Wishing is a framework for developing content editors

# Features

- Developed using C++ and CMake
- Utilizes [Niflect](https://github.com/sainimu78/Niflect) for C++ Native-Style Reflection
- Reference-Based Content File Management
- Content Editing and Validation Pipeline
- Content Cooking Pipeline from Editor to Runtime
- Modern Animation-Driven Widgets
- Fast Iterative Development Experience with Modular C++ Scripting
- Packaging Pipeline for Desktop Products on Windows and Ubuntu

# Expected Application Cases

- Game Development Workflow
- Presentations (PPT) based on Next-Gen Resource Management Solutions
- Video or Image Post-Processing Applications

# R&D Goals

Content-editing products often share some common systems and functionalities, which can be challenging to implement, such as:

- Interrelated content file references
- Cooking pipeline for edited content
  - "Cooking" refers to the process of converting content files into a simpler and more compact data format.
  - This is used to improve the loading and serialization efficiency of runtime applications.
- Modification and validation update processes after editing contents or instance properties
- Collaborative content editing for multiple users

As a result, Wishing aims to standardize the development process for content-editing products.

