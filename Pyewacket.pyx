#!python3
#distutils: language = c++
import itertools as _itertools


__all__ = (
    "seed",
    "random", "uniform",
    "randbelow", "randint", "randrange",
    "gauss", "normalvariate", "lognormvariate",
    "expovariate", "vonmisesvariate", "gammavariate", "triangular",
    "betavariate", "paretovariate", "weibullvariate",
    "shuffle", "choice", "sample", "choices",
)


cdef extern from "Pyewacket.hpp":
    void       _seed         "Storm::Engine::cyclone.seed"(unsigned long long)
    double     _random       "Storm::canonical_variate"()
    long long  _randbelow    "Storm::random_below"(long long)
    long long  _randint      "Storm::uniform_int_variate"(long long, long long)
    long long  _randrange    "Storm::random_range"(long long, long long, long long)
    double     _uniform      "Storm::uniform_real_variate"(double, double)
    double     _exponential  "Storm::exponential_variate"(double)
    double     _gamma        "Storm::gamma_variate"(double, double)
    double     _weibull      "Storm::weibull_variate"(double, double)
    double     _normal       "Storm::normal_variate"(double, double)
    double     _lognormal    "Storm::lognormal_variate"(double, double)
    double     _beta         "Storm::beta_variate"(double, double)
    double     _pareto       "Storm::pareto_variate"(double)
    double     _vonmises     "Storm::vonmises_variate"(double, double)
    double     _triangular   "Storm::triangular_variate"(double, double, double)


# SEEDING #
def seed(seed=0) -> None:
    _seed(seed)


# RANDOM VALUE #
def choice(seq):
    if len(seq) == 0:
        return None
    return seq[_randbelow(len(seq))]

def shuffle(array):
    for i in reversed(range(len(array) - 1)):
        j = _randrange(i, len(array), 1)
        array[i], array[j] = array[j], array[i]

def choices(population, weights=None, *, cum_weights=None, k=1):
    def cwc(pop, weights):
        max_weight = weights[-1]
        rand = _randbelow(max_weight)
        for weight, value in zip(weights, pop):
            if weight > rand:
                return value

    if not weights and not cum_weights:
        return [choice(population) for _ in range(k)]
    if not cum_weights:
        cum_weights = list(_itertools.accumulate(weights))
    assert len(cum_weights) == len(population), "The number of weights does not match the population"
    return [cwc(population, cum_weights) for _ in range(k)]

def sample(population, k):
    n = len(population)
    assert 0 < k <= n, "Sample size k is larger than population or is negative"
    if k == 1:
        return [choice(population)]
    elif k == n or k >= n // 2:
        result = list(population)
        shuffle(result)
        return result[:k]
    else:
        result = [None] * k
        selected = set()
        selected_add = selected.add
        for i in range(k):
            j = _randbelow(n)
            while j in selected:
                j = _randbelow(n)
            selected_add(j)
            result[i] = population[j]
        return result


# RANDOM INTEGER #
def randbelow(a) -> int:
    return _randbelow(a)

def randint(a, b) -> int:
    return _randint(a, b)

def randrange(start, stop=0, step=1) -> int:
    return _randrange(start, stop, step)


# RANDOM FLOATING POINT #
def random() -> float:
    return _random()

def uniform(a, b) -> float:
    return _uniform(a, b)

def expovariate(lambd) -> float:
    return _exponential(lambd)

def gammavariate(alpha, beta) -> float:
    return _gamma(alpha, beta)

def weibullvariate(alpha, beta) -> float:
    return _weibull(alpha, beta)

def betavariate(alpha, beta) -> float:
    return _beta(alpha, beta)

def paretovariate(alpha) -> float:
    return _pareto(alpha)

def gauss(mu, sigma) -> float:
    return _normal(mu, sigma)

def normalvariate(mu, sigma) -> float:
    return _normal(mu, sigma)

def lognormvariate(mu, sigma) -> float:
    return _lognormal(mu, sigma)

def vonmisesvariate(mu, kappa) -> float:
    return _vonmises(mu, kappa)

def triangular(low=0.0, high=1.0, mode=0.5) -> float:
    return _triangular(low, high, mode)
