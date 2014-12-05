# Ode

[![Gem Version](https://badge.fury.io/rb/ode.svg)](http://badge.fury.io/rb/ode)

A ODE solver package for Ruby users.
Ode is a the wrapper for [ODEPACK](https://computation.llnl.gov/casc/odepack/) and may perform as well as scipy.integrate.odeint and other wrappers.

## Installation
```
gem install ode
```

## Examples
```
require 'ode'

f = Proc.new{|t, y, fargs|
  p, r, b = fargs[:p], fargs[:r], fargs[:b]
    [ -p*y[0] + p*y[1],
      -y[0]*y[2] + r*y[0] - y[1],
      y[0]*y[1] - b*y[2]
    ]
}

solver = Ode::Solver.new(f).init(0, [0, 0, 0]).f_args({p: 10, r: 28, b: 8/3}).
solver.integrate(3.0) #integrate f from t=0 to t=3.0
```

## License

All files under ext/ode/odepack are from scipy.integrate (originally from ODEPACK), and distributed under [SciPy License](https://github.com/domitry/ode/blob/master/SciPy-License.txt).  
All the other files are distributed under [the MIT License](https://github.com/domitry/ode/blob/master/MIT-License.txt).
