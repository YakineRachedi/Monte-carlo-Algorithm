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

# $\pi$ approximation :

### First Monte Carlo Algorithm: Estimating π

We implement a class `SquareInDisk` to estimate the value of $\pi$. 

Firstly, we randomly generate points $(x, y) \in [0, 1]^2$ (according to the uniform distribution) and count the proportion of these points that fall within the unit disk $\{(x, y) : x^2 + y^2 \leq 1\}$. This proportion converges to the ratio of the areas, which is $\frac{\pi}{4}$, as the number of points tends to infinity.

To model this experiment, we introduce the class of Bernoulli random variables, which describe whether a uniform point from the unit square falls within the quarter of the unit circle.

# Simultaneous Calculation of Variance and Empirical Mean :
It is possible to calculate the empirical mean and the empirical variance simultaneously.

Recall that the empirical variance
$Var_d(Z)$ of a random variable is defined by

$E_d(Z) = \frac{1}{n} \sum_{k=1}^n Z_k$

$Var_d(Z) = \frac{1}{n} \sum_{k=1}^n (Z_k - E_d(Z))^2$

which can be expressed as

$Var_d(Z) = \frac{1}{n} \sum_{k=1}^n Z_k^2 - (E_d(Z))^2 = E_d(Z^2) - (E_d(Z))^2$

When estimating the precision of an empirical mean approximation, we can determine its confidence interval. 

When the population follows a normal distribution (which is the case when the population size is sufficiently large and its individuals are independent, according to the central limit theorem), we have the following asymptotic bounds:

$$
E_d(X) - k \frac{\sqrt{Var_d(X)}}{\sqrt{n}} \leq E[X] \leq E_d(X) + k \frac{\sqrt{Var_d(X)}}{\sqrt{n}},
$$

where $k$ is the quantile that determines the confidence level. For example, for a 95% confidence level, $k = 1.96$.

# Estimation of integrals :
Estimation using the Monte Carlo function template of the integrals given by :

$$\int_{0}^{1} \ln(1 + x^2) \, dx$$

$$\int_{\mathbb{R}^+ \times [0,1]} \ln(1 + xy) \, e^{-x} \, dx \, dy$$

For the second integral, note that

$$\int_{\mathbb{R}^+ \times [0,1]} f(x, y) \, e^{-x} \, dx \, dy = \mathbb{E}[f(X, Y)]$$

where $X$ follows an exponential distribution with parameter 1 and $Y$ follows a uniform distribution on $[0, 1]$.
