# Pyewacket
### Fast, fault-tolerant, drop-in replacement for the Python3 random module

Built on top of the RNG Storm Engine for stability and performance. Storm is a high quality random engine, but totally not appropriate for cryptography of any kind. Pyewacket is meant for games, data science, A.I. and experimental programming, not security.


### Quick Install `$ pip install Pyewacket`


### Installation may require the following:
- Python 3.6 or later with dev tools (setuptools, pip, etc.)
- Cython: Bridge from C/C++ to Python.
- Modern C++17 Compiler and Standard Library.


### Sister Projects:
- Fortuna: Collection of tools to make custom random value generators. https://pypi.org/project/Fortuna/
- Pyewacket: Drop-in replacement for the Python3 random module. https://pypi.org/project/Pyewacket/
- MonkeyScope: Framework for testing non-deterministic generators. https://pypi.org/project/MonkeyScope/


# Random Generators

## Random Integers
- `Pyewacket.randbelow(n: int) -> int`
    - @param n :: Pyewacket expands the acceptable input domain to include non-positive values of n.
    - @return :: random integer in range (n, 0] or [0, n) depending on the sign of n.

```python
from Pyewacket import randbelow


randbelow(10)   # -> [0, 10)
randbelow(0)    # -> [0, 0) => 0
randbelow(-10)  # -> (-10, 0]
```

- `Pyewacket.randint(a: int, b: int) -> int`
    - @param a, b :: inputs to form the output distribution range
    - @return :: random integer in range [a, b] or [b, a]
    - Inclusive on both sides
    - Removed the asymmetric requirement of a < b
    - When a == b this always returns a

```python
from Pyewacket import randint


randint(1, 10)   # -> [1, 10]
randint(10, 1)   # -> [1, 10]
randint(10, 10)  # -> [10, 10] => 10
```

- `Pyewacket.randrange(start: int, stop: int = 0, step: int = 1) -> int`
    - @param start :: This is the starting point for the distribution range so long as start <= stop and step >= 0
    - @param stop :: optional, default=0, stating point iff stop < start.
    - @param step :: optional, default=1, negative stepping will flip start and stop.
        - The sign of the step controls the phase of the output, said another way: negative ranges count backwards.
    - @return :: random integer in range (stop, start] or [start, stop), by increments of |step|
    - Removed the requirements of start < stop, and step > 0
    - Always returns start iff start == stop or step == 0

```python
from Pyewacket import randrange


randrange(10)           # -> [0, 10) by whole numbers
randrange(1, 10)        # -> [1, 10) by whole numbers
randrange(1, 10, 2)     # -> [1, 10) by 2, odd numbers
randrange(-10)          # -> [-10, 0) by 1
randrange(10, 1)        # -> [1, 10) by 1
randrange(10, 0, 2)     # -> [0, 10) by 2, even numbers
randrange(10, 10, 0)    # -> [10, 10) => 10
```

## Random Floating Point
- `Pyewacket.random() -> float`
    - random float in range [0.0, 1.0] or [0.0, 1.0) depending on rounding, platform specific.
- `Pyewacket.uniform(a: float, b: float) -> float`
    - random float in [a, b] or [a, b) depending on rounding
- `Pyewacket.expovariate(lambd: float) -> float`
- `Pyewacket.gammavariate(alpha, beta) -> float`
- `Pyewacket.weibullvariate(alpha, beta) -> float`
- `Pyewacket.betavariate(alpha, beta) -> float`
- `Pyewacket.paretovariate(alpha) -> float`
- `Pyewacket.gauss(mu: float, sigma: float) -> float`
- `Pyewacket.normalvariate(mu: float, sigma: float) -> float` same as Pyewacket.gauss()
- `Pyewacket.lognormvariate(mu: float, sigma: float) -> float`
- `Pyewacket.vonmisesvariate(mu: float, kappa: float) -> float`
- `Pyewacket.triangular(low: float, high: float, mode: float = None)`

