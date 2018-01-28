# Math_Library
A simple graphics-focused math library written in C++.

## Overview
This project is a small vector and matrix math library that I used as a basis for other projects, like the ray tracer. It includes two main files; a template Vector class and a template Matrix class. Along with typical linear algebra functions, it has methods useful for graphics programming, which is why the templates are constrained to vectors and matrices in 2, 3 and 4 dimensions. 
The project files also include the Unit tests I created. It was imperative that I test every method in each class with test files cases, that way I could trust it as the foundation for other projects.

## Vector
The Vector template contains methods to add, subtract, scale, normalize, and find the magnitude of vectors in 2, 3 and 4 dimensions. You can also take the dot product, cross product (only meaningful for 3 dimensional vectors), and homogenize vectors. The underlying data structure for the class is and std::vector containing floats, and my Vector class implements all relevant iterator methods to allow you to loop over it normally.
Both the Vector and Matrix classes have copy constructors that perform deep copies of the object, as well as to_string() methods that display the contained data in a meaningful way.

## Matrix
The Matrix template also contains methods to add, subtract, and scale matrices of the same size. You also have the ability to multiply them to vectors and other matrices; as well as find the determinant, inverse, and transpose of the matrix. The underlying data structure is a std::vector containing this library's Vector type. 
I chose to store the matrices in column-major order. So single bracket notation, my_matrix[i], will allow you to access any column in the matrix (of type Vector) and double bracket notation,my_matrix[i][j], will allow you to access any individual value.

##Graphics Methods
I've added some specialized methods for graphics applications. There are special constructor methods for Translation, Scale, and Rotation matrices. Additionally, the inverse methods for these matrices take advantage of their specialized structure to optimize the inversion process. There are also orthographic and perspective projection matrices used for camera transformations. The perspective projection matrix takes in a field of view value, an origin point, a look direction, and an up direction for the camera. I used this in my ray tracer project to transform the camera rays from screen space into the world space of the scene.
