# Math_Library
A simple graphics-focused math library written in C++.

## Overview
This library contains a Vector class for vectors in 2, 3, and 4 dimensions as well as a Matrix class for square matrices, 
also in 2, 3, and 4 dimensions. Each includes methods useful for affine transformations in graphics rendering.
Unit tests have been created for all methods to verify correctness.

## Vector
Vector.h is a templated vector class, supporting vectors in 2, 3, and 4 dimensions. It also includes several methods for
dividing a position vector by the homogenous coordinate in order to properly convert into a lower dimensional vector.
Typical vector methods are present, including dot product, cross product (for 3 dimensional vectors), magnitude, normal,
as well as all basic arithmetic operations between vectors and vectors and scalars.
The underlying representation of the class uses the standard library vector class.

## Matrix
Matrix.h is a templated matrix class, supporting matrices in 2, 3, and 4 dimensions. Matrices are stored in column major order.

In addition to typical matrix operations, I've include serveral specialized static methods for contstructing and inverting 
affine transformation matrices. There are methods to construct a Scale, Rotation, and Translation matrix more efficiently,
as well both an Orthographic and Perspective Projection matrix. There are also static methods to invert a Scale, Rotation,
and Translation matrix, since these inversions can be optimized based on the structure of those matrices. However, those
methods don't verify that they are inverting a correctly formed matrix of each type, so it's up to the user to call them
appropriately. 

This library is designed to be used in other graphics project. For example, I used it to create the Ray Tracer project.