## Random Sequence Values
- `Pyewacket.choice(seq: List) -> Value`
    - @param seq :: any zero indexed object like a list or tuple.
    - @return :: random value from the list, can be any object type that can be put into a list.
- `Pyewacket.choices(population, weights=None, *, cum_weights=None, k=1)`
    - @param population :: data values
    - @param weights :: relative weights
    - @param cum_weights :: cumulative weights
    - @param k :: number of samples to be collected
- `Pyewacket.cumulative_weighted_choice(table, k=1)`
    - Supports Cumulative Weights only. Convert relative weights to cumulative if needed: `cum_weights = tuple(itertools.accumulate(rel_weights))`
    - @param table :: two dimensional list or tuple of weighted value pairs. `[(1, "a"), (10, "b"), (100, "c")...]`
        - The table can be constructed as `tuple(zip(cum_weights, population))` weights always come first.
    - @param k :: number of samples to be collected. Returns a list of size k if k > 1, otherwise returns a single value - not a list of one.
- `Pyewacket.shuffle(array: list) -> None`
    - Shuffles a list in place.
    - @param array :: must be a mutable list.
    - Implements Knuth B Shuffle Algorithm. Knuth B is twice as fast as Knuth A or Fisher-Yates for every test case. This is likely due to the combination of walking backward and rotating backward into the back side of the list. With this combination it can never modify the data it still needs to walk through. Fresh snow all the way home, aka very low probability for cache misses.
- `Pyewacket.sample(population: List, k: int) -> list`
    - @param population :: list or tuple.
    - @param k :: number of unique samples to get.
    - @return :: size k list of unique random samples.

## Hardware & Software Seeding
- `seed(seed: int=0) -> None`
    - Hardware seeding is enabled by default. This function is used to turn toggle software seeding and set or reset the engine seed. This affects all random functions in the module.
    - @param seed :: any non-zero positive integer less than 2**63 enables software seeding.
    - Calling `seed()` or `seed(0)` will turn off software seeding and re-enable hardware seeding.
    - While you can toggle software seeding on and off and re-seed the engine at will without error, this function is **not intended to be used inside a tight loop**. General rule: seed once, or better yet, not at all. Typically, software seeding is for debugging a product, hardware seeding is used for product release. Please don't use software seeding for the release version of a game!


## Development Log
##### Pyewacket 1.3.9
- Installer update

##### Pyewacket 1.3.8
- Documentation Update

##### Pyewacket 1.3.7
- Fixed more typos

##### Pyewacket 1.3.6
- Fixed Typos

##### Pyewacket 1.3.5
- Installer update

##### Pyewacket 1.3.4
- Storm 3.2.2 Update.

##### Pyewacket 1.3.3
- Pyewacket is now compatible with python notebooks.

##### Pyewacket 1.3.2
- Storm Update

##### Pyewacket 1.3.1
- Storm Update

##### Pyewacket 1.3.0
- Major API Update, several utilities have been moved into their own module: MonkeyScope.
    - distribution_timer
    - distribution
    - timer

##### Pyewacket 1.2.4
- `Pyewacket.randrange()` bug fix
- Test Update

##### Pyewacket 1.2.3
- Minor Bug Fix

##### Pyewacket 1.2.2
- Typo Fix

##### Pyewacket 1.2.1
- Test Update

##### Pyewacket 1.2.0
- Storm Update

##### Pyewacket 1.1.2
- Low level clean up

##### Pyewacket 1.1.1
- Docs Update

##### Pyewacket 1.1.0
- Storm Engine Update

##### Pyewacket 1.0.3
- minor typos

##### Pyewacket 1.0.2
- added choices alternative `cumulative_weighted_choice`

##### Pyewacket 1.0.1
- minor typos

##### Pyewacket 1.0.0
- Storm 2 Rebuild.

##### Pyewacket 0.1.22
- Small bug fix.

