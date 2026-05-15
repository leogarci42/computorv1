# ComputorV1 #

This program solves polynomial equations up to degree 2.

## What is a 2nd-degree polynomial? ##

A polynomial in one variable is a sum of terms with non-negative integer powers of that variable.

A 2nd-degree (quadratic) polynomial has the form:

$$ax^2 + bx + c$$

with $a \neq 0$. If $a = 0$, the degree drops to 1 (linear) or 0 (constant).

Examples of degree-2 polynomials:

- $2x^2 + 3x - 5$
- $x^2 - 12$
- $-4x^2$

Not degree 2:

- $2$ (degree 0)
- $3x + 1$ (degree 1)
- $2 * 1$ (just the constant 2)

## Input rules for this parser ##

The parser in this project accepts a restricted grammar:

- Variables are `X` or `x`.
- Exponents must be non-negative integers: `X^2`, `X^0`, `X^10`.
- `*` is only allowed between a coefficient and the variable: `2 * X` or `2*X^2`.
- A term can be written as `X`, `2X`, `2*X`, `2*X^2`, or a constant like `42`.

So `2 * 1 = 12` is rejected, because `*` must be followed by a variable, not a number.

## Build ##

```
make
```

## Run ##

```
./computorv1 "2 * X^2 + 1 = 12"
```

More valid inputs:

- `./computorv1 "X^2 + 2X + 1 = 0"`
- `./computorv1 "5*X^2 - 4*X + 2 = 0"`
- `./computorv1 "2*X = 12"`
- `./computorv1 "7 = 7"`

## Quick checks ##

There are no automated tests yet. Use the command line to validate parsing and solving behavior:

- Quadratic: `./computorv1 "X^2 - 12 = 0"`
- Linear: `./computorv1 "2*X - 4 = 0"`
- Constant: `./computorv1 "2 = 2"`