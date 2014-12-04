# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'ode/version'

Gem::Specification.new do |spec|
  spec.name          = "ode"
  spec.version       = Ode::VERSION
  spec.authors       = ["domitry"]
  spec.email         = ["domitry@gmail.com"]
  spec.summary       = %q{The Ruby wrapper for ODEPACK}
  spec.description   = %q{The Ruby wrapper for ODEPACK}
  spec.homepage      = ""
  spec.license       = "MIT"
  spec.extensions    = %w[ext/ode/extconf.rb]
  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.5"
  spec.add_development_dependency "rake"
end
