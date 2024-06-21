# Quadratic equation solver
### From [SeveraTheDuck](https://github.com/SeveraTheDuck)

## Contents
1. [Short description](#short-description)
2. [Install guide](#install-guide)
3. [Usage](#usage)
4. [Examples](#examples)
5. [Documentation link](#documentation-link)

## Short description
The [repository](https://github.com/SeveraTheDuck/SquareSolver) contains simple quadratic equation solver.
It solves all possible variants of roots above the real numbers.

## Install guide
1. Download the [repository](https://github.com/SeveraTheDuck/SquareSolver) from github or use
`git clone https://github.com/SeveraTheDuck/SquareSolver`.
2. Open terminal in the SquareSolver folder.
3. Run `make` command via terminal to compile executable file.
4. Run `./quadratic_equation_solver` command to run the solver.

## Usage
1. You will be asked to enter coefficients of the quadratic equation $ax^2+bx+c=0$. Enter them in the sequence of a, b, c.
2. After that you will be asked whether the equation is correct or not. Enter `y` if yes and `n` if no and go back to paragraph 1.
3. You will receive output with information about number of roots and their values.

## Examples
```
Please, enter coefficients:
a_coef:
1
b_coef:
3
c_coef:
2
Is it your equation? [Y]es [N]o
1.000000x^2 + 3.000000x + 2.000000 = 0
y
Number of roots: 2
First root: -2.000000
Second root: -1.000000
```

```
Please, enter coefficients:
a_coef:
1
b_coef:
3
c_coef:
2
Is it your equation? [Y]es [N]o
1.000000x^2 + 3.000000x + 2.000000
n
Please, try again
Please, enter coefficients:
a_coef:
0
b_coef:
1
c_coef:
2
Is it your equation? [Y]es [N]o
0.000000x^2 + 1.000000x + 2.000000
y
Number of roots: 1
The only root: -2.000000
```

## Documentation link
