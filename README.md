### _Introduction :_ 
Monte Carlo methods encompass a set of techniques and algorithms used to approximate the numerical value of certain integrals by simulating a large number of independent and identically distributed random variables.

### _Principle of the algorithm :_

Let $(\Omega, \mathcal{F}, P)$ be a probability space, $E$ and $F$ be measurable spaces, and $X : \Omega \to E$ be a random variable such that $E(|X|) < \infty$. Let $f : E \to F$ be a measurable function. Suppose that $X_1, \ldots, X_n$ are $n$ i.i.d. random variables with the same distribution as $X$. The $k$-th empirical moment of $f(X)$ is defined as:

$$
m_{k,n}^b = \frac{1}{n} \sum_{i=1}^{n} f(X_i)^k.
$$

If $f(X)^k$ is integrable, the strong law of large numbers states that

$$
\hat{m}_{k,n} \xrightarrow{p.s., L^1} E(f(X)^k)
$$

as $n \to \infty$.


- - - - - -- - - - --- --  - - -
### _Explanation of the classes in the Monte Carlo function template :_

- Statistique Class: Represents the estimator we want to calculate using simulation, such as the empirical mean.

- RandomVariable Class: Represents the distribution of the random variables being simulated, for example, std::uniform_real_distribution<double>.

- Measurement Class: Represents the set of possible functions $f$.

- RNG Class: Specifies the type of generator used, and throughout the project, we will restrict ourselves to the std::mt19937 type.


`MonteCarlo(res, X, f, G, n)` stores in `res` the result of the calculation

$$
\frac{1}{n} \sum_{k=1}^{n} f(X_k)
$$

where $f : E \to F$ is a measurable function whose argument type corresponds to the output type of the $X_k$, which are i.i.d. random variables with a distribution determined by the `RandomVariable` class and are simulated using the random generator `G`.
- - - -- - - - - - - - 

# Approximation de $\pi$ :

### First Monte Carlo Algorithm: Estimating π

We implement a class `SquareInDisk` to estimate the value of $\pi$. 

Firstly, we randomly generate points $(x, y) \in [0, 1]^2$ (according to the uniform distribution) and count the proportion of these points that fall within the unit disk $\{(x, y) : x^2 + y^2 \leq 1\}$. This proportion converges to the ratio of the areas, which is $\frac{\pi}{4}$, as the number of points tends to infinity.

To model this experiment, we introduce the class of Bernoulli random variables, which describe whether a uniform point from the unit square falls within the quarter of the unit circle.
