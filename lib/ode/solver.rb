module Ode
  class Solver
    def initialize(f, jac=nil)
      @f = f
      @t = 0
      @y = 0
      @jac = jac
      @fargs = nil
      @opts = nil
      @method = :lsoda
    end

    def init(t0, y0)
      @t = t0
      @y = y0
      self
    end

    def method(name)
        if Ode::Methods.respond_to?(name)
          @method = name
        else
          raise NameError, "Ode do not have an implementation of the method named" + name.to_s + "."
        end
      self
    end

    def f_args(args)
      @fargs=args
      self
    end

    def integrate(t_out)
      @opts ||= Ode::Methods.default_opts(@method)
      @y = Ode::Methods.send(@method, t_out, @f, @jac, @t, @y, @fargs, @opts)
      @t = t_out
      self
    end

    attr_reader :t, :y
  end
end
