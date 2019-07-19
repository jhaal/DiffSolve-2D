![](https://github.com/jhaal/DiffSolve-2D/blob/master/k.png?raw=true)

# 2-D Neutron Diffusion Equation Solver in Cartesian Coordinate Geometry

> Neutron Diffusion Equation Solver in Cartesian Coordinate Geometry


- DiffSolve-2D.cpp
- DESCRIPTION:steady state testbench
- REQUIREMENTS:DiffSolve-2D.hpp,ccomp,xsec
- BUGS: None
- AUTHOR: Alok_Jha
- E-mail: jhaalok1984_at_gmail.com
- ORGANIZATION:NPCIL
- VERSION:1.1
- REVISION:0.0
- CREATED:Thursday, 17 January 2019. Released on 18-06-2019



[![Build Status](http://img.shields.io/travis/badges/badgerbadgerbadger.svg?style=flat-square)](https://travis-ci.org/badges/badgerbadgerbadger)  [![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org) [![Badges](http://img.shields.io/:badges-9/9-ff6799.svg?style=flat-square)](https://github.com/badges/badgerbadgerbadger)

## Table of Contents (Optional)

- [Installation](#installation)
- [Features](#features)
- [Contributing](#contributing)
- [Team](#team)
- [FAQ](#faq)
- [Support](#support)
- [License](#license)

## Installation

None

## Features

### Any Core Size

Any 2-D Core size input will work. Modify in the header file. However, for WINDOWS machine of 32 bits, the core size smaller than 12 rows by 16 columns, the results are not correct due to 'double' and 'long double' limitations. Please check by reducing the 

```
#define F_max        1e5	 //maximum iteration

#define K_max        1e5	 //maximum iteration 
```
in the header file. It may yield reasonably acceptable results.

### Addendum

- Added reactivity &rho; calculation in the code.
- Added criticality declaration in the code.

 

### Compile

Use makefile


```shell
$ make -k makefile
```
or, at the terminal

Call

```shell
$ g++ DiffSolve-2D.cpp -o DiffSolve-2D && ./DiffSolve-2D
```
or,

```shell
$ c++ DiffSolve-2D.cpp -o DiffSolve-2D && ./DiffSolve-2D
```

### Plotting Of Results

```shell
$ gnuplot < plot.gp
```

Label in the plot "thermal.txt" corrected from the earlier code where incorrect y-label is generated.


## Support

Reach out to me at the following place!

- Twitter at <a href="http://twitter.com/amigo_2222" target="_blank">`@amigo_2222`</a>

---

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
