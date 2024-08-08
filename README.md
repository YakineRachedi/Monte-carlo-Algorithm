### Introduction : 
Monte Carlo methods encompass a set of techniques and algorithms used to approximate the numerical value of certain integrals by simulating a large number of independent and identically distributed random variables.

Let $(\Omega, \mathcal{F}, P)$ be a probability space, $E$ and $F$ be measurable spaces, and $X : \Omega \to E$ be a random variable such that $E(|X|) < \infty$. Let $f : E \to F$ be a measurable function. Suppose that $X_1, \ldots, X_n$ are $n$ i.i.d. random variables with the same distribution as $X$. The $k$-th empirical moment of $f(X)$ is defined as:

$$
m_{k,n}^b = \frac{1}{n} \sum_{i=1}^{n} f(X_i)^k.
$$

If $f(X)^k$ is integrable, the strong law of large numbers states that

$$
\hat{m}_{k,n} \xrightarrow{p.s., L^1} E(f(X)^k)
$$

as $n \to \infty$.