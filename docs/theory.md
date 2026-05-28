# Computorv1

## What is a polynomial?

A *polynomial expression* in algebra is made of:

- variable (x)
- coefficients (like 3 in 3x)
- exponents (like ^2 in 3x^2)

so all of those are *polynomial expression*:

- 2X + 3
- X^2 - 5X + 1

Each part of a polynomial is called a **term**.

### What is a *Polynomial degree*:

It's the highest exponent of the variable in the given polynomial.

For example:

- 3X^2 + 2X + 1

So here the power is 2 (3X^**2**), 1 (2X == 2X^**1**) and 0 (1 == 1X^**0**), so the largest here is 2.

## How to solve a *Polynomial degree equation*

The first step is to find the degree, but in or context of **Computorv1** we start by parsing the input, and reduce the equation, and only then identify the degree.

Once we identify the highest degree, we then can choose our solving methods, out of two since we need to handle only a polynomial second or lower degree equation.

**Degree 0**

it's a regular calculator 

for example:
```
3X^0 + 1 = 4 == 3 + 1 = 4
```

**Degree 1**

A first degree equation (or linear equation) with one unknown is always of the form
```
aX + b = 0
```

Then we want to isolate the X so it becomes:
```
aX / a = (-b) / a
X = (-b) / a
```

**Degree 2**

We simplify it to aX^2 + bX + C = 0 we can obtain this equation (a != 0): 

```
(X + b / 2a)^2 = Δ / 4a^2 
```

And here we can simply identify multiple cases:

- Δ < 0 no solution (bc a scare is always strictly positive)
- Δ == 0 got only one answer
```
X = -b / 2a 
```

- Δ > 0 Here we got two choices :
```
X + b / 2a = √(Δ / 4a^2) = √Δ / 2a so X = (-b + √Δ) / 2a 
```
or 
```
X + b / 2a = -√(Δ / 4a^2) = -√Δ / 2a so X = (-b - √Δ) / 2a
```

And that's all for this subject!