##### Pyewacket 0.1.21
- Public Release

##### Pyewacket 0.0.2b1
- Added software seeding.

##### Pyewacket v0.0.1b8
- Fixed a small bug in the tests.

##### Pyewacket v0.0.1b7
- Engine Fine Tuning
- Fixed some typos.

##### Pyewacket v0.0.1b6
- Rearranged tests to be more consistent and match the documentation.

##### Pyewacket v0.0.1b5
- Documentation Upgrade
- Minor Performance Tweaks

##### Pyewacket v0.0.1b4
- Public Beta

##### Pyewacket v0.0.1b3
- quick_test()
- Extended Functionality
    - sample()
    - expovariate()
    - gammavariate()
    - weibullvariate()
    - betavariate()
    - paretovariate()
    - gauss()
    - normalvariate()
    - lognormvariate()
    - vonmisesvariate()
    - triangular()

##### Pyewacket v0.0.1b2
- Basic Functionality
    - random()
    - uniform()
    - randbelow()
    - randint()
    - randrange()
    - choice()
    - choices()
    - shuffle()

##### Pyewacket v0.0.1b1
- Initial Design & Planning


## Distribution and Performance Tests
```
MonkeyScope: Pyewacket

Base Case
Output Analysis: Random._randbelow(10)
Typical Timing: 581 ± 20 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 5
 Maximum: 9
 Mean: 4.557
 Std Deviation: 2.8430179387404504
Distribution of 10000 samples:
 0: 9.9%
 1: 10.19%
 2: 10.64%
 3: 10.21%
 4: 10.19%
 5: 10.02%
 6: 10.09%
 7: 9.63%
 8: 9.47%
 9: 9.66%

Output Analysis: randbelow(10)
Typical Timing: 67 ± 10 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 4
 Maximum: 9
 Mean: 4.425
 Std Deviation: 2.8692115641757754
Distribution of 10000 samples:
 0: 9.92%
 1: 9.48%
 2: 10.36%
 3: 10.7%
 4: 9.92%
 5: 9.85%
 6: 10.38%
 7: 9.96%
 8: 9.76%
 9: 9.67%

Base Case
Output Analysis: Random.randint(1, 10)
Typical Timing: 1148 ± 71 ns
Statistics of 1000 samples:
 Minimum: 1
 Median: 5
 Maximum: 10
 Mean: 5.394
 Std Deviation: 2.8500463154131372
Distribution of 10000 samples:
 1: 10.1%
 2: 10.43%
 3: 9.63%
 4: 9.85%
 5: 9.46%
 6: 9.83%
 7: 10.15%
 8: 10.7%
 9: 9.64%
 10: 10.21%

Output Analysis: randint(1, 10)
Typical Timing: 61 ± 8 ns
Statistics of 1000 samples:
 Minimum: 1
 Median: 6
 Maximum: 10
 Mean: 5.566
 Std Deviation: 2.871871167026822
Distribution of 10000 samples:
 1: 10.52%
 2: 9.61%
 3: 9.96%
 4: 10.1%
 5: 9.95%
 6: 9.38%
 7: 10.66%
 8: 9.84%
 9: 10.13%
 10: 9.85%

Base Case
Output Analysis: Random.randrange(0, 10, 2)
Typical Timing: 1248 ± 73 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 4
 Maximum: 8
 Mean: 3.946
 Std Deviation: 2.7873076615257237
Distribution of 10000 samples:
 0: 20.18%
 2: 19.76%
 4: 21.0%
 6: 19.9%
 8: 19.16%

Output Analysis: randrange(0, 10, 2)
Typical Timing: 98 ± 16 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 4
 Maximum: 8
 Mean: 3.834
 Std Deviation: 2.8072128526351547
Distribution of 10000 samples:
 0: 20.61%
 2: 20.39%
 4: 20.07%
 6: 19.58%
 8: 19.35%

Base Case
Output Analysis: Random.random()
Typical Timing: 37 ± 6 ns
Statistics of 1000 samples:
 Minimum: 0.0022025335119719713
 Median: (0.504236734486946, 0.5043377592978666)
 Maximum: 0.9988675528749947
 Mean: 0.4992614084502893
 Std Deviation: 0.29450740919885326
Post-processor distribution of 10000 samples using round method:
 0: 50.17%
 1: 49.83%

Output Analysis: random()
Typical Timing: 36 ± 1 ns
Statistics of 1000 samples:
 Minimum: 0.0005611174645538731
 Median: (0.5035689629010788, 0.5043732233487602)
 Maximum: 0.9997053348692302
 Mean: 0.5062137836044255
 Std Deviation: 0.2872867534109569
Post-processor distribution of 10000 samples using round method:
 0: 50.19%
 1: 49.81%

Base Case
Output Analysis: Random.uniform(0.0, 10.0)
Typical Timing: 239 ± 21 ns
Statistics of 1000 samples:
 Minimum: 0.00855387357446502
 Median: (4.8377420821319275, 4.839112429261609)
 Maximum: 9.944528377056002
 Mean: 4.985114491741573
 Std Deviation: 2.854828406573762
Post-processor distribution of 10000 samples using floor method:
 0: 9.97%
 1: 9.86%
 2: 9.47%
 3: 9.99%
 4: 10.33%
 5: 9.99%
 6: 9.88%
 7: 10.45%
 8: 10.33%
 9: 9.73%

Output Analysis: uniform(0.0, 10.0)
Typical Timing: 40 ± 6 ns
Statistics of 1000 samples:
 Minimum: 0.014370725680160675
 Median: (4.932233828685737, 4.934800131365183)
 Maximum: 9.991743209602872
 Mean: 4.944711192504797
 Std Deviation: 2.903933069340305
Post-processor distribution of 10000 samples using floor method:
 0: 9.97%
 1: 9.87%
 2: 10.1%
 3: 9.71%
 4: 10.15%
 5: 10.05%
 6: 9.36%
 7: 10.35%
 8: 10.29%
 9: 10.15%

Base Case
Output Analysis: Random.expovariate(1.0)
Typical Timing: 344 ± 20 ns
Statistics of 1000 samples:
 Minimum: 0.00013930738155526723
 Median: (0.6974151830509201, 0.6982605474669916)
 Maximum: 7.006299712833918
 Mean: 0.9851091283909009
 Std Deviation: 0.9482631726906081
Post-processor distribution of 10000 samples using floor method:
 0: 63.02%
 1: 23.19%
 2: 8.99%
 3: 3.01%
 4: 1.15%
 5: 0.38%
 6: 0.16%
 7: 0.04%
 8: 0.04%
 10: 0.01%
 13: 0.01%

Output Analysis: expovariate(1.0)
Typical Timing: 55 ± 6 ns
Statistics of 1000 samples:
 Minimum: 0.0005268217098112992
 Median: (0.7287325498157464, 0.729028105461747)
 Maximum: 6.423738021042586
 Mean: 1.010884902851076
 Std Deviation: 0.9798177662432959
Post-processor distribution of 10000 samples using floor method:
 0: 62.92%
 1: 23.47%
 2: 8.41%
 3: 3.2%
 4: 1.3%
 5: 0.35%
 6: 0.27%
 7: 0.05%
 8: 0.03%

Base Case
Output Analysis: Random.gammavariate(2.0, 1.0)
Typical Timing: 1216 ± 39 ns
Statistics of 1000 samples:
 Minimum: 0.022123265128863975
 Median: (1.6738025588508376, 1.6869422953529067)
 Maximum: 9.144862623568999
 Mean: 1.9946207548427557
 Std Deviation: 1.3831794343166977
Post-processor distribution of 10000 samples using round method:
 0: 9.04%
 1: 34.77%
 2: 27.07%
 3: 15.54%
 4: 7.6%
 5: 3.25%
 6: 1.53%
 7: 0.75%
 8: 0.21%
 9: 0.13%
 10: 0.06%
 11: 0.01%
 12: 0.02%
 13: 0.01%
 14: 0.01%

Output Analysis: gammavariate(2.0, 1.0)
Typical Timing: 114 ± 5 ns
Statistics of 1000 samples:
 Minimum: 0.05050761827178252
 Median: (1.7155254242728513, 1.7155403374497076)
 Maximum: 9.474394865820214
 Mean: 2.0432583626258274
 Std Deviation: 1.440053170380605
Post-processor distribution of 10000 samples using round method:
 0: 8.35%
 1: 36.19%
 2: 26.63%
 3: 15.04%
 4: 7.56%
 5: 3.61%
 6: 1.59%
 7: 0.58%
 8: 0.33%
 9: 0.06%
 10: 0.03%
 11: 0.03%

Base Case
Output Analysis: Random.weibullvariate(1.0, 1.0)
Typical Timing: 433 ± 31 ns
Statistics of 1000 samples:
 Minimum: 0.0013211102177539506
 Median: (0.689421374168411, 0.6902805115868248)
 Maximum: 6.763716954010422
 Mean: 1.0145977021774952
 Std Deviation: 1.0058606176825422
Post-processor distribution of 10000 samples using floor method:
 0: 63.62%
 1: 22.96%
 2: 8.29%
 3: 3.2%
 4: 1.32%
 5: 0.36%
 6: 0.18%
 7: 0.04%
 8: 0.01%
 10: 0.02%

Output Analysis: weibullvariate(1.0, 1.0)
Typical Timing: 103 ± 15 ns
Statistics of 1000 samples:
 Minimum: 0.00143486573238355
 Median: (0.6919630243174832, 0.6933880404695633)
 Maximum: 7.915315904014041
 Mean: 0.9999870976051519
 Std Deviation: 1.0199621642753662
Post-processor distribution of 10000 samples using floor method:
 0: 63.82%
 1: 22.46%
 2: 8.53%
 3: 3.25%
 4: 1.21%
 5: 0.47%
 6: 0.18%
 7: 0.06%
 8: 0.01%
 9: 0.01%

Base Case
Output Analysis: Random.betavariate(3.0, 3.0)
Typical Timing: 2558 ± 78 ns
Statistics of 1000 samples:
 Minimum: 0.039839528361731796
 Median: (0.5015726481908723, 0.5029699817553287)
 Maximum: 0.9435702178836589
 Mean: 0.5000214739643288
 Std Deviation: 0.18805632108618242
Post-processor distribution of 10000 samples using round method:
 0: 49.34%
 1: 50.66%

Output Analysis: betavariate(3.0, 3.0)
Typical Timing: 199 ± 16 ns
Statistics of 1000 samples:
 Minimum: 0.014386257468019166
 Median: (0.5041917967703041, 0.5043820043201677)
 Maximum: 0.9224068506980523
 Mean: 0.5036287644629798
 Std Deviation: 0.19311990407311008
Post-processor distribution of 10000 samples using round method:
 0: 50.03%
 1: 49.97%

Base Case
Output Analysis: Random.paretovariate(4.0)
Typical Timing: 299 ± 22 ns
Statistics of 1000 samples:
 Minimum: 1.0003778533014105
 Median: (1.165002857930227, 1.165698705069618)
 Maximum: 10.516678707241427
 Mean: 1.3111050026121693
 Std Deviation: 0.5187788907898297
Post-processor distribution of 10000 samples using floor method:
 1: 93.54%
 2: 5.2%
 3: 0.93%
 4: 0.19%
 5: 0.03%
 6: 0.04%
 7: 0.04%
 10: 0.01%
 11: 0.01%
 12: 0.01%

Output Analysis: paretovariate(4.0)
Typical Timing: 79 ± 6 ns
Statistics of 1000 samples:
 Minimum: 1.0000021203352474
 Median: (1.1950046733402977, 1.1960253759614277)
 Maximum: 4.928427639622488
 Mean: 1.3384992333095633
 Std Deviation: 0.44348583284188964
Post-processor distribution of 10000 samples using floor method:
 1: 93.57%
 2: 5.14%
 3: 0.83%
 4: 0.32%
 5: 0.08%
 6: 0.03%
 7: 0.01%
 8: 0.01%
 9: 0.01%

Base Case
Output Analysis: Random.gauss(1.0, 1.0)
Typical Timing: 597 ± 27 ns
Statistics of 1000 samples:
 Minimum: -1.9198822626936378
 Median: (1.005335898102709, 1.011229972843203)
 Maximum: 3.995102828970162
 Mean: 1.0036902758611341
 Std Deviation: 1.0049002779744916
Post-processor distribution of 10000 samples using round method:
 -3: 0.01%
 -2: 0.7%
 -1: 6.54%
 0: 24.32%
 1: 37.67%
 2: 24.28%
 3: 5.86%
 4: 0.57%
 5: 0.05%

Output Analysis: gauss(1.0, 1.0)
Typical Timing: 84 ± 2 ns
Statistics of 1000 samples:
 Minimum: -2.105377657621053
 Median: (0.9677613928765401, 0.9738364825460277)
 Maximum: 3.9619897840596185
 Mean: 0.9803515870690724
 Std Deviation: 0.9847928983953689
Post-processor distribution of 10000 samples using round method:
 -3: 0.03%
 -2: 0.58%
 -1: 6.02%
 0: 24.3%
 1: 38.52%
 2: 23.92%
 3: 5.93%
 4: 0.67%
 5: 0.03%

Base Case
Output Analysis: Random.normalvariate(0.0, 2.8)
Typical Timing: 686 ± 22 ns
Statistics of 1000 samples:
 Minimum: -9.36705533019951
 Median: (-0.08343328178059332, -0.07242218755420544)
 Maximum: 9.638137159093363
 Mean: 0.015326886488786868
 Std Deviation: 2.896301190156864
Post-processor distribution of 10000 samples using round method:
 -10: 0.03%
 -9: 0.12%
 -8: 0.24%
 -7: 0.71%
 -6: 1.38%
 -5: 3.12%
 -4: 4.93%
 -3: 8.03%
 -2: 11.44%
 -1: 13.25%
 0: 14.37%
 1: 13.02%
 2: 10.66%
 3: 8.17%
 4: 5.2%
 5: 3.02%
 6: 1.29%
 7: 0.69%
 8: 0.22%
 9: 0.07%
 10: 0.04%

Output Analysis: normalvariate(0.0, 2.8)
Typical Timing: 84 ± 2 ns
Statistics of 1000 samples:
 Minimum: -9.046455801727028
 Median: (0.004054759430993154, 0.021315402592363517)
 Maximum: 9.578970261780695
 Mean: -0.014712782228340401
 Std Deviation: 2.760000323856411
Post-processor distribution of 10000 samples using round method:
 -11: 0.01%
 -10: 0.04%
 -9: 0.05%
 -8: 0.16%
 -7: 0.69%
 -6: 1.61%
 -5: 3.04%
 -4: 5.24%
 -3: 7.95%
 -2: 10.99%
 -1: 13.18%
 0: 14.69%
 1: 13.53%
 2: 11.0%
 3: 7.66%
 4: 4.95%
 5: 2.59%
 6: 1.46%
 7: 0.73%
 8: 0.3%
 9: 0.09%
 10: 0.02%
 11: 0.01%
 13: 0.01%

Base Case
Output Analysis: Random.lognormvariate(0.0, 0.5)
Typical Timing: 878 ± 53 ns
Statistics of 1000 samples:
 Minimum: 0.2248693655862111
 Median: (1.0456443550688597, 1.0463295395067145)
 Maximum: 5.681692998787057
 Mean: 1.1774875785497383
 Std Deviation: 0.6355607662063447
Post-processor distribution of 10000 samples using round method:
 0: 8.24%
 1: 71.03%
 2: 17.45%
 3: 2.71%
 4: 0.43%
 5: 0.11%
 6: 0.02%
 9: 0.01%

Output Analysis: lognormvariate(0.0, 0.5)
Typical Timing: 109 ± 9 ns
Statistics of 1000 samples:
 Minimum: 0.21215863870079615
 Median: (0.9708663230257852, 0.971472722331232)
 Maximum: 4.11173040529319
 Mean: 1.0903966237459795
 Std Deviation: 0.5587946576471575
Post-processor distribution of 10000 samples using round method:
 0: 8.65%
 1: 70.43%
 2: 17.45%
 3: 2.91%
 4: 0.48%
 5: 0.05%
 6: 0.03%

Base Case
Output Analysis: Random.vonmisesvariate(0, 0)
Typical Timing: 270 ± 21 ns
Statistics of 1000 samples:
 Minimum: 0.004918010643852079
 Median: (3.212229751626989, 3.2201766390537983)
 Maximum: 6.257997091009342
 Mean: 3.140987802653663
 Std Deviation: 1.7890683319823657
Post-processor distribution of 10000 samples using floor method:
 0: 16.05%
 1: 16.0%
 2: 15.44%
 3: 16.56%
 4: 15.69%
 5: 15.67%
 6: 4.59%

Output Analysis: vonmisesvariate(0, 0)
Typical Timing: 70 ± 9 ns
Statistics of 1000 samples:
 Minimum: 0.00460539766627348
 Median: (3.084578088420162, 3.0866691165283298)
 Maximum: 6.278298447163166
 Mean: 3.115976931902511
 Std Deviation: 1.7888917760687573
Post-processor distribution of 10000 samples using floor method:
 0: 15.94%
 1: 15.94%
 2: 15.94%
 3: 15.77%
 4: 15.78%
 5: 15.93%
 6: 4.7%

Base Case
Output Analysis: Random.triangular(0.0, 10.0, 0.0)
Typical Timing: 495 ± 19 ns
Statistics of 1000 samples:
 Minimum: 0.003237961622717833
 Median: (2.756018739981477, 2.77041555411836)
 Maximum: 9.679493886664185
 Mean: 3.217204114204818
 Std Deviation: 2.2695608348990586
Post-processor distribution of 10000 samples using floor method:
 0: 19.81%
 1: 16.45%
 2: 15.12%
 3: 12.91%
 4: 11.14%
 5: 8.9%
 6: 6.77%
 7: 4.82%
 8: 3.08%
 9: 1.0%

Output Analysis: triangular(0.0, 10.0, 0.0)
Typical Timing: 43 ± 1 ns
Statistics of 1000 samples:
 Minimum: 0.0003452204741609677
 Median: (3.050051144263745, 3.0566898002269616)
 Maximum: 9.787833018174565
 Mean: 3.335322504335237
 Std Deviation: 2.303377888450858
Post-processor distribution of 10000 samples using floor method:
 0: 18.17%
 1: 16.9%
 2: 15.42%
 3: 12.71%
 4: 11.34%
 5: 9.08%
 6: 7.48%
 7: 4.89%
 8: 3.02%
 9: 0.99%

Base Case
Output Analysis: Random.choice([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
Typical Timing: 789 ± 39 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 5
 Maximum: 9
 Mean: 4.604
 Std Deviation: 2.8201390036663083
Distribution of 10000 samples:
 0: 10.18%
 1: 9.69%
 2: 9.88%
 3: 9.94%
 4: 10.21%
 5: 9.87%
 6: 9.82%
 7: 10.29%
 8: 9.56%
 9: 10.56%

Output Analysis: choice([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
Typical Timing: 75 ± 10 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 5
 Maximum: 9
 Mean: 4.531
 Std Deviation: 2.9125657074133113
Distribution of 10000 samples:
 0: 9.55%
 1: 10.29%
 2: 9.91%
 3: 9.94%
 4: 10.03%
 5: 10.1%
 6: 10.73%
 7: 10.19%
 8: 10.0%
 9: 9.26%

Base Case
Output Analysis: Random.choices([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], [10, 9, 8, 7, 6, 5, 4, 3, 2, 1], k=1)
Typical Timing: 2374 ± 70 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 3
 Maximum: 9
 Mean: 2.944
 Std Deviation: 2.4076677511650146
Distribution of 10000 samples:
 0: 17.9%
 1: 16.81%
 2: 14.91%
 3: 12.4%
 4: 10.98%
 5: 8.8%
 6: 7.55%
 7: 5.4%
 8: 3.54%
 9: 1.71%

Output Analysis: choices([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], [10, 9, 8, 7, 6, 5, 4, 3, 2, 1], k=1)
Typical Timing: 1147 ± 56 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 3
 Maximum: 9
 Mean: 3.016
 Std Deviation: 2.4754280437936385
Distribution of 10000 samples:
 0: 18.44%
 1: 16.19%
 2: 14.63%
 3: 12.99%
 4: 10.77%
 5: 8.88%
 6: 7.59%
 7: 5.21%
 8: 3.57%
 9: 1.73%

Base Case
Output Analysis: Random.choices([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], cum_weights=[10, 19, 27, 34, 40, 45, 49, 52, 54, 55], k=1)
Typical Timing: 1782 ± 52 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 2
 Maximum: 9
 Mean: 2.886
 Std Deviation: 2.4594723011247757
Distribution of 10000 samples:
 0: 17.65%
 1: 16.66%
 2: 14.8%
 3: 12.17%
 4: 11.21%
 5: 9.01%
 6: 7.36%
 7: 5.67%
 8: 3.66%
 9: 1.81%

Output Analysis: choices([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], cum_weights=[10, 19, 27, 34, 40, 45, 49, 52, 54, 55], k=1)
Typical Timing: 702 ± 20 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 3
 Maximum: 9
 Mean: 3.054
 Std Deviation: 2.409374192606869
Distribution of 10000 samples:
 0: 17.91%
 1: 15.49%
 2: 14.94%
 3: 12.73%
 4: 10.98%
 5: 9.59%
 6: 7.51%
 7: 5.46%
 8: 3.54%
 9: 1.85%

Base Case
Timer only: random.shuffle(some_list) of size 10:
Typical Timing: 8322 ± 1705 ns

Timer only: shuffle(some_list) of size 10:
Typical Timing: 794 ± 317 ns

Base Case
Output Analysis: Random.sample([5, 7, 8, 2, 6, 3, 4, 9, 1, 0], k=3)
Typical Timing: 4137 ± 161 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 4
 Maximum: 9
 Mean: 4.485
 Std Deviation: 2.9294666750109997
Distribution of 10000 samples:
 0: 10.03%
 1: 10.19%
 2: 9.98%
 3: 10.05%
 4: 9.92%
 5: 9.44%
 6: 10.59%
 7: 9.77%
 8: 10.26%
 9: 9.77%

Output Analysis: sample([5, 7, 8, 2, 6, 3, 4, 9, 1, 0], k=3)
Typical Timing: 848 ± 20 ns
Statistics of 1000 samples:
 Minimum: 0
 Median: 5
 Maximum: 9
 Mean: 4.568
 Std Deviation: 2.8631060057217583
Distribution of 10000 samples:
 0: 9.8%
 1: 10.03%
 2: 10.4%
 3: 9.73%
 4: 10.17%
 5: 10.1%
 6: 9.76%
 7: 10.08%
 8: 10.13%
 9: 9.8%


Total Test Time: 1.986 sec
```
